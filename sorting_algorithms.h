#pragma once

#include <iostream>
#include <thread>
#include <vector>


namespace util
{
	template <typename T, size_t size>
	void print_array(T(&arr)[size])
	{
		for (int i(0); i < size; ++i)
			std::cout << arr[i] << std::endl;
	}

	template <class T>
	void swap(T& first, T& second)
	{
		T temp = first;
		first  = second;
		second = temp;
	}

	template <class Iterator>
	size_t distance(Iterator begin, Iterator end)
	{
		int distance(0);
		for (auto iter(begin); iter != end; distance++, iter++) {}
		return distance;
	}

	int get_next_gap(int gap)
	{
		gap = (gap * 10) / 13;

		if (gap < 1) return 1;
		return gap;
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

template <typename ForwardIt>
void bubble_sort(ForwardIt begin, ForwardIt end)
{
	for (auto iter1(begin); iter1 != end; ++iter1)
	{
		ForwardIt iter2(begin), iter3(begin);
		for (iter3++; iter3 != end; ++iter2, ++iter3)
		{
			if (*iter2 > * iter3)
				std::iter_swap(iter2, iter3);
		}
	}
}

template <typename T, size_t size>
void cocktail_sort(T(&arr)[size])
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

template <typename T, size_t size>
void comb_sort(T(&arr)[size])
{
	int gap(size);
	bool swapped(true);

	while (gap != 1 || swapped == true)
	{
		gap = util::get_next_gap(gap);
		swapped = false;

		for (int i(0); i < size - gap; ++i)
		{
			if (arr[i] > arr[i + gap])
			{
				util::swap(arr[i], arr[i + gap]);
				swapped = true;
			}
		}
	}
}

template <typename Iterator>
void comb_sort(Iterator begin, Iterator end)
{
	int gap = util::distance(begin, end) - 1;
	bool swapped = true;

	while (gap != 1 || swapped == true)
	{
		gap = util::get_next_gap(gap);
		swapped = false;

		auto iter2(begin);
		std::advance(iter2, gap);
		for (auto iter1(begin); iter2 != end; ++iter1, ++iter2)
		{
			if (*iter1 > * iter2)
			{
				util::swap(*iter1, *iter2);
				swapped = true;
			}
		}
	}
}
