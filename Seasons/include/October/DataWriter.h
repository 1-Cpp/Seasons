#pragma once
#include "October/ByteWriter.h"
class Data;
class DataWriter :
	public ByteWriter
{
protected:
	Data & data;
	unsigned long position = 0;
	unsigned long fileEnd = 0;
public:
	DataWriter(Data&outData);
	virtual ~DataWriter();
	virtual int write(int element);
	virtual int write(unsigned char buffer[], unsigned long offset, unsigned long count);
	virtual void flush();
};

