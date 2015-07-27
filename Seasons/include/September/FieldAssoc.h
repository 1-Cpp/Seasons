#pragma once

#include "September/FieldObject.h"
#include "September/Field.h"

class FieldAssoc
{
protected:
	Field descriptor;
	FieldObject * theObject;
public:
	FieldAssoc();
	virtual ~FieldAssoc();
};

