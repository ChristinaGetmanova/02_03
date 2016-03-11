#pragma once
#include <string>

class Read_File
{
public:
	Read_File(std::string);
	~Read_File();
	void set_line();
	void set_column();
	void reset();
	int get_line();
	int get_column();
	std::ifstream *get_file();
private:
	std::ifstream *read_file;
	int line, column;
	std::string *file_name;;
};

