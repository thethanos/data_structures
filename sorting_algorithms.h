#pragma once

#include <algorithm>

namespace util
{
	template <class T>
	void swap(T& begin, T& end)
	{
		T temp = begin;
		begin  = end;
		end    = temp;
	}

}

template <typename T, size_t size>
void bubble_sort(T (&arr)[size])
{
	bool early_exit(true);
	for (int i(0); i < size - 1; ++i)
	{
		for (int j(0); j < size - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				util::swap(arr[j], arr[j + 1]);
				early_exit = false;
			}
		}
		
		if (early_exit)
			break;
	}
}

template <typename T, size_t size>
void selection_sort(T(&arr)[size])
{
	int min(0);
	for (int i(0); i < size - 1; ++i)
	{
		for (int j(i+1); j < size; ++j)
			if (arr[j] < arr[min])
				min = j;

		util::swap(arr[i], arr[min]);
	}
}

template <typename T, size_t size>
void coctail_sort(T(&arr)[size])
{
	int begin = 0, end = size - 1;
	bool swapped = true;

	while (swapped)
	{
		swapped = false;

		for (int i(begin); i < end; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				util::swap(arr[i],arr[i + 1]);
				swapped = true;
			}
		}

		if (!swapped)
			return;

		swapped = false;

		--end;

		for (int i(end - 1); i >= begin; --i)
		{
			if (arr[i] > arr[i + 1])
			{
				util::swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}

		++begin;
	}
}


