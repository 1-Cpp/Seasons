#pragma once

typedef unsigned char byte;
class Data
{
protected:
	byte * buffer = nullptr;
	unsigned int theSize = 0 ;
public:
	Data();
	Data(const Data&data);
	Data(byte * data,unsigned int size);
	virtual ~Data();
	byte byteAt(unsigned int position) const ;
	byte * pointer(unsigned int offset) const;
	unsigned int size() const;
	void dump() const;
};

