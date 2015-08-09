#pragma once

#include "October/ArrayList.h"
#include "October/Algorithms.h"

namespace Seasons
{
	template<class TYPE,typename COMPARATOR=less<TYPE>> class SortedArrayList : public BaseArrayList<TYPE>
	{
	public:
		using BaseArrayList<TYPE>::theArray;
		using BaseArrayList<TYPE>::sizeAllocated;
		using BaseArrayList<TYPE>::sizeChunk;
		using BaseArrayList<TYPE>::length;
		COMPARATOR comparator;
		void add(const BaseArrayList<TYPE>& ar)
		{
			BaseArrayList<TYPE>::reserve(length + ar.length);
			for (int  j = 0; j < ar.length; j++)
			{
				insert(ar.get(j));
			}
		}

		void insert(const TYPE &value)
		{
			int index = length;
			for (int i = 0; i < length; ++i)
			{
				if (comparator(value, theArray[i]))
				{
					index = i;
					break;
				}
			}
			BaseArrayList<TYPE>::reserve(length + 2);
			for (int i = length; i > index; --i)
			{
				theArray[i] = theArray[i - 1];
			}
			length++;
			theArray[index] = value;

		}
		SortedArrayList<TYPE>& operator=(const BaseArrayList<TYPE>&otherArray)
		{
			BaseArrayList<TYPE>::clear();
			add(otherArray);
			return *this;
		}

	};
}
