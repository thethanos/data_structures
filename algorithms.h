#pragma once


template <typename BidirectIt, typename T>
bool two_pointers(BidirectIt begin, BidirectIt end, T goal)
{
	auto first = begin, second = --end;

	while (first != second)
	{
		if (*first + *second == goal)
			return true;

		if (*first + *second < goal)
			++first;
		else
			--second;
	}

	return false;
}
