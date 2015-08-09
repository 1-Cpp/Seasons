#pragma once


#include "October/BaseArrayList.h"


namespace Seasons
{

	template<typename TYPE> class ArrayList : public BaseArrayList<TYPE>
	{
	protected:
	public:
		virtual ~ArrayList()
		{

		}
		void add(const TYPE &value)
		{
			if (sizeAllocated <= length)
				reallocateTo(sizeAllocated + sizeChunk);
			theArray[length] = value;
			length++;
		}
		void add(const ArrayList<TYPE>& ar)
		{
			BaseArrayList<TYPE>::add((const BaseArrayList<TYPE>&)ar);
		}
		void set(int index, const TYPE&value)
		{
			if (index >= 0 && index < length)
			{
				theArray[index] = value;
			}
			else
			{
				throw OutOfBoundsException();
			}
		}
		void insert(int index, const TYPE& value)
		{
			reserve(length + 1);
			for (int i = length; i > index; --i)
			{
				theArray[i] = theArray[i - 1];
			}
			length++;
			theArray[index] = value;
		}
		ArrayList<TYPE>& operator=(const BaseArrayList<TYPE>&otherArray)
		{
			clear();
			add(otherArray);
			return *this;
		}
		bool operator==(const BaseArrayList<TYPE>&otherArray)
		{
			if (length != otherArray.length)
				return false;
			for (int i = 0; i < length; ++i)
			{
				if (theArray[i] != otherArray.theArray[i])
					return false;
			}
			return true;
		}
		bool operator!=(const BaseArrayList<TYPE>&otherArray)
		{
			if (length != otherArray.length)
				return true;
			for (int i = 0; i < length; ++i)
			{
				if (theArray[i] != otherArray.theArray[i])
					return true;
			}
			return false;
		}
		bool operator <(const BaseArrayList<TYPE>&otherArray)
		{
			int count = min(length, otherArray->length);
			for (int i = 0; i < count; ++i)
			{
				if (theArray[i] < otherArray.theArray[i])
					return true;
				if (theArray[i] == otherArray.theArray[i])
					continue;
				else
					return false;
			}
			if (count < otherArray.length)
				return true;
			return false;
		}
	protected:
	};

}





