#pragma once

#include "October/ArrayList.h"
#include "October/Algorithms.h"

namespace Seasons
{
	template<class TYPE,typename COMPARATOR=less<TYPE>> class SortedArrayList : public BaseArrayList<TYPE>
	{
	public:
		COMPARATOR comparator;
		void add(const BaseArrayList<TYPE>& ar)
		{
			reserve(length + ar.length);
			for (int  j = 0; j < ar.length; j++)
			{
				insert(ar.theArray[j]);
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
			reserve(length + 2);
			for (int i = length; i > index; --i)
			{
				theArray[i] = theArray[i - 1];
			}
			length++;
			theArray[index] = value;

		}
		SortedArrayList<TYPE>& operator=(const BaseArrayList<TYPE>&otherArray)
		{
			clear();
			add(otherArray);
			return *this;
		}

	};
}
