#include "October/DataWriter.h"
#include "October/Data.h"


DataWriter::DataWriter(Data&outData):data(outData)
{
}


DataWriter::~DataWriter()
{
}

int DataWriter::write(int element) {
	if (data.size() <= position + 1)
		data.resize(data.size() + 512);
	data.setByteAt(position++, (byte)element);
	if (position > fileEnd) {
		fileEnd = position;
	}
	return 1;
}
int DataWriter::write(unsigned char buffer[], unsigned long offset, unsigned long count) {
	if (data.size() <= position + count)
		data.resize(data.size() + count + 512);
	data.setBytesAt(position, &buffer[offset], count);
	position += count;
	if (position > fileEnd)
		fileEnd = position;
	return count;
}
void DataWriter::flush() {
	
	data.resize(fileEnd);
}
