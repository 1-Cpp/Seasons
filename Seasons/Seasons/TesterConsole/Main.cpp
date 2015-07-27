/**
* mbr $DATE$ $TIME$
* version 1.0.2015.1
*/

#include "Main.h"

Main::Main(int argc, wchar_t ** argv) {
	this->argc = argc;
	this->argv = argv;
	if (*argv) {
		name = *argv;
	}

}

bool Main::evalArgs(int argc, wchar_t ** argv) {
	this->argc = argc;
	this->argv = argv;
	if (*argv) {
		name = *argv;
	}
	return evalArgs();
}
bool Main::evalArgs() {
	int a_argc = argc;
	wchar_t ** a_argv = argv;
	while (--a_argc) {
		++a_argv;
		int count = evalOpts(a_argc, a_argv);
		if (count) {
			a_argc -= count;
			a_argv += count;
		}
		else {
			evalParam(*a_argv);
		}
	}
	return true;
}
int Main::run() {
	// TODO here goes your program functionality
	if (arguments.empty()) {
		errorMsg = L"missing parameters\n";
		help();
	}
	return 0;
}
void Main::help() {
	wprintf(L"%s%s Version %s \n", errorMsg.c_str(), name.c_str(),getVersionString().c_str());
}
// TODO implement a resource inquiry
std::wstring Main::getVersionString() {
	return L"1.0";
}
bool Main::isOpt(wchar_t * arg, std::wstring & option) {
	for (int i = 0; optionStart[i] != nullptr; ++i) {
		if (!wcscmp(arg, optionStart[i])) {
			option = arg + wcslen(optionStart[i]);

			return true;
		}
	}
	return false;
}
int Main::evalOpts(int argc, wchar_t**argv) {
	std::wstring option;
	if (isOpt(*argv, option)) {
		// TODO set flags and process additional option parameters

		// TODO return 1 + number plus count of additional option parameterss
		return 1;
	}
	return 0;
}
bool Main::evalParam(wchar_t* arg) {
	arguments.insert(arguments.end(), std::wstring(arg));
	return true;
}
