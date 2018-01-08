#include "AntTweakBar_user.h"

#include <gl\glut.h>

#include "Pyramid(R_4).h"
#include "Prism.h"

void ATB_menu::Initialize(int width, int height)
{
	TwInit(TW_OPENGL, nullptr);
	TwWindowSize(width, height);
};
void ATB_menu::Reshape(int width, int height)
{
	TwWindowSize(width, height);
};
void ATB_menu::Registration()
{
	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
	glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	TwGLUTModifiersFunc(glutGetModifiers);
};
void ATB_menu::Stop_TW()
{
	TwTerminate();
};
void ATB_menu::AntTweak_Menu(int width, int height)
{
	ATB_menu::Initialize(width, height);
	ATB_menu::Registration();

	bar = TwNewBar("Menu");

	TwDefine(" GLOBAL help='Play with 3D modeling! \n\n"\
			 "\t\t\t\t\tControl\n"\
			 "(-) Press \"arrows\" to rotate the scene \n"\
			 "(-) Press (to rotate figure)\n \t\t4,7 --> along X-axis;\n \t\t5,8 --> along Y-axis;\n \t\t6,8 --> along Z-axis\n"\
			 "(-) Press ( to move figure )\n \t\tq,w --> along X-axis;\n \t\ta,s --> along Y-axis;\n \t\tz,x --> along Z-axis\n"\
			 "(-) Press \"e\"/\"r\" to increase/decrease figure' ");

	TwDefine(" Menu movable=false resizable=false color='96 10 100' size = '300 500'");
	TwDefine(" GLOBAL fontsize=3 ");


	Menu_Figure();
	TwAddSeparator(bar, nullptr, "");
	Menu_Settings();
	TwAddSeparator(bar, nullptr, "");
	Menu_DB();

};

void TW_CALL ATB_menu::GetCallback_Settings(void*)
{ 
	for(auto &it : figures_to_paint)
		if(it->selected) {
			it->d_angle = d_angle_TW;
			it->d_step = d_step_TW;
			it->d_zoom = d_zoom_TW;

			it->color(color3F_TW[0], color3F_TW[1], color3F_TW[2]);
		}
};
void TW_CALL ATB_menu::SetCallback_DataBase(void*)
{
	DATA.Insert(figures_to_paint);
};
void TW_CALL ATB_menu::GetCallback_DataBase(void*)
{
	DATA.Download(figures_to_paint);
};
void TW_CALL ATB_menu::Callback_Figure_Delete(void*)
{
	for(int i = figures_to_paint.size()-1; i >= 0 ; i--)
			if(figures_to_paint[i]->selected) {
				figures_to_paint[i]->~Figure();
				figures_to_paint.erase(figures_to_paint.begin()+i);
			}
};
void TW_CALL ATB_menu::Callback_Projection_Delete(void*)
{
	for(int i = figures_to_paint.size()-1; i >= 0 ; i--)
		if(figures_to_paint[i]->selected && 
			!figures_to_paint[i]->projections.empty())
				figures_to_paint[i]->projections.pop_back();
};
void TW_CALL ATB_menu::Callback_Figure_Selected(void*)
{
	for(auto &it : figures_to_paint)
		it->selected = true;
};
void TW_CALL ATB_menu::GetCallback_Pr(void*)
{
	if(Pr_type_TW._x == Pr_type_TW._y &&
		Pr_type_TW._x == Pr_type_TW._z)
		return;

	for(int i = figures_to_paint.size()-1; i >= 0 ; i--)
		if(figures_to_paint[i]->selected)
			Projection::make_Projection(figures_to_paint[i], 
													Pr_type_TW);
};
void TW_CALL ATB_menu::GetCallback_Pyramid(void*)
{
	if(length_TW > 0 && height_TW > 0)
		figures_to_paint.push_back(new Pyramid(height_TW, length_TW));
};
void TW_CALL ATB_menu::GetCallback_Prism(void*)
{
	if(points_TW.empty() || (points_TW.size() == 1 && angle_TW == (0, 0, 0)))
		return;
	figures_to_paint.push_back(new Prism(points_TW, angle_TW));
	points_TW.clear();
	angle_TW = (0, 0, 0);
	number_points_TW = 0;
};
void TW_CALL ATB_menu::Callback_Point(void* insert)
{
	bool ans = static_cast<bool>(insert);
	if(ans) {
		points_TW.push_back(temp_point);
		number_points_TW++;
	}
	else
		if(!points_TW.empty()) {
			points_TW.pop_back();
			number_points_TW--;
		}
};

void ATB_menu::Menu_Settings()
{
	TwAddVarRW(bar, "Color", TW_TYPE_COLOR3F, &color3F_TW, 
		" group=Settings ");
	TwAddVarRW(bar, "Angel", TW_TYPE_DOUBLE, &d_angle_TW, 
		" group=Settings value=2.0 min=0.0 max=6.0 step=0.1 ");
	TwAddVarRW(bar, "Step", TW_TYPE_DOUBLE, &d_step_TW, 
		" group=Settings value=2.0 min=0.0 max=6.0 step=0.1 ");
	TwAddVarRW(bar, "Zoom", TW_TYPE_DOUBLE, &d_zoom_TW, 
		" group=Settings value=0.1 min=0.0 max=0.35 step=0.01 ");
	TwAddButton(bar, "Save_settings", GetCallback_Settings, nullptr, 
		" group=Settings label='Apply' ");

	TwDefine("Menu/Settings opened=false");
};
void ATB_menu::Menu_DB()
{
	TwAddButton(bar, "Save", SetCallback_DataBase, nullptr, 
		" group=DataBase label='Save' ");
	TwAddButton(bar, "Download", GetCallback_DataBase, nullptr, 
		" group=DataBase label='Download' ");

	TwDefine("Menu/DataBase opened=false");
};
void ATB_menu::Menu_Figure()
{
	TwAddButton(bar, "Selected", Callback_Figure_Selected, nullptr, 
		"label='Selected All' ");
	TwAddSeparator(bar, nullptr, nullptr);
	TwAddButton(bar, "Delete", Callback_Figure_Delete, nullptr, 
		" group=Figures label='Delete Figure' ");

	TwDefine("Menu/Figures opened=false");
	
	Menu_Pyramid();
	Menu_Prism();
	Menu_Projection();
};
void ATB_menu::Menu_Pyramid()
{
	TwAddVarRW(bar, "Height", TW_TYPE_DOUBLE, &height_TW, 
		" group=Pyramid value=0 min=0 max=1000 step=10 ");
	TwAddVarRW(bar, "Length", TW_TYPE_DOUBLE, &length_TW, 
		" group=Pyramid value=0 min=0 max=1000 step=10 ");
	TwAddButton(bar, "Apply Pyramid", GetCallback_Pyramid, nullptr, 
		" group=Pyramid ");
	TwAddSeparator(bar, nullptr, " group=Pyramid ");
	TwDefine( " Menu/Pyramid group=Figures " ); 
	TwDefine("Menu/Pyramid opened=false");
};
void ATB_menu::Menu_Prism()
{
	TwAddVarRO(bar, "NumberPointsPrism", TW_TYPE_INT16, &number_points_TW, 
				" group=Prism label=' Points on Base:' ");

	TwType my_points = TwDefineStruct("MyStruct_forPoints", 
		Coordinates_TW, 3, sizeof(Coordinates),
		nullptr, nullptr);
	TwAddVarRW(bar, " ", my_points, &temp_point, 
		" group=Point ");
	TwAddButton(bar, "Push", Callback_Point, (void*)true, 
		" group=Point ");
	TwAddButton(bar, "Pop", Callback_Point, (void*)false, 
		" group=Point ");
	TwDefine( " Menu/Point group=Prism " ); 
	TwAddVarRW(bar, "Angle", my_points, &angle_TW, 
		" group=Prism ");
	TwAddButton(bar, "Apply Prism", GetCallback_Prism, nullptr, 
		" group=Prism ");
	TwAddSeparator(bar, nullptr, " group=Prism ");
	TwDefine( " Menu/Prism group=Figures " ); 

	TwDefine("Menu/Point opened=true");
	TwDefine("Menu/Prism opened=false");
};
void ATB_menu::Menu_Projection()
{
	TwType my_choose_projection = TwDefineStruct("MyStruct_forProjection", 
		Choose_projection, 3, sizeof(Projection::Pr_struct), 
		nullptr, nullptr);
	TwAddVarRW(bar, "Projection", my_choose_projection, &Pr_type_TW, 
		" group=Figures ");
	TwAddButton(bar, "Apply Projection", GetCallback_Pr, nullptr, 
		" group=Projection ");
	TwAddButton(bar, "Delete last projection", Callback_Projection_Delete, nullptr, 
		" group=Projection ");
	TwDefine("Menu/Projection opened=false");
};