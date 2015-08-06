#pragma once
#include "Reader.h"

namespace Seasons
{

class ByteReader : public Reader
{
public:

	ByteReader()
	{
	}

	virtual ~ByteReader()
	{
	}
	// reads count bytes from stream and places them at offset in buffer
	virtual unsigned int read(unsigned char buffer[], unsigned long offset, unsigned long count) = 0;
};

}
