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
	virtual void write(int element) = 0;
};

