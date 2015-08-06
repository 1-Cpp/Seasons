#pragma once
#include "October/Reader.h"

namespace Seasons
{

class String;
class LineReader :
	public Reader
{
public:

	LineReader()
	{
	}

	virtual ~LineReader()
	{
	}



	virtual int readLine(String&outLine) = 0 ;
};

}
