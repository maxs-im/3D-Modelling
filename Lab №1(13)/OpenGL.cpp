#include "OpenGL.h"

using namespace Change;

void OpenGL::start_OpenGL( double _box_size )
{
		//initialization
	box_size = box_size;
	int argc = 1;
	char *argv[1] = { (char*)"" }; 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH|GL_STENCIL);
	glutInitWindowSize(Window_Size_W, Window_Size_H);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D-Models");

	ATB_menu::AntTweak_Menu(Window_Size_W, Window_Size_H);

	Initialize();
	glutDisplayFunc(Draw);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SKeyboard);
	//glutReshapeFunc(Reshape);
	glutTimerFunc(1000/fps, Timer, 0);

	glutMainLoop();
};
void OpenGL::Timer(int value)
{
  glutPostRedisplay();
  glutTimerFunc(1000/fps, Timer, 0); 
};
void OpenGL::Initialize()
{
	glViewport(0, 0, Window_Size_W, Window_Size_H);
	glutFullScreen();
	glClearColor( (GLclampf)0.1, (GLclampf)0.1, (GLclampf)0.1, 1.0);
	glClearDepth(1.0);
	glClearStencil(0);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40, (double)Window_Size_W/Window_Size_H, 1, box_size*1000);
	gluLookAt (1.2*box_size/2, 0.8*box_size/2, 1.2*box_size/2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};
void OpenGL::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glLineWidth(1);

	glPushMatrix();

	glStencilFunc(GL_ALWAYS, 0, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	GLfloat step = (GLfloat)box_size / 50,
			length = (GLfloat)0.9*(GLfloat)(box_size / 2);

	glBegin(GL_LINES);
		glColor3f( (GLfloat)0.2, (GLfloat)0.2, (GLfloat)0.2);
		for(GLfloat i(step); i < length; i+=step) {
			glVertex3f(0.0, 0.0, i);
			glVertex3f(0.0, length, i);
			glVertex3f(i, 0.0, 0.0);
			glVertex3f(i, length, 0.0);

			glVertex3f(0.0, 0.0, i);
			glVertex3f(length, 0.0, i);
			glVertex3f(0.0, i, 0.0);
			glVertex3f(length, i, 0.0);

			glVertex3f(i, 0.0, 0.0);
			glVertex3f(i, 0.0, length);
			glVertex3f(0.0, i, 0.0);
			glVertex3f(0.0, i, length);
		}

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, (GLfloat)-box_size/4, 0.0);
		glVertex3f(0.0, (GLfloat)box_size/2, 0.0);//y - green

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f((GLfloat)-box_size/4, 0.0, 0.0);
		glVertex3f((GLfloat)box_size/2, 0.0, 0.0);//x - red
		
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, (GLfloat)-box_size/4);
		glVertex3f(0.0, 0.0, (GLfloat)box_size/2);//z - blue.
	glEnd();
	glPopMatrix();
	

	glPushMatrix();

	for(int i(figures_to_paint.size()-1); i >= 0; i--) {
		glStencilFunc(GL_ALWAYS, i+1, 0);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		Draw_figures(figures_to_paint[i]);
	}
	glPopMatrix();

	TwDraw();
	
	glutSwapBuffers();
};
void OpenGL::Draw_figures(Figure* figure)
{		
	glColor3f((GLfloat)figure->color.x, (GLfloat)figure->color.y, (GLfloat)figure->color.z);	
	if(figure->selected) glLineWidth(3);
	else glLineWidth(2);

	glBegin(GL_LINE_LOOP);
		for(auto it : figure->point)
			glVertex3d(it.x, it.y, it.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(auto it : figure->s_point)
			glVertex3d(it.x, it.y, it.z);
	glEnd();

	 bool k(1);								// prisma or pyramid			
	if (figure->s_point.size() == 1) k = 0;
	if (figure->s_point.size() == 0) 
		return;								//projection
	glBegin(GL_LINES);
		for(int i(figure->point.size()-1); i >= 0; i--)
		{
			glVertex3d(figure->point[i].x, figure->point[i].y, figure->point[i].z);
			glVertex3d(figure->s_point[i*k].x, figure->s_point[i*k].y, figure->s_point[i*k].z);
		}
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0x00F5);
	glLineWidth(1.5);
	for(auto it : figure->projections) {
		glBegin(GL_LINE_LOOP);
			for(auto it0 : it) 
				glVertex3d(it0.x, it0.y, it0.z);
		glEnd();
	}
	glDisable(GL_LINE_STIPPLE);
};
void OpenGL::Mouse(int button, int state, int x, int y)
{
	if( !TwEventMouseButtonGLUT(button, state, x, y) ) {
		if(state != GLUT_DOWN)
			return;

		GLuint index;
		glReadPixels(x, Window_Size_H - y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		if(index == 0) {
			for(auto &it : figures_to_paint)
				it->selected = false;
		} 
		else {
			if(figures_to_paint[index-1]->selected)
				figures_to_paint[index-1]->selected = false;
			else
				figures_to_paint[index-1]->selected = true;
		}
	}
};
void OpenGL::Keyboard(unsigned char key, int x, int y)
{
	if(!TwEventKeyboardGLUT(key, x , y)) {
		if(key == 27) {
			for(auto it : figures_to_paint)
				it->~Figure();
			ATB_menu::Stop_TW();
			exit(1);
		}
	
		size_t count = figures_to_paint.size();
		if(count == 0)
			return;

		for(size_t i = 0; i < count; i++)
			if(figures_to_paint[i]->selected)
			switch (key) { 
			case '4':
				change_Angle(figures_to_paint[i], -1, 0, 0); 
				break; 
			case '7': 
				change_Angle(figures_to_paint[i], 1, 0, 0); 
				break; 
			case '5': 
				change_Angle(figures_to_paint[i], 0, -1, 0);
				break; 
			case '8': 
				change_Angle(figures_to_paint[i], 0, 1, 0); 
				break; 
			case '6': 
				change_Angle(figures_to_paint[i], 0, 0, -1);
				break; 
			case '9': 
				change_Angle(figures_to_paint[i], 0, 0, 1); 
				break; 
			case 'q':
				change_Coordinates(figures_to_paint[i], 1, 0, 0);
				break;
			case 'w':
				change_Coordinates(figures_to_paint[i], -1, 0, 0);
				break;
			case 'a':
				change_Coordinates(figures_to_paint[i], 0, 1, 0);
				break;
			case 's':
				change_Coordinates(figures_to_paint[i], 0, -1, 0);
				break;
			case 'z':
				change_Coordinates(figures_to_paint[i], 0, 0, 1);
				break;
			case 'x':
				change_Coordinates(figures_to_paint[i], 0, 0, -1);
				break;
			case 'e':
				change_Zoom(figures_to_paint[i], 0);
				break;
			case 'r':		
				change_Zoom(figures_to_paint[i], 1);
				break;
			} 
	}
};
void OpenGL::SKeyboard(int key, int x, int y)
{
	if(!TwEventSpecialGLUT(key, x, y)) {
		switch (key) { 
		case GLUT_KEY_RIGHT: 
			glRotatef(-1.0, 0.0, 1.0, 0.0);
			break; 
		case GLUT_KEY_LEFT: 
			glRotatef(1.0, 0.0, 1.0, 0.0);
			break; 
		case GLUT_KEY_UP: 
			glRotatef(1.0, 1.0, 0.0, -1.0);
			break; 
		case GLUT_KEY_DOWN: 
			glRotatef(-1.0, 1.0, 0, -1.0);
			//glTranslated( -10, (double)2/3 * -10, -10);
			break; 
		}
	}
};
void OpenGL::Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (double)width/height, 1, box_size*1000);
	gluLookAt (1.1 * box_size/2, 0.9 * box_size/2, 1.1 * box_size/2, 
				0.0, 0.0, 0.0, 
				0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	ATB_menu::Reshape(width, height);
};