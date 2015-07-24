#include "October/Data.h"
#include <memory.h>
#include "October/Exception.h"
#include <string>

void printHex(const void*p, int size);
Data::Data()
{
}


Data::~Data()
{
}

Data::Data(byte * data, unsigned int size) {
	this->theSize = size;
	
	buffer = new byte[size + 1];
	buffer[0] = 0;
	if(data != nullptr)
		memcpy(buffer, data,size);
	buffer[size] = 0;

}
Data::Data(const Data&data) {
	theSize = data.theSize;
	buffer = new byte[theSize + 1];
	memcpy(buffer, data.buffer, theSize);
	buffer[theSize] = 0;
}
byte Data::byteAt(unsigned int position) const {
	if (position >= theSize) {
		throw OutOfBoundsException();
	}
	return buffer[position];
}
unsigned int Data::size() const {
	return theSize;
}
byte * Data::pointer(unsigned int offset) const {
	if (offset >= theSize) {
		throw OutOfBoundsException();
	}
	return buffer + offset;
}
void Data::dump() const {
	printHex(buffer, theSize);
}
std::wstring getHex(unsigned int value) {
	std::wstring str;
	unsigned int ch = ((value % 256) / 16);
	ch = ch < 10 ? ch + L'0' : (ch - 10) + L'A';
	str += (wchar_t)ch;
	ch = value % 16;
	ch = ch < 10 ? ch + L'0' : (ch - 10) + L'A';
	str += (wchar_t)ch;
	return str;
}

void printHex(const void*p, int size) {
	wprintf(L"%p size=%d\n", p, size);
	unsigned char * byte = (unsigned char *)p;
	//unsigned char out[20];
	std::wstring out;
	std::wstring text;
	bool bFirst = true;
	for (int i = 0; i < size; ++i) {
		int j = i % 16;
		if (!bFirst && !(j % 8)) {
			text += L" ";
		}
		if (bFirst)
			bFirst = false;
		else if (!j) {
			text += L"  ";
			text += out;
			out.clear();
			wprintf(L"%s\n", text.c_str());
			text.clear();
		}
		text += getHex(byte[i]) + L" ";
		if (isprint(byte[i])) {
			out += (wchar_t)byte[i];
		}
		else
			out += L".";
	}
	int j = size % 16;
	if (j) {
		for (; j < 16; ++j) {
			if (j && !(j % 8)) {
				text += L" ";
			}
			text += L"   ";
		}
	}
	text += L"   ";
	text += out;
	wprintf(L"%s\n", text.c_str());
}

