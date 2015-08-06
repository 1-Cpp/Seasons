#pragma once
#include "Writer.h"

namespace Seasons
{

class ByteWriter :
	public Writer
{

public:
	ByteWriter();
	virtual ~ByteWriter();
	virtual int write(unsigned char buffer[], unsigned long offset, unsigned long count) = 0;
	virtual void flush() = 0;
};

}
