/**
  * mbr $DATE$ $TIME$
  * mbr 27.07.2015 09:13:53
  * (C) Copyright 2015 @Martin@
  *
  * version 1.0.2015
  */
#include <string>
#include <vector>
#include <tchar.h>

/**
 * Main class - implements parameter evaluation
 * derive from this class to implement your functionality
 */
class Main {

protected:
	/**
	 * after parameter evaluation this property holds the name of the program as passed in the command
	 *
	 */
	std::wstring name;

	/**
	  * after parameter evaluation this holds all arguments which are not identified as option
	  *
	  */
	std::vector<std::wstring> arguments;

	/**
	* after parameter evaluation this holds all the set option flags
	*
	*/
	std::vector<std::wstring> optionFlags;

	/**
	 * all the character combinations which mark an option
	 *
	 *
	 **/
	const wchar_t * optionStart[4] = {
		L"--", L"-",L"/",nullptr
	};

	std::wstring errorMsg = L"";


	int argc = 0;
	wchar_t ** argv = nullptr;
public:
	Main() {}
	Main(int argc, wchar_t ** argv);

	/**
	* evaluates arguments and determines if this parameter is an option
	* @return true if successful - otherwise false
	*/
	bool evalArgs();

	/** 
	* evaluates arguments and determines if this parameter is an option
	* 
	* @param argc argument count as passed in main or wmain 
	* @param argv array of arguments as passed in main or wmain
	*
	* @return true if successful - otherwise false
	* 
	*/
	bool evalArgs(int argc, wchar_t ** argv);

	/**
	*
	* runs program - override a derived class to implement your function
	* @return exit code of your program
	*/
	int run();

	/**
	  * override to display a help text
	  */
	void help();
protected:
	/**
	  * determines whether this argument is an option
	  * @param arg the argument to process
	  * @param option holds the found option if any
	  * 
	  * @return true when option is found otherwise false
	  * override to implement your options
	  */
	virtual bool isOpt(wchar_t * arg, std::wstring & option);
	virtual std::wstring getVersionString();
protected:
	int evalOpts(int argc, wchar_t**argv);
	bool evalParam(wchar_t* arg);

};
