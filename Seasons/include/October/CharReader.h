#pragma once
#include "Reader.h"

namespace Seasons
{

class CharReader :
	public Reader
{
public:

	CharReader()
	{
	}

	virtual ~CharReader()
	{
	}
	// reads count characters from stream and places them at offset in buffer
	virtual long read(wchar_t buffer[], unsigned long offset, unsigned long count) = 0;

};

}
