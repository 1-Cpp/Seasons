#pragma once

#include <stdarg.h>
#include <string>
#include "Exception.h"

namespace Seasons
{
	class StringImpl;
	class String
	{
	protected:
		StringImpl * theImpl = nullptr;
	public:

		String();

		virtual ~String();

		String(const wchar_t*str);
		String(const wchar_t*str, unsigned int count);
		String(const String&str);
		String(const std::wstring&str);
		int format(const wchar_t*format, ...);
		int vformat(const wchar_t*format, va_list list);
		String substr(unsigned int offset, unsigned int count);
		operator std::wstring() const;
		operator const wchar_t*() const;

		wchar_t charAt(unsigned int offset) const;
		unsigned int size() const;

		void setFormatBufferSize(unsigned int size);
		void trim();
		void ltrim();
		void rtrim();
		String operator=(const String&toAssign);
		String operator+=(const String&toAdd);
		String operator+=(const wchar_t&toAdd);
		bool operator==(const String&toCompare) const;
		bool operator!=(const String&toCompare) const;
		//bool operator < (const String&toCompare) const;
		bool isEmpty();
		int compare(const String&other) const;
	};
	String operator+(const String & s1, const String& s2);
	bool operator<(const String & s1, const String& s2);

	//bool operator==(const String & s1, const String& s2);

}