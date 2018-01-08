#include "DataBase.h"

#include "Pyramid(R_4).h"
#include "Prism.h"

#define PATH "Data.db"
		//Storage file
Data_Base DATA(PATH);

Data_Base::Data_Base(char* _path) : path(_path)
{
	sqlite3_open(path, &DB);
	Create();
	sqlite3_close(DB);
};
void Data_Base::Create()
{
	SQL = "CREATE TABLE Figures ("\
		  "ID INT PRIMARY KEY, Type TEXT, Object BLOB);";	
	sqlite3_prepare_v2(DB, SQL, -1, &statement, nullptr);
	sqlite3_step(statement);
	sqlite3_finalize(statement);
};
void Data_Base::Insert(const std::vector<Figure*>& re_data)
{
	sqlite3_open(path, &DB);
	
	Delete();

	SQL = "INSERT INTO Figures(ID, Type, Object)"\
		  "VALUES(?, ?, ?);";
	sqlite3_prepare_v2(DB, SQL, -1, &statement, nullptr);

	int count = re_data.size();
	for(int i(0); i < count; i++) {
		const char* type = re_data[i]->getname();
		sqlite3_bind_int(statement, 1, i+1);
		sqlite3_bind_text(statement, 2, type, 
											-1, nullptr);
		/*
		if( strcmp(type, "Prism") == 0 )
			sqlite3_bind_blob(statement, 3, re_data[i], 
											sizeof(Prism), nullptr);
		else if( s	trcmp(type, "Pyramid(R_4)") == 0 )
			sqlite3_bind_blob(statement, 3, re_data[i], 
											sizeof(Pyramid), nullptr);
		*/
		Zip_box(re_data[i]);
		sqlite3_bind_blob(statement, 3, box, 
			sizeof(Coordinates)*((int)(3+box[0].x+box[0].y)), nullptr);

		sqlite3_step(statement);
		sqlite3_reset(statement);
		delete []box;
	}
	sqlite3_finalize(statement);

	sqlite3_close(DB);
};
void Data_Base::Delete()
{
	SQL = "DELETE FROM FIGURES;";
	sqlite3_prepare_v2(DB, SQL, -1, &statement, nullptr);
	sqlite3_step(statement);
	sqlite3_finalize(statement);
};
void Data_Base::Download(std::vector<Figure*>& data)
{
	sqlite3_open(path, &DB);

	for(auto &it : data)
		it->~Figure();
	data.clear();

	SQL = "SELECT * from Figures";
	sqlite3_prepare_v2(DB, SQL, -1, &statement, nullptr);

	 while (sqlite3_step(statement) == SQLITE_ROW) {
		const char* type; 
		type = (const char*)sqlite3_column_text(statement, 1);

		Figure* temp;
		if( strcmp(type, "Prism") == 0 ) {
			/*
			Prism* temp;
			temp = (Prism *)sqlite3_column_blob(statement, 2);
			data.push_back(new Prism(*temp));
			*/
			box = (Coordinates*)sqlite3_column_blob(statement, 2);
			temp = new Prism(*UnZip_box());
		}
		else if ( strcmp(type, "Pyramid(R_4)") == 0 ) {
			/*
			Pyramid* temp;
			temp = (Pyramid *)sqlite3_column_blob(statement, 2);
			data.push_back(new Pyramid(*temp));
			*/
			box = (Coordinates*)sqlite3_column_blob(statement, 2);
			temp = new Pyramid(*UnZip_box());
		}
		data.push_back(temp);
	}
	sqlite3_finalize(statement);

	sqlite3_close(DB);
};
void Data_Base::Zip_box(Figure* figure)
{
	box = new Coordinates[3 +figure->point.size() + figure->s_point.size()];
	Coordinates number(figure->point.size(), figure->s_point.size()),
		delta(figure->d_angle, figure->d_step, figure->d_zoom);
	if(figure->selected)
		number.z = 1;

	box[0] = number;
	box[1] = delta;
	box[2] = figure->color;

	for(int i(0); i < (int)number.x; i++)
		box[3 + i] = figure->point[i];

	for(int i(0); i < (int)number.y; i++)
		box[3+(int)number.x + i] = figure->s_point[i];
};
Figure* Data_Base::UnZip_box()
{
	Figure* temp = new Figure();

	temp->selected = box[0].z;
	temp->d_angle = box[1].x;
	temp->d_step = box[1].y;
	temp->d_zoom = box[1].z;
	temp->color = box[2];

	for(int i(0); i < (int)box[0].x; i++)
		temp->point.push_back(box[3 + i]);

	for(int i(0); i < (int)box[0].y; i++)
		temp->s_point.push_back(box[3+(int)box[0].x + i]);

	temp->centre = temp->find_Centre();

	return temp;
};