#pragma once

#include "October/ArrayList.h"

namespace Seasons
{

	template<class TYPE> class Stack : protected ArrayList<TYPE>
	{
		int & length = ArrayList<TYPE>::length;
		TYPE * & theArray = ArrayList<TYPE>::theArray;
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
			if (ArrayList<TYPE>::sizeAllocated <= length)
			{
				ArrayList<TYPE>::reallocateTo(ArrayList<TYPE>::sizeChunk);
			}
			theArray[length] = value;
			length++;
		}

	};

}

