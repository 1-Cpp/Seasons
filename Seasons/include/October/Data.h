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
	void setByteAt(unsigned int position, byte value);
	void setBytesAt(unsigned int position, byte value[], unsigned int count);
	unsigned int size() const;
	void resize(int newSize);
	void dump() const;
};

