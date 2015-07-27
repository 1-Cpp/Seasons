#include "October/DataReader.h"
#include "October/Data.h"
#include "October/Exception.h"
#include <memory.h>

DataReader::DataReader(const Data& str) : buffer(str)
{

}


DataReader::~DataReader()
{
}

unsigned int DataReader::read() {
	if (position >= buffer.size())
		return -1;
	return buffer.byteAt(position++);
}

void DataReader::close() {
}

bool DataReader::markSupported() const {
	return true;
}

void DataReader::setReadLimit(long readLimit) {
	throw UnsupportedOperationException();
}

void DataReader::mark() {
	markPosition = position;
}

void DataReader::reset() {
	position = markPosition;
}


long DataReader::skip(long skip) {
	long jump = 0;
	if (position >= this->buffer.size())
		return -1;
	if (((long)position + skip) < 0)
		jump = -(long)position;
	if (position + skip >= this->buffer.size()) {
		jump = buffer.size() - position;
	}
	markPosition = position;
	position += jump;
	return jump;
}

long DataReader::align(long boundary) {

	long adjust = boundary - (position%boundary);
	if (adjust == boundary)
		return 0;
	position += adjust;
	return adjust;
}
unsigned int DataReader::read(unsigned char buffer[], unsigned long offset, unsigned long count) {
	unsigned long copy = count;
	if (position >= this->buffer.size())
		return -1;
	if (position + count >= this->buffer.size()) {
		copy = this->buffer.size() - position;
	}
	memcpy(buffer, (const wchar_t*)this->buffer.pointer(position), copy);
	position += copy;
	return copy;
}