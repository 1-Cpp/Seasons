#pragma once

#include "September/FieldObject.h"
#include "September/Field.h"

namespace Seasons
{

class FieldAssoc
{
protected:
	Field descriptor;
	FieldObject * theObject;
public:
	FieldAssoc();
	virtual ~FieldAssoc();
};

}
