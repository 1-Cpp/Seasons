#pragma once

#include "October/String.h"
#include "October/Data.h"
#include <vector>

class ByteReader;

class ResourceException : public Exception {
public:
	ResourceException()
	{
	}

	virtual ~ResourceException()
	{
	}
};


class VersionInfo
{
protected:
	typedef struct {
		WORD             wLength;
		WORD             wValueLength;
		WORD             wType;
		//wchar_t          szKey[1];
	} VS_RESOURCE_ENTRY_HEADER;

	VS_RESOURCE_ENTRY_HEADER header;
	String key;
	Data values;
	std::vector<DWORD> dwValues;
	std::vector<VersionInfo*> children;
	Data allData;
	Data rest;
public:
	VersionInfo();
	virtual ~VersionInfo();
	bool initFromData(ByteReader& reader);
	void dump() const ;
};

