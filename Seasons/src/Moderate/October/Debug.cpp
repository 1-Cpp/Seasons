#include "October/Debug.h"

#include <stdarg.h>
#include <stdio.h>

#pragma comment(lib,"kernel32.lib")
extern "C"
{
__declspec(dllimport)
void
__stdcall
OutputDebugStringW(
	_In_opt_ wchar_t* lpOutputString
	);
}



namespace Seasons
{
	int debugOut(wchar_t*format, ...)
	{
		wchar_t * buffer = new wchar_t[4096];
		//String str;
		va_list list;
		va_start(list, format);

		int ret = vswprintf_s(buffer, 4096, format,list);
		va_end(list);
		buffer[ret] = 0;
		OutputDebugStringW(buffer);
		delete buffer;
		return ret;
	}


}
