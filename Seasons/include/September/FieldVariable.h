#pragma once
#include "October/String.h"
class FieldObject;

class FieldVariable
{
protected:
	String nameSpace;
	String name;
	FieldObject * theObject;
public:
	FieldVariable();
	virtual ~FieldVariable();
};

