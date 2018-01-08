#ifndef DATABASE_H_
#define DATABASE_H_

#include "sqlite3.h"

#include "Figure.h"

class Data_Base
{
	char* path;
	sqlite3* DB;
	sqlite3_stmt* statement;
	char* SQL;
	void Create();
	void Delete();
public:
	Coordinates* box; //temporary storage for Figure
	//------------------------------------------
	// 0 - numbers; 1 - delta
	// 2 - color;
	// 3.. - point; ..4 - s_point;
	//------------------------------------------

	void Zip_box(Figure*);
	Figure* UnZip_box();
	void Release_memory();

	Data_Base(char*);

	void Download(std::vector<Figure*>&);
	void Insert(const std::vector<Figure*>&);
};

extern Data_Base DATA;

#endif //DATABASE_H_