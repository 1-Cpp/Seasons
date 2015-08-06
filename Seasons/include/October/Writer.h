#pragma once


namespace Seasons
{

class Writer
{
public:

	Writer()
	{
	}

	virtual ~Writer()
	{
	}
	virtual int write(int element) = 0;
};

}
