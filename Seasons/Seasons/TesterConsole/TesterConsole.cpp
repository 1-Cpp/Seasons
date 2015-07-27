/**
* mbr $DATE$ $TIME$
*/
#include <Windows.h>
#include "Main.h"
#include "January/DSCReader.h"
#include "October/File.h"
#include "October/Data.h"
#pragma pack(1)
typedef struct _tagResourceEntry
{
	unsigned __int64 type = 1;
	unsigned __int64 name = 2;
	unsigned __int16 lang = 3;
	//wchar_t *		strType = L"Text" ;
	//wchar_t *		strName = L"Name";
} ResEntry;
#pragma pack()
typedef bool(__stdcall *EnumAllFun)(struct _tagResourceEntry entry, void*p);

std::string getResTypeName(int Type)
{

	const int XRT_ACCELERATOR = 9; //Accelerator table.
	const int XRT_ANICURSOR = 21; //Animated cursor.
	const int XRT_ANIICON = 22; //Animated icon.
	const int XRT_BITMAP = 2; //Bitmap resource.
	const int XRT_CURSOR = 1; //Hardware-dependent cursor resource.
	const int XRT_DIALOG = 5; //Dialog box.
	const int XRT_DLGINCLUDE = 17; //Allows
	const int XRT_FONT = 8; //Font resource.
	const int XRT_FONTDIR = 7; //Font directory resource.
	const int XRT_GROUP_CURSOR = ((XRT_CURSOR)+11); //Hardware-independent cursor resource.

	const int XRT_HTML = 23; //HTML resource.
	const int XRT_ICON = 3; //Hardware-dependent icon resource.
	const int XRT_MANIFEST = 24; //Side-by-Side Assembly Manifest.
	const int XRT_MENU = 4; //Menu resource.
	const int XRT_MESSAGETABLE = 11; //Message-table entry.
	const int XRT_PLUGPLAY = 19; //Plug and Play resource.
	const int XRT_RCDATA = 10; //Application-defined resource (raw data).
	const int XRT_STRING = 6; //String-table entry.
	const int XRT_VERSION = 16; //Version resource.
	const int XRT_VXD = 20; //
	const int XRT_DLGINIT = 240;
	const int XRT_TOOLBAR = 241;

	const int XRT_GROUP_ICON = ((XRT_ICON)+11); //Hardware-independent icon resource.

	std::string ret;
	switch ((int)Type)
	{
	case XRT_ACCELERATOR:
		ret = "XRT_ACCELERATOR";
		break;
	case XRT_ANICURSOR:
		ret = "XRT_ANICURSOR";
		break;
	case XRT_ANIICON:
		ret = "XRT_ANIICON";
		break;
	case XRT_BITMAP:
		ret = "XRT_BITMAP";
		break;
	case XRT_CURSOR:
		ret = "XRT_CURSOR";
		break;
	case XRT_DIALOG:
		ret = "XRT_DIALOG";
		break;
	case XRT_DLGINCLUDE:
		ret = "XRT_DLGINCLUDE";
		break;
	case XRT_FONT:
		ret = "XRT_FONT";
		break;
	case XRT_FONTDIR:
		ret = "XRT_FONTDIR";
		break;
	case XRT_GROUP_CURSOR:
		ret = "XRT_GROUP_CURSOR";
		break;
	case XRT_GROUP_ICON:
		ret = "XRT_GROUP_ICON";
		break;
	case XRT_HTML:
		ret = "XRT_HTML";
		break;
	case XRT_ICON:
		ret = "XRT_ICON";
		break;
	case XRT_MANIFEST:
		ret = "XRT_MANIFEST";
		break;
	case XRT_MENU:
		ret = "XRT_MENU";
		break;
	case XRT_MESSAGETABLE:
		ret = "XRT_MESSAGETABLE";
		break;
	case XRT_PLUGPLAY:
		ret = "XRT_PLUGPLAY";
		break;
	case XRT_RCDATA:
		ret = "XRT_RCDATA";
		break;
	case XRT_STRING:
		ret = "XRT_STRING";
		break;
	case XRT_VERSION:
		ret = "XRT_VERSION";
		break;
	case XRT_VXD:
		ret = "XRT_VXD";
		break;
	case XRT_DLGINIT:
		ret = "XRT_DLGINIT";
		break;
	case XRT_TOOLBAR:
		ret = "XRT_TOOLBAR";
		break;
	default:
		ret = "Unbekannt";
		break;
	}
	return ret;
}


typedef unsigned __int64(*InitSeasons)();
typedef void(*FreeSeasons)(unsigned __int64 handle);
typedef bool(*OpenResModule)(unsigned __int64 handle, const wchar_t * path);
typedef void(*CloseResModule)(unsigned __int64 handle);
typedef bool(*EnumAll)(unsigned __int64 handle, EnumAllFun function, void*p);


static bool __stdcall proc(ResEntry entry, void*p)
{
	if (entry.name > 0x00010000)
		wprintf(L"%08.8x <%s>", (unsigned int)entry.name, (wchar_t*)entry.name);
	else
		wprintf(L"%d", (int)entry.name);
	printf("   ");
	if (entry.type > 0x00010000)
		wprintf(L"%08.8x <%s>", (unsigned int)entry.type, (wchar_t*)entry.type);
	else
		wprintf(L"[%S]", getResTypeName((int)entry.type).c_str());
	printf("\n");
	return true;
}

class TesterConsole : public Main {
	HMODULE hMod = nullptr;
	unsigned __int64 handle = 0;
	
	unsigned __int64 (*initSeasons)();
	void (*freeSeasons)(unsigned __int64 handle);
	bool (*openResModule)(unsigned __int64 handle, const wchar_t * path);
	void (*closeResModule)(unsigned __int64 handle);
	bool (*enumAll)(unsigned __int64 handle, EnumAllFun function, void*p);





public:
	void prepare() {
		hMod = LoadLibrary(L"d:\\Source\\1-cpp\\Seasons\\Debug\\Seasoning.dll");
		initSeasons = (InitSeasons)GetProcAddress(hMod, "initSeasons");
		freeSeasons = (FreeSeasons)GetProcAddress(hMod, "freeSeasons");
		openResModule = (OpenResModule)GetProcAddress(hMod, "openResModule");
		closeResModule = (CloseResModule)GetProcAddress(hMod, "closeResModule");
		enumAll= (EnumAll)GetProcAddress(hMod, "enumAll");
		
	}
	void cleanup()	{
		FreeLibrary(hMod);
		hMod = nullptr;
	}
	int run() {
		if (arguments.size() < 1) {
			help();
			return 1;
		}

		prepare();
		std::wstring path = arguments[0];
		handle = initSeasons();
		openResModule(handle,path.c_str());
		enumAll(handle, proc, this);
		closeResModule(handle);
		freeSeasons(handle);
		cleanup();
		return 0;
	}
} ;
#pragma comment(lib,"October.lib")
//#pragma comment(lib,"Cold.lib")

class SeasonTester : public Main {

public:
	int run() {
		Data data;
		File file(L"d:\\Source\\1-cpp\\Seasons\\res\\March\\resource.dsc");
		file.readAll(data);
		DSCReader reader(data);
		reader.parse();
		return 0;
	}
};
int wmain(int argc, wchar_t ** argv) {
	SeasonTester program;
  
	if(program.evalArgs(argc,argv) ) {
		return program.run();
	}
	else {
		program.help();
	}
	return 0;
}
