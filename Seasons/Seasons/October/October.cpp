/**
  * October
  * (C) Copyright 2015 @Martin@ 
  * mbr 27.07.2015 09:59:08
  */
#include "October.h"

#pragma comment(lib,"kernel32.lib")
extern "C"
{
	__declspec(dllimport)
		void
		__stdcall
		OutputDebugStringW(
			const wchar_t* lpOutputString
			);
}

#define M(x) L##x
#define X(x) L#x

#define COPY L"(C) Copyright 2015 @Martin@"

#ifdef _DEBUG
#define L(x,y,z) L"@(#)DEBUG:  " M(x) L" "  M(y) L" MSC:" X(z) L" October.lib " COPY
#else
#define L(x,y,z) L"@(#)RELEASE:" M(x) L" "  M(y) L" MSC:" X(z) L" October.lib " COPY
#endif


namespace Seasons
{
	wchar_t * pszOctober = L(__DATE__, __TIME__, _MSC_FULL_VER);


	October whatOctober = October(pszOctober);
	void October::print(int param)
	{
		OutputDebugStringW(param == 1 ? L"Start " : L"End   ");
		OutputDebugStringW(what);
		OutputDebugStringW(L"\r\n");
	}
}
