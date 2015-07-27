#pragma once

class Reader;
class Field;
class Writer;
class FieldObject {
	virtual int read(Reader&reader, const Field&field) = 0;
	virtual int write(Writer&writer, const Field&field) = 0;
};
