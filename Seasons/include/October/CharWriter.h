#pragma once
#include "Writer.h"


namespace Seasons
{

class CharWriter :
	public Writer
{
public:

	CharWriter()
	{
	}

	virtual ~CharWriter()
	{
	}
	virtual void write(wchar_t buffer[], unsigned long offset, unsigned long count) = 0;
};

}
