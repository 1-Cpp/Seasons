/**
  * @Martin@
  * mbr 27.07.2015 09:13:53 
  * mbr $DATE$ $TIME$
  * (C) Copyright 2015 @Martin@
  *
  */
  
//#include "TesterOctober.h"

#include "Main.h"


#define M(x) L##x
#define X(x) L#x

#define COPY L"(C) Copyright @Martin@"

#ifdef _DEBUG
#define L(x,y,z) L"@(#)DEBUG:  " M(x) L" "  M(y) L" MSC:" X(z) L" TesterOctober.exe" COPY
#else
#define L(x,y,z) L"@(#)RELEASE:" M(x) L" "  M(y) L" MSC:" X(z) L" TesterOctober.exe" COPY
#endif

static wchar_t * p = L(__DATE__,__TIME__,_MSC_FULL_VER) ;

class TesterOctober : public Main {
public:
  int run() {
  // TODO write your code here
  return 0;
  }
};

int wmain(int argc, wchar_t ** argv) {
	TesterOctober program;
  
	if(program.evalArgs(argc,argv) ) {
		return program.run();
	}
	else {
		program.help();
	}
	return 0;
}
