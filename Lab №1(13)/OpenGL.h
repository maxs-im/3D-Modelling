#ifndef OPENGL_H_
#define OPENGL_H_

#include <gl\glut.h>

#include "AntTweakBar_user.h"

#include "Figure.h"
#include "Figure_change.h"

namespace OpenGL
{
	static int Window_Size_H(768),
			Window_Size_W(1366),
			fps(60);

	void start_OpenGL(double);
	void Initialize();

	void Timer(int);
	void Keyboard(unsigned char, int, int);
	void Mouse(int, int, int, int);
	void SKeyboard(int, int, int);
	void Reshape(int, int);

	void Draw();
	void Draw_figures(Figure*);
};


#endif //OPENGL_H_