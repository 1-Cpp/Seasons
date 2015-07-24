#pragma once
#include "ByteReader.h"

class Data;
class DataReader :
	public ByteReader
{
protected:
	unsigned long position = 0;
	unsigned long markPosition = 0;
	const Data & buffer;
public:
	DataReader(const Data & str);
	virtual ~DataReader();

	virtual unsigned int read();

	virtual void close();

	virtual bool markSupported() const;

	virtual void setReadLimit(long readLimit);

	virtual void mark();

	virtual void reset();

	// skips  elements - automatically sets mark if supported
	virtual long skip(long skip);


	virtual unsigned int read(unsigned char buffer[], unsigned long offset, unsigned long count);

	virtual long align(long boundary);

};


