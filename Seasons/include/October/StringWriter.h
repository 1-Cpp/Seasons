#pragma once
#include "CharWriter.h"
class String;
class StringWriter :
	public CharWriter
{
protected:
	String & buffer;
	long position = 0;
public:
	StringWriter(String&out);
	virtual ~StringWriter();
	virtual void write(wchar_t buffer[], unsigned long offset, unsigned long count);
	virtual void write(const String&str);
};

