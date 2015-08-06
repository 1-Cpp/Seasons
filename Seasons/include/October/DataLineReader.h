#pragma once
#include "LineReader.h"

namespace Seasons
{

class Data;
class DataLineReader :
	public LineReader
{
protected:
	unsigned long position = 0;
	unsigned long markPosition = 0;
	const Data & data;
public:
	DataLineReader(const Data & data);
	virtual ~DataLineReader();

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
	virtual int readLine(String&outLine);

};


}
