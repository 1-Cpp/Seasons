#pragma once
#include "October/String.h"
#include "September/FieldObject.h"

class Field : public FieldObject {
protected:
	String name;
	unsigned int sizeBytes = 0;
	unsigned int sizeBits = 0;
	bool isLittleEndian = true;
public:
	Field();
	virtual ~Field();
	virtual int read(Reader&reader, const Field&field);
	virtual int write(Writer&writer, const Field&field);
};

