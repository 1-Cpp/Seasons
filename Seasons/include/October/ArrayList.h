#pragma once

#include "October/Exception.h"
#include <memory.h>

namespace Seasons
{

	template<class TYPE> class ArrayList
	{
	protected:
		TYPE * theArray = nullptr;
		int sizeAllocated = 0;
		int sizeChunk = 64;
	public:
		int length = 0;
		virtual ~ArrayList()
		{
			delete (unsigned char*)theArray;
		}
		void add(TYPE value)
		{
			if (sizeAllocated <= length)
				reallocateTo(sizeChunk);
			theArray[length] = value;
			length++;
		}
		void add(ArrayList<TYPE> ar)
		{
			reserve(length + ar.length);
			for (int i = length, j = 0; i < length + ar.length; i++, j++)
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
		void insert(int index, TYPE value)
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
	protected:
		void reallocateTo(int newSize)
		{
			TYPE * newArray = (TYPE*)new unsigned char[newSize * sizeof(TYPE)];
			sizeAllocated = newSize;
			memset(newArray, 0, sizeof(TYPE)*newSize);
			memcpy(newArray, theArray, length*sizeof(TYPE));
			delete (unsigned char *)theArray;
			theArray = newArray;
		}
		void grow()
		{
			reallocateTo(sizeAllocated + sizeChunk);
		}
	};

}





