#pragma once
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

