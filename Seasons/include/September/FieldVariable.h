#pragma once
#include "October/String.h"


namespace Seasons
{

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

}
