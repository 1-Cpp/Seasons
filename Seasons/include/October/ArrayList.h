#pragma once

#include "October/Exception.h"
#include <memory.h>

namespace Seasons
{

	template<class TYPE> class ArrayList
	{
	protected:
		void * reserved = nullptr;
		TYPE * theArray = nullptr;
		int sizeAllocated = 0;
		int sizeChunk = 2 ;
	public:
		int length = 0;
		virtual ~ArrayList()
		{
			if(theArray)
				delete [] theArray;
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
			reserve(length + ar.length);
			for (int i = length, j = 0; i < length + ar.length && j < ar.length; i++, j++)
			{
				theArray[i] = ar.theArray[j];
			}
			length += ar.length;
		}
		bool isEmpty()
		{
			return length == 0;
		}
		TYPE getLast()
		{
			if (length == 0)
				throw OutOfBoundsException();
			return theArray(length - 1);
		}
		void removeLast()
		{
			length--;
		}
		void remove(int index)
		{
			for (int i = index; i < length - 1; i++)
			{
				theArray[i] = theArray[i + 1];
			}
			length--;
		}
		void remove(int index, int count)
		{
			if (index + count > length)
				throw OutOfBoundsException();

			for (int i = index; i < length - count; i++)
			{
				theArray[i] = theArray[i + count];
			}
			resize(length - count);
		}
		int size()
		{
			return length;
		}
		TYPE & operator[](int i)
		{
			if (i >= 0 && i < length)
				return theArray[i];
			throw OutOfBoundsException();
		}
		void set(int index, const TYPE&value)
		{
			if (index >= 0 && index < length)
				theArray[index] = value;
			else
				throw OutOfBoundsException();
		}
		TYPE & get(int index)
		{
			if (index >= 0 && index < length)
				return theArray[index];
			else
				throw OutOfBoundsException();
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
		void resize(int newSize)
		{
			reserve(newSize);
			length = newSize;
		}
		void reserve(int newSize)
		{
			if (sizeAllocated < newSize)
			{
				reallocateTo(((newSize / sizeChunk) + 1)*sizeChunk);
			}
			else if (sizeAllocated > newSize + sizeChunk)
			{
				reallocateTo(((newSize / sizeChunk) + 1) * sizeChunk);
			}
		}
		void clear()
		{
			if(theArray != nullptr)
				delete [] theArray;
			theArray = nullptr;
			length = 0 ;
			sizeAllocated = 0 ;
		}
		ArrayList<TYPE>& operator=(const ArrayList<TYPE>&otherArray)
		{
			clear();
			add(otherArray);
			return *this;
		}
		bool operator==(const ArrayList<TYPE>&otherArray)
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
		bool operator!=(const ArrayList<TYPE>&otherArray)
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
		bool operator <(const ArrayList<TYPE>&otherArray)
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
		void reallocateTo(int newSize)
		{
			TYPE * newArray = new TYPE [newSize ];
			int oldSize = sizeAllocated;
			sizeAllocated = newSize;
			//memset(newArray, 0, sizeof(TYPE)*newSize);
			if (theArray )
			{
				for (int i = 0; i < (oldSize < sizeAllocated?oldSize:sizeAllocated); ++i)
				{
					newArray[i] = theArray[i];
				}
				delete [] theArray;
			}
			theArray = newArray;
		}
		void grow()
		{
			reallocateTo(sizeAllocated + sizeChunk);
		}
	};

}





