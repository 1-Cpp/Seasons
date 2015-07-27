/**
  * Seasoning
  * (C) Copyright 2015 @Martin@
  * mbr 27.07.2015 18:45:44
  */

#include <Windows.h>
#include "October/String.h"

typedef bool(*EnumNameFun)(const wchar_t*type, int iType, const wchar_t*name, int iName, unsigned __int64 handle);
typedef bool(*EnumTypeFun)(const wchar_t*type, int iType, unsigned __int64 handle);
typedef bool(*EnumLangFun)(const wchar_t*type, int iType, const wchar_t*name, int iName, unsigned short langId,unsigned __int64 handle);

#pragma comment(lib,"October.lib")

#pragma pack(1)
typedef struct _tagResourceEntry
{
	unsigned __int64 type=1;
	unsigned __int64 name=2;
	unsigned __int16 lang=3;
	//wchar_t *		strType = L"Text" ;
	//wchar_t *		strName = L"Name";
} ResEntry;
#pragma pack()
typedef bool(__stdcall *EnumAllFun)(struct _tagResourceEntry entry, void*p);

extern "C"
{
	_declspec(dllexport) unsigned __int64 initSeasons();
	_declspec(dllexport) void freeSeasons(unsigned __int64 handle);
	_declspec(dllexport) int openResModule(unsigned __int64 handle, const wchar_t * path);
	_declspec(dllexport) void closeResModule(unsigned __int64 handle);

	_declspec(dllexport) bool enumerateTypes(unsigned __int64 handle, EnumTypeFun function);
	_declspec(dllexport) bool enumerateNames(unsigned __int64 handle, const wchar_t* type, EnumNameFun function);
	_declspec(dllexport) bool enumerateNamesInt(unsigned __int64 handle, int type, EnumNameFun function);
	_declspec(dllexport) bool enumAll(unsigned __int64 handle, EnumAllFun function, void*p);

	_declspec(dllexport) void* testNew();
	_declspec(dllexport) void testSet(void*p);

	_declspec(dllexport) bool getResourceSize(unsigned __int64 handle, void*pIn, void*pOut);
	_declspec(dllexport) bool getResource(unsigned __int64 handle, void*pIn, unsigned __int32 insize, void*pInOut);
}
_declspec(dllexport) void* testNew()
{
	return (void*)new ResEntry();
}
_declspec(dllexport) void testSet(void*p)
{
	ResEntry *pR = (ResEntry*)p;
	pR->lang = 100;
	pR->name = 200;
	pR->type = 300;
	//	pR->strName = L"Kein Name";
	//pR->strType = L"Kein Typ";
}

class Resource
{
protected:
	String text;
public:
	void * p;
	EnumAllFun fun;
	void addVersion(const wchar_t * name){}
	void addType(int type){}
	void addType(const wchar_t*type){}
	void add(...){}
	int wprintf(const wchar_t * format, ...)
	{
		String str;
		va_list list;
		va_start(list, format);
		int ret = str.vformat(format, list);
		va_end(list);
		text += str;
		return ret;
	}
	const wchar_t * getText()const
	{
		return text;
	}
};


BOOL CALLBACK EnumResLangProc(
	HMODULE  hModule,
	INT_PTR  lpszType,
	LPCTSTR  lpszName,
	WORD     wIDLanguage,
	LONG_PTR lParam
	)
{
	Resource * _this = (Resource*)lParam;
	_this->add(lpszType, lpszName, wIDLanguage);
	ResEntry entry;
	entry.lang = wIDLanguage;
	entry.name = (unsigned __int64)lpszName;
	entry.type = (unsigned __int64)lpszType;

	bool bRet = _this->fun(entry, _this->p);
	return TRUE;
}
BOOL CALLBACK EnumResNameProc(
	 HMODULE  hModule,
	 INT_PTR  lpszType,
	 LPTSTR   lpszName,
	 LONG_PTR lParam
	) {
	Resource * _this = (Resource*)lParam;
	if (IS_INTRESOURCE(lpszName)) {
		_this->wprintf(L"    %p\n", lpszName);
	}
	else
		_this->wprintf(L"    %s\n", lpszName);
	if (lpszType == 16) {
		_this->addVersion(lpszName);
	}
	BOOL bRet = EnumResourceLanguagesW(hModule, (LPCWSTR)lpszType, lpszName, (ENUMRESLANGPROCW)EnumResLangProc, (LONG_PTR) _this);
	return TRUE;
}

BOOL EnumResTypeProc(
	 HMODULE  hModule,
	 INT_PTR   lpszType,
	 LONG_PTR lParam
	) {
	
	Resource * _this = (Resource*)lParam;
	if (IS_INTRESOURCE(lpszType)) {
		_this->wprintf(L"%p\n", lpszType);
		_this->addType((int)lpszType);
	}
	else {
		_this->wprintf(L"%s\n", lpszType);
		_this->addType(lpszType);
	}
	BOOL bRet = EnumResourceNamesW(hModule, (LPCWSTR)lpszType, (ENUMRESNAMEPROCW)EnumResNameProc, lParam);

	return TRUE;
}

class Seasons {
	HMODULE hMod = nullptr;
	Resource* that;
public:
	Seasons()
	{
		that = new Resource();
	}
	~Seasons()
	{
		delete that;
	}
	bool open(const wchar_t * path) {
		hMod = LoadLibraryExW(path, nullptr, LOAD_LIBRARY_AS_DATAFILE); // _EXCLUSIVE when updating
		if (hMod)
			return true;
		return false;
	}
	void close() {
		FreeLibrary(hMod);
		hMod = nullptr;
	}
	bool enumerateTypes(EnumTypeFun fun) {
		return false;
	}
	bool enumAll(EnumAllFun fun,void *p) {
		
		that->fun = fun;
		that->p = p;
		bool bRet = EnumResourceTypesW(hMod, (ENUMRESTYPEPROCW) EnumResTypeProc, (LONG)that) ? true: false;
		DWORD dwErr = GetLastError();

		return bRet;
	}
	bool getResourceSize(void *pIn, void*pOut) {
		ResEntry *pR = (ResEntry*)pIn;
		LPCWSTR type = (LPCWSTR)pR->type;
		LPCWSTR name = (LPCWSTR)pR->name;
		HRSRC hRsrc = FindResourceEx(hMod, type, name, pR->lang);
		if (hRsrc == nullptr) {
			return false;
		}
		HGLOBAL glob = LoadResource(hMod, hRsrc);
		
		unsigned int * pi = (unsigned int *)pOut;
		*pi = SizeofResource(hMod, hRsrc);
		LPVOID p = LockResource(glob);
		return true;

	}
	bool getResource(void*pIn, unsigned __int32 insize,void *pInOut) {
		ResEntry *pR = (ResEntry*)pIn;
		LPCWSTR type = (LPCWSTR)pR->type;
		LPCWSTR name = (LPCWSTR)pR->name;
		HRSRC hRsrc = FindResourceEx(hMod, type, name, pR->lang);
		if (hRsrc == nullptr) {
			return false;
		}
		unsigned int size = SizeofResource(hMod, hRsrc);
		HGLOBAL glob = LoadResource(hMod, hRsrc);

		unsigned char * p = (unsigned char *)pInOut;
		//SizeofResource(hMod, hRsrc);
		LPVOID pResource = LockResource(glob);
		if (insize < size)
			return false;
		memcpy(p, pResource, size);
		// not implemented yet
		return true;

	}
};
_declspec(dllexport) unsigned __int64 initSeasons() {
	return (unsigned __int64)new Seasons();
}
_declspec(dllexport) void freeSeasons(unsigned __int64 handle) {
	delete (Seasons*)handle;
}


_declspec(dllexport) int openResModule(unsigned __int64 handle, const wchar_t * path)
{
	char *p = (char*)path;
	return ((Seasons*)handle)->open(path) ? 1 : 0 ;
}
_declspec(dllexport) void closeResModule(unsigned __int64 handle)
{
	((Seasons*)handle)->close();
}

_declspec(dllexport) bool enumerateTypes(unsigned __int64 handle, EnumTypeFun function)
{
	return ((Seasons*)handle)->enumerateTypes(function);
}
/*
_declspec(dllexport) bool enumerateNames(unsigned __int64 handle, const wchar_t* type, EnumNameFun function)
{
	return ((Seasons*)handle)->enmerateNames(type, function);
}
_declspec(dllexport) bool enumerateNamesInt(unsigned __int64 handle, int type, EnumNameFun function)
{
	return ((Seasons*)handle)->enumerateNames(type, function);
}
_declspec(dllexport) bool enumerateLang(unsigned __int64 handle, const wchar_t* type, const wchar_t* name, EnumLangFun function)
{
	return ((Seasons*)handle)->enmerateLang(type,name, function);
}
_declspec(dllexport) bool enumerateLangInt(unsigned __int64 handle, int type, int name,EnumLangFun function)
{
	return ((Seasons*)handle)->enumerateLang(type,name, function);
}*/
_declspec(dllexport) bool enumAll(unsigned __int64 handle, EnumAllFun function,void*p)
{
	return ((Seasons*)handle)->enumAll(function,p);
}
_declspec(dllexport) bool getResourceSize(unsigned __int64 handle,void*pIn,void*pOut)
{
	return ((Seasons*)handle)->getResourceSize(pIn,pOut);
}
_declspec(dllexport) bool getResource(unsigned __int64 handle, void*pIn, unsigned __int32 insize,void*pInOut)
{
	return ((Seasons*)handle)->getResource(pIn, insize, pInOut);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

