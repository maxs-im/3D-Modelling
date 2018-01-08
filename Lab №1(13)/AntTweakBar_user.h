#ifndef ANTTWEAKBAR_USER_H_
#define ANTTWEAKBAR_USER_H_

#include <AntTweakBar.h>

#include "Figure.h"
#include "Projection.h"
#include "DataBase.h"

namespace ATB_menu
{
	static TwStructMember Coordinates_TW[] = {
		{ "x", TW_TYPE_DOUBLE, offsetof(Coordinates, x), "step=10 min=-1000 max=1000" },
		{ "y", TW_TYPE_DOUBLE, offsetof(Coordinates, y), "step=10 min=-1000 max=1000" },
		{ "z", TW_TYPE_DOUBLE, offsetof(Coordinates, z), "step=10 min=-1000 max=1000" }
	};
	static TwStructMember Choose_projection[] = {
		{ "On X", TW_TYPE_BOOLCPP, offsetof(Projection::Pr_struct, _x), " true='Make' false='-' "},
		{ "On Y", TW_TYPE_BOOLCPP, offsetof(Projection::Pr_struct, _y), " true='Make' false='-' "},
		{ "On Z", TW_TYPE_BOOLCPP, offsetof(Projection::Pr_struct, _z), " true='Make' false='-' "}
	};

	static TwBar *bar;
		//settings
	static float color3F_TW[] = {0.0, 0.0, 0.0};
	static double d_step_TW, d_angle_TW, d_zoom_TW;
	static Coordinates color_TW;
		//projections
	static Projection::Pr_struct Pr_type_TW( 0, 0, 0 );
		//pyramid
	static double height_TW,
				length_TW;
		//prism
	static std::vector<Coordinates> points_TW;
	static Coordinates angle_TW,
					temp_point;
	static unsigned number_points_TW(0);
	
	void Initialize(int, int);
	void Reshape(int, int);
	void Registration();
	void AntTweak_Menu(int, int);
	void Stop_TW();

	void Menu_Figure();
	 void Menu_Pyramid();
	 void Menu_Prism();
	 void Menu_Projection();
	void Menu_Settings();
	void Menu_DB();

	void TW_CALL SetCallback(const void *, void *);
	void TW_CALL GetCallback_Settings(void*);
	void TW_CALL GetCallback_DataBase(void*);
	void TW_CALL SetCallback_DataBase(void*);
	void TW_CALL Callback_Figure_Delete(void*);
	void TW_CALL Callback_Projection_Delete(void*);
	void TW_CALL Callback_Figure_Selected(void*);

	void TW_CALL GetCallback_Pr(void*);
	void TW_CALL GetCallback_Pyramid(void*);
	void TW_CALL GetCallback_Prism(void*);
	void TW_CALL Callback_Point(void*);
};

#endif //ANTTWEAKBAR_USER_H_