/**
  * December
  * (C) Copyright 2015 @Martin@ 
  * mbr 27.07.2015 18:54:37
  */
#include "December.h"

#define M(x) L##x
#define X(x) L#x

#define COPY L"(C) Copyright 2015 @Martin@"

#ifdef _DEBUG
#define L(x,y,z) L"@(#)DEBUG:  " M(x) L" "  M(y) L" MSC:" X(z) L" December.lib" COPY
#else
#define L(x,y,z) L"@(#)RELEASE:" M(x) L" "  M(y) L" MSC:" X(z) L" December.lib" COPY
#endif


wchar_t * pszDecember = L(__DATE__,__TIME__,_MSC_FULL_VER) ;

December whatDecember(pszDecember) ;
