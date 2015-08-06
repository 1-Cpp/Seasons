#pragma once
#include "October/ByteWriter.h"

namespace Seasons
{
	class IconData;
	class IcoFileWriter :
		public ByteWriter
	{
		int baseOffset = 0;
		int currentOffset = 0;
	public:
		IcoFileWriter();
		virtual ~IcoFileWriter();
		virtual int writeHeader(int count, bool isCursor);
		virtual int writeEntry(const IconData&icon);
		virtual int writeDirectory(int count, const IconData icons[]);
		virtual int write2bytes(unsigned int what);
		virtual int write4bytes(unsigned int what);
	};

}
