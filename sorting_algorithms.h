#pragma once

#include <iostream>

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

	void merge(int*, int, int, int);
	void merge_sort(int* arr, int low, int high)
	{
		if (low >= high)
			return;
			
		int mid = (low + high) / 2;
		merge_sort(arr, low, mid);
		merge_sort(arr, mid + 1, high);
			
		merge(arr, low, high, mid);
	}

	void merge(int* arr, int low, int high, int mid)
	{
		int i(low), j(mid + 1), k(low);
		int* temp = new int[high + 1];

		while (i <= mid && j <= high)
		{
			if (arr[i] < arr[j])
			{
				temp[k] = arr[i];
				k++;
				i++;
			}
			else
			{
				temp[k] = arr[j];
				k++;
				j++;
			}
		}

		for (; i <= mid; k++, i++)
			temp[k] = arr[i];

		for (; j <= high; k++, j++)
			temp[k] = arr[j];

		for (i = low; i < k; i++)
			arr[i] = temp[i];

		delete[] temp;
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
			if (util::swap(arr[j], arr[j + 1]))
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
void merge_sort(T(&arr)[size])
{
	util::merge_sort(arr, 0, size - 1);
}
