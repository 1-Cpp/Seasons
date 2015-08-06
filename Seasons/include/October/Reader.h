#pragma once


namespace Seasons
{

class Reader
{
public:

	Reader()
	{
	}

	virtual ~Reader()
	{
	}

	/**
	  *
	  * reads one element ( 1- 4 bytes ) - returns an unsigned int with the most signficant bytes set to zero
	  *
	  */
	virtual unsigned int read() = 0;

	virtual void close() = 0;

	virtual bool markSupported() const = 0;

	virtual void setReadLimit(long readLimit) = 0 ;
	
	virtual void mark() = 0;

	virtual void reset() = 0;

	// skips  elements - automatically sets mark if supported
	virtual long skip(long skip) = 0;

	virtual long align(long boundary) = 0;

};

}
