#pragma once
#include "Writer.h"

class ByteWriter :
	public Writer
{
public:
	ByteWriter();
	virtual ~ByteWriter();
	virtual void write(unsigned char buffer[], unsigned long offset, unsigned long count) = 0;
};

