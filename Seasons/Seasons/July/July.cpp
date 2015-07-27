/**
  * July
  * (C) Copyright 2015 @Martin@ 
  * mbr 27.07.2015 18:53:04
  */
#include "July.h"

#define M(x) L##x
#define X(x) L#x

#define COPY L"(C) Copyright 2015 @Martin@"

#ifdef _DEBUG
#define L(x,y,z) L"@(#)DEBUG:  " M(x) L" "  M(y) L" MSC:" X(z) L" July.lib" COPY
#else
#define L(x,y,z) L"@(#)RELEASE:" M(x) L" "  M(y) L" MSC:" X(z) L" July.lib" COPY
#endif


wchar_t * pszJuly = L(__DATE__,__TIME__,_MSC_FULL_VER) ;

July whatJuly(pszJuly) ;
