/**
* Seasoning
* (C) Copyright 2015 @Martin@
* mbr 27.07.2015 18:45:44
*/
// TODO insertexports here

extern "C" {
	__declspec(dllexport) void funSeasoning();

}


#define M(x) L##x
#define X(x) L#x

#define COPY L"(C) Copyright 2015 @Martin@"

#ifdef _DEBUG
#define L(x,y,z) L"@(#)DEBUG:  " M(x) L" "  M(y) L" MSC:" X(z) L" Seasoning.dll" COPY
#else
#define L(x,y,z) L"@(#)RELEASE:" M(x) L" "  M(y) L" MSC:" X(z) L" Seasoning.dll" COPY
#endif

static wchar_t * p = L(__DATE__, __TIME__, _MSC_FULL_VER);

class Seasoning {
public:
	const wchar_t * what;
	Seasoning(const wchar_t* what) : what(what) {

	}
};

Seasoning varSeasoning(p);

__declspec(dllexport) void funSeasoning() {}


