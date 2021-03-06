#pragma once


namespace Seasons
{
	class Exception
	{
	public:

		Exception()
		{
		}

		virtual ~Exception()
		{
		}
	};
	class OutOfMemoryException : public Exception {
	public:
		OutOfMemoryException()
		{
		}

		virtual ~OutOfMemoryException()
		{
		}
	};
	class OutOfBoundsException : public Exception {
	public:
		OutOfBoundsException()
		{
		}

		virtual ~OutOfBoundsException()
		{
		}
	};

	class IOException : public Exception {
	public:
		IOException()
		{
		}

		virtual ~IOException()
		{
		}
	};
	class EOFException : public IOException {
	public:
		EOFException()
		{
		}

		virtual ~EOFException()
		{
		}
	};

	class UnsupportedOperationException : public Exception {
	public:
		UnsupportedOperationException()
		{
		}

		virtual ~UnsupportedOperationException()
		{
		}
	};



}