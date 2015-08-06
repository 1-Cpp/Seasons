#include "July/IcoFileWriter.h"

#include "July/IconData.h"

namespace Seasons
{

IcoFileWriter::IcoFileWriter()
{
}


IcoFileWriter::~IcoFileWriter()
{
}


int IcoFileWriter::writeHeader(int count,bool isCursor)
{
	Writer::write(0);
	Writer::write(0);

	Writer::write(count & 0x0000FF);
	Writer::write(count >> 8 & 0x0000FF);

	Writer::write(isCursor ? 2 : 1);
	Writer::write(0);
	baseOffset = 6 + count * 16;
	currentOffset = baseOffset;
	return 6;
}
int IcoFileWriter::writeEntry(const IconData&iconData)
{
	
	Writer::write(iconData.width);
	Writer::write(iconData.height);
	Writer::write(iconData.paletteColorCount);
	Writer::write(0);
	Writer::write(iconData.colorPlanes & 0x0000FF);// cursor x of hotspot
	Writer::write(iconData.colorPlanes >> 8 & 0x0000FF);// cursor x of hotspot
	Writer::write(iconData.bitsPerPixel & 0x0000FF); // cursor: y of hotspot
	Writer::write(iconData.bitsPerPixel >> 8 & 0x0000FF); // cursor: y of hotspot
	write4bytes(iconData.dataSize);
	write4bytes(currentOffset);
	currentOffset += iconData.dataSize;
	return 16;
}
int IcoFileWriter::write2bytes(unsigned int what)
{
	Writer::write(what & 0x0000FF);
	Writer::write(what >> 8 & 0x0000FF);
	return 2;
}
int IcoFileWriter::write4bytes(unsigned int what)
{
	Writer::write(what & 0x0000FF);
	Writer::write(what >> 8 & 0x0000FF);
	Writer::write(what >> 16 & 0x0000FF);
	Writer::write(what >> 24 & 0x0000FF);
	return 4;
}

int IcoFileWriter::writeDirectory(int count, const IconData icons[])
{
	int ret = writeHeader(count, false);

	for (int i = 0; i < count; i++)
	{
		int iRet= writeEntry(icons[i]);

		ret += iRet;
	}
	return ret;
}

}
