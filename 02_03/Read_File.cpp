#include "stdafx.h"
#include "Read_File.h"
#include <iostream>
#include <fstream>
#include "string"

using namespace std;

Read_File::Read_File(string _file_name)
{
	line = 0;
	column = 0;
	file_name = new string(_file_name);
	read_file = new ifstream(file_name->c_str());
	if (!read_file->is_open())
		cerr << "Error";
}
Read_File::~Read_File()
{
	read_file->close();
	delete read_file;
	delete file_name;
}

//переделать
void Read_File::set_line()
{
	char *c = new char[9400];
	//line = 0;
	while (!read_file->eof())
	{
		read_file->getline(c, 9400);
		line++;
	}
	read_file->clear();
	reset();
	delete c;
};

void Read_File::set_column()
{
	char c;
	//column = 0;
	do
	{
		read_file->get(c);
		if (c == ' ') column++;
	} while (c != '\n');

	read_file->clear();
}

void Read_File::reset()
{
	read_file->close();
	delete read_file;
	read_file = new ifstream(file_name->c_str());
}

int Read_File::get_line()
{
	if (line == 0) set_line();
	return line;
}
int Read_File::get_column()
{
	if (column == 0) set_column();
	return column;
}
ifstream* Read_File::get_file()
{
	return read_file;
}
