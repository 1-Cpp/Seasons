#pragma once

/**
  * October
  * (C) Copyright 2015 @Martin@ 
  * mbr 27.07.2015 09:59:08
  */
namespace Seasons
{
	class October
	{
	public:
		const wchar_t * what;
		October(const wchar_t * what) : what(what) {
			print(1);
		}
		~October() {
			print(2);
		}
		void print(int param);
	};

}
