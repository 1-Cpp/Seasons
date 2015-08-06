#include "October/StringReader.h"
#include "October/String.h"

namespace Seasons
{

StringReader::StringReader(const String& str) : buffer(str)
{

}


StringReader::~StringReader()
{
}

unsigned int StringReader::read(){
	if (position >= buffer.size())
		return -1;
	return buffer.charAt(position++);
}

void StringReader::close(){
}

bool StringReader::markSupported() const{
	return true;
}

void StringReader::setReadLimit(long readLimit){
	throw UnsupportedOperationException();
}

void StringReader::mark(){
	markPosition = position;
}

void StringReader::reset(){
	position = markPosition;
}


long StringReader::skip(long skip){
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


long StringReader::read(wchar_t buffer[], unsigned long offset, unsigned long count){
	unsigned long copy = count;
	if (position >= this->buffer.size())
		return -1;
	if (position + count >= this->buffer.size()) {
		copy = this->buffer.size() - position;
	}
	wmemcpy(buffer, (wchar_t*)buffer, copy);
	return copy;
}

}
