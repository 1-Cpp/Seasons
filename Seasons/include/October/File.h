#pragma once
#include "October/String.h"
class Data;
class File
{
public:
	String path;
	int readAll(Data&data);
	static int readAll(File & file, Data & data);
	File(const String& path);
	
	File(const File&file);
	virtual ~File();
};

