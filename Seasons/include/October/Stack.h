#pragma once

#include "October/ArrayList.h"

namespace Seasons
{

	template<class TYPE> class Stack : protected ArrayList<TYPE>
	{
	public:
		bool isEmpty()
		{
			return length == 0;
		}
		TYPE pop()
		{
			if (length == 0)
				throw OutOfBoundsException();
			return theArray[--length];
		}
		TYPE peek()
		{
			if (length == 0)
				throw OutOfBoundsException();
			return theArray(length - 1);
		}
		void push(TYPE value)
		{
			if (sizeAllocated <= length)
			{
				reallocateTo(sizeChunk);
			}
			theArray[length] = value;
			length++;
		}

	};

}

