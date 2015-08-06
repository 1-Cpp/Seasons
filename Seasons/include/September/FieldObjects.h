#pragma once

#include "FieldObject.h"

namespace Seasons
{

class FieldInt : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);
} ;

class FieldDWORD : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);
} ;


class FieldWORD : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);
} ;

class FieldLong : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);

} ;

class FieldShort : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);

} ;

class FieldChar : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);

} ;

class FieldWChar : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);

} ;

class FieldBuffer : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);

} ;

class FieldString : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);

} ;

class FieldUString : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);

} ;

class FieldStruct : public FieldObject {
	virtual int read(Reader&reader, const Field&field) ;
	virtual int write(Writer&writer, const Field&field);

} ;

}
