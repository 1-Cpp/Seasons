#include <Windows.h>
#include "October/Reader.h"
#include "July/VersionInfo.h"
#include "October/Data.h"
#include "October/DataReader.h"
#include "October/String.h"

VersionInfo::VersionInfo()
{
}


VersionInfo::~VersionInfo()
{
}

class WrapperReader : public ByteReader {
protected:
	ByteReader&theReader;
public:
	WrapperReader(ByteReader & reader) : theReader(reader) {

	}
	virtual unsigned int read() {
		return ((Reader&)theReader).read();
	}
	virtual unsigned int read(byte buffer[], unsigned long offset, unsigned long count) {
		return theReader.read(buffer, offset, count);
	}
	void close() { }

	bool markSupported() const { return theReader.markSupported(); }

	void setReadLimit(long readLimit) { theReader.setReadLimit(readLimit); }

	void mark() { theReader.mark(); }

	void reset() { theReader.reset(); }

	long skip(long skip) { return theReader.skip(skip); }

	long align(long boundary) {
		return theReader.align(boundary);
	}
	
	unsigned int readString(String&ret) {
		String empty;
		unsigned int readCount = 0;
		wchar_t ch = 0;
		do {
			
			unsigned int red = read((byte*)&ch, 0, sizeof(ch));
			if (red == -1)
				throw ResourceException();
			if(ch)
				empty += ch;
			readCount += red;

		} while (ch != 0);
		ret = empty;
		return readCount;
	}
};
/*
&& !(header.wValueLength % 4)) {
int count = header.wValueLength / 4;
for (int i = 0; i < count; ++i) {
DWORD dw = 0;
red += reader.read((byte*)&dw,0,sizeof(dw));
dwValues.insert(dwValues.end(), dw);
*/
bool VersionInfo::initFromData(ByteReader& versionReader)
{
	WrapperReader reader(versionReader);
	typedef unsigned int uint;
	uint red = 0;
	reader.align(sizeof(DWORD));
	reader.mark();
	uint ret = reader.read((unsigned char*)&header, 0, sizeof(header));
	if (ret == -1 || ret == 0)
		return false;
	red += ret;
	red += reader.readString(key);
	red += reader.align(sizeof(DWORD));
	if (header.wValueLength) {
		if (header.wType == 0) {
			this->values = Data(nullptr, header.wValueLength);
			red += reader.read(values.pointer(0), 0, header.wValueLength);
		}
		else if (header.wType == 1) {
			this->values = Data(nullptr, header.wValueLength << 1);
			red += reader.read(values.pointer(0), 0, header.wValueLength << 1);
		}
		else
			throw ResourceException();
		
	}
	if(header.wLength > red) {
		rest = Data(nullptr, header.wLength - red);
		reader.read(rest.pointer(0), 0, rest.size());
	}
	reader.reset();
	allData = Data(nullptr,header.wLength);
	reader.read(allData.pointer(0), 0, header.wLength);
	dump();
	if (rest.size()) {
		bool bContinue = false;
		DataReader childReader(rest);
		do {
			VersionInfo * pNew = new VersionInfo();
			bContinue = pNew->initFromData(childReader);
			pNew->dump();
			children.insert(children.end(),pNew);
		} while (bContinue);
	}
	return true;
}
void VersionInfo::dump() const {
	this->allData.dump();
	wprintf(L"%d ; %d ; %d\n", this->header.wLength, header.wValueLength, header.wType);

	wprintf(L"Key:<%s> Values:\n", (const wchar_t*)key);
	for (DWORD dw : this->dwValues) {
		wprintf(L"DW=%d\n", dw);
	}	
	this->values.dump();
	wprintf(L"Rest:\n");
	rest.dump();
	wprintf(L"Children %d :\n", children.size());
	for (VersionInfo * p : children) {
		p->dump();
	}

}
