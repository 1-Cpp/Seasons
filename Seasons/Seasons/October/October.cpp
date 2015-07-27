/**
  * October
  * (C) Copyright 2015 @Martin@ 
  * mbr 27.07.2015 09:59:08
  */
#include "October.h"

#define M(x) L##x
#define X(x) L#x

#define COPY L"(C) Copyright 2015 @Martin@"

#ifdef _DEBUG
#define L(x,y,z) L"@(#)DEBUG:  " M(x) L" "  M(y) L" MSC:" X(z) L" October.lib" COPY
#else
#define L(x,y,z) L"@(#)RELEASE:" M(x) L" "  M(y) L" MSC:" X(z) L" October.lib" COPY
#endif


wchar_t * pszOctober = L(__DATE__,__TIME__,_MSC_FULL_VER) ;

October whatOctober(pszOctober) ;
