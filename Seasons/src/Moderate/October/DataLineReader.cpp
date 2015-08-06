#include "October/DataLineReader.h"

#include "October/Data.h"
#include "October/Exception.h"
#include "October/String.h"

namespace Seasons
{

int DataLineReader::readLine(String & outLine)
{
	String outStr;
	unsigned char ch = 0;
	wchar_t wchar = 0;
	int count = 0;
	bool readMark = false;
	if (position == 0)
		readMark = true;
	try {
		do {
			wchar = read();
			ch = read();
			wchar |= ch << 8;
			if (readMark && (wchar == 0xfffe || wchar == 0xfeff))
				continue;
			outStr += wchar;
			count++;
		} while (wchar != 0 && wchar != L'\n');
	}
	catch (EOFException ex) {
		return 0;
	}
	outLine = outStr;
	return count;
}

DataLineReader::DataLineReader(const Data & data) : data(data)
{
}

DataLineReader::~DataLineReader()
{
}

unsigned int DataLineReader::read()
{
	if (position >= data.size())
		throw EOFException();
	return data.byteAt(position++);
}

void DataLineReader::close()
{
}

bool DataLineReader::markSupported() const
{
	return true;
}

void DataLineReader::setReadLimit(long readLimit)
{
}

void DataLineReader::mark()
{
	markPosition = position;
}

void DataLineReader::reset()
{
	position = markPosition;
}

long DataLineReader::skip(long skip)
{
	if (position >= data.size())
		throw OutOfBoundsException();
	unsigned long count = skip;
	if (position + count >= data.size()) {
		count = data.size() - position;
	}
	markPosition = position;
	position += count;
	return count;
}

unsigned int DataLineReader::read(unsigned char buffer[], unsigned long offset, unsigned long count)
{
	return 0;
}

long DataLineReader::align(long boundary)
{
	return 0;
}

}
