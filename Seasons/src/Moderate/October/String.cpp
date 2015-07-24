
#include "October/String.h"

class StringImpl {
protected:
	wchar_t * buffer = nullptr;
	unsigned int theSize = 0;
	unsigned int formatBuffertheSize = 4096;
public:
	StringImpl(){}
	StringImpl(const StringImpl * impl) {
		theSize = impl->theSize;
		buffer = new wchar_t[theSize + 1];
		memcpy(buffer, impl->buffer, theSize<<1 );
		buffer[theSize] = 0;
	}
	StringImpl(const wchar_t*str) {
		theSize = wcslen(str);
		buffer = new wchar_t[theSize + 1];
		if (!buffer)
			throw OutOfMemoryException();
		wcscpy_s(buffer,theSize + 1, str);
	}
	StringImpl(const wchar_t*str,unsigned int count) {
		
		buffer = new wchar_t[count + 1];
		if (!buffer)
			throw OutOfMemoryException();
		memcpy(buffer, str,count<<1);
		buffer[count] = 0;
	}
	~StringImpl() {
		if(buffer)
			delete buffer;
	}
	int vformat(const wchar_t*format, va_list list) {
		wchar_t * formatBuffer = nullptr;
		formatBuffer = new wchar_t[formatBuffertheSize];
		int ret = vswprintf_s(formatBuffer, formatBuffertheSize, format, list);
		delete buffer;
		theSize = ret;
		buffer = formatBuffer;
		return ret;
	}
	wchar_t * offset(unsigned int offset) {
		if (offset >= theSize) {
			throw OutOfBoundsException();
		}
		return &buffer[offset];
	}
	wchar_t charAt(unsigned int offset) const {
		if (offset >= theSize) {
			throw OutOfBoundsException();
		}
		return buffer[offset];
	}
	unsigned int size() const {
		return theSize;
	}
	void add(const wchar_t next) {
		// TODO optimize! introduce overlength buffer
		theSize++;
		wchar_t * newBuffer = new wchar_t[theSize + 1];
		if (buffer) {
			memcpy(newBuffer, buffer, (theSize - 1) << 1);
			delete buffer;
		}
		newBuffer[theSize - 1] = next;
		newBuffer[theSize] = 0;
		buffer = newBuffer;
	}
	void add(const StringImpl * next) {
		wchar_t * newBuffer = new wchar_t[theSize + next->theSize + 1];
		if (buffer) {
			memcpy(newBuffer, buffer, theSize << 1);
			delete buffer;
		}
		memcpy(newBuffer + theSize, next->buffer, next->theSize << 1);
		theSize += next->theSize;
		newBuffer[theSize] = 0;
		buffer = newBuffer;
	}
	std::wstring wstring() const {
		return std::wstring(buffer, theSize);
	}
	wchar_t*getBuffer() const {
		return buffer;
	}
	void setFormatBufferSize(unsigned int size) {
		formatBuffertheSize = size;
	}
};
String::String() {
	theImpl = new StringImpl();
}
String::String(const wchar_t*str){
	theImpl = new StringImpl(str);
}
String::String(const wchar_t*str,unsigned int count) {
	theImpl = new StringImpl(str,count);
}
String::String(const String&str){
	theImpl = new StringImpl(str.theImpl);
}
String::String(const std::wstring&str){
	theImpl = new StringImpl(str.c_str(),str.size());
}
String::~String()
{
	delete theImpl;
}

int String::format(const wchar_t*format, ...){
	va_list list;
	va_start(list, format);
	int ret = vformat(format, list);
	va_end(list);
	return ret;
}
int String::vformat(const wchar_t*format, va_list list){
	return theImpl->vformat(format, list);
}
String String::substr(unsigned int offset, unsigned int count){
	return String(theImpl->offset(offset),count);
}
String::operator std::wstring() const{
	return theImpl->wstring();
}
String::operator const wchar_t*() const {
	return theImpl->getBuffer();
}

wchar_t String::charAt(unsigned int offset) const
{
	return theImpl->charAt(offset) ;
}
unsigned int String::size() const {
	return theImpl->size();
}

String String::operator=(const String&toAssign) {
	if (theImpl)
		delete theImpl;
	theImpl = new StringImpl(toAssign.theImpl);
	return *this;
}
String String::operator+=(const String&toAdd) {
	theImpl->add(toAdd.theImpl);
	return *this;
}
String String::operator+=(const wchar_t&toAdd) {
	theImpl->add(toAdd);
	return *this;
}
String operator+(const String & s1, const String& s2) {
	String sum(s1);
	sum += s2;
	return sum;
}
void String::setFormatBufferSize(unsigned int size) {
	theImpl->setFormatBufferSize(size);
}