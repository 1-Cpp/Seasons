#include <Windows.h>

#include "October/File.h"
#include "October/Data.h"

namespace Seasons
{

int File::readAll(Data & data)
{
	WIN32_FILE_ATTRIBUTE_DATA info;
	FILE * fp = nullptr;
	GetFileAttributesEx((const wchar_t*)path, GetFileExInfoStandard, &info);
	if (_wfopen_s(&fp, (const wchar_t*)path, L"rb"))
		throw IOException();
	data = Data(nullptr, info.nFileSizeLow);
	
	int ret = fread(data.pointer(0), 1, info.nFileSizeLow,fp);
	data.resize(ret);
	return ret;
}

int File::readAll(File&file,Data & data)
{
	return file.readAll(data);
}

File::File(const String & path) : path(path)
{
}


File::File(const File & file)
{
}

File::~File()
{
}

}
