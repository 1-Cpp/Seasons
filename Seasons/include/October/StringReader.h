#pragma once
#include "CharReader.h"

class String;
class StringReader :
	public CharReader
{
protected:
	unsigned long position=0;
	unsigned long markPosition=0;
	const String & buffer;
public:
	StringReader(const String & str);
	virtual ~StringReader();

	virtual unsigned int read() ;

	virtual void close() ;

	virtual bool markSupported() const ;

	virtual void setReadLimit(long readLimit) ;

	virtual void mark() ;

	virtual void reset() ;

	// skips  elements - automatically sets mark if supported
	virtual long skip(long skip) ;


	virtual long read(wchar_t buffer[], unsigned long offset, unsigned long count) ;

};

