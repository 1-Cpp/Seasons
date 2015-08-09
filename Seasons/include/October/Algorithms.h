#pragma once

namespace Seasons
{
	template<typename KEY> class less
	{
	public:
		bool operator()(const KEY& keyLeft, const KEY & keyRight)
		{
			return keyLeft < keyRight;
		}
	};

}
