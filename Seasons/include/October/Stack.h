#pragma once

#include "October/ArrayList.h"

namespace Seasons
{

	template<class TYPE> class Stack : protected ArrayList<TYPE>
	{
	public:
		bool isEmpty()
		{
			return ArrayList<TYPE>::isEmpty();
		}
		void clear()
		{
			ArrayList<TYPE>::clear();
		}
		TYPE pop()
		{
			if (ArrayList<TYPE>::length == 0)
				throw OutOfBoundsException();
			return ArrayList<TYPE>::theArray[--ArrayList<TYPE>::length];
		}
		TYPE peek()
		{
			if (ArrayList<TYPE>::length == 0)
				throw OutOfBoundsException();
			return ArrayList<TYPE>::theArray(ArrayList<TYPE>::length - 1);
		}
		void push(TYPE value)
		{
			if (ArrayList<TYPE>::sizeAllocated <= ArrayList<TYPE>::length)
			{
				ArrayList<TYPE>::reallocateTo(ArrayList<TYPE>::length+1);
			}
			ArrayList<TYPE>::theArray[ArrayList<TYPE>::length] = value;
			ArrayList<TYPE>::length++;
		}
		ArrayList<TYPE> & getArrayList()
		{
			return (ArrayList<TYPE>&)*this;
		}
		const ArrayList<TYPE> & getArrayList() const
		{
			return (const ArrayList<TYPE>&)*this;
		}
	};

}

