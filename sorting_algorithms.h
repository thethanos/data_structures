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

		for (;i <= mid && j <= high; k++)
		{
			if (arr[i] < arr[j])
			{
				temp[k] = arr[i];
				i++;
			}
			else
			{
				temp[k] = arr[j];
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

	template <typename ForwardIt>
	void merge(ForwardIt begin, ForwardIt end, ForwardIt mid)
	{
		std::vector<typename ForwardIt::value_type> temp;

		auto iter1 = begin, iter2 = mid;
		for (; iter1 != mid && iter2 != end; )
		{
			if (*iter1 < *iter2)
			{
				temp.push_back(*iter1);
				++iter1;
			}
			else
			{
				temp.push_back(*iter2);
				++iter2;
			}
		}

		for (; iter1 != mid; ++iter1)
			temp.push_back(*iter1);

		for (; iter2 != end; ++iter2)
			temp.push_back(*iter2);

		copy(temp.begin(), temp.end(), begin);
	}

	int partition(int arr[], int low, int high)
	{
		int pivot = arr[high];  
		int i = (low - 1); 

		for (int j(low); j < high; j++)
		{ 
			if (arr[j] < pivot)
			{
				i++; 
				swap(arr[i], arr[j]);
			}
		}

		swap(arr[i + 1], arr[high]);
		return (i + 1);
	}

	template <typename ForwardIt>
	ForwardIt partition(ForwardIt begin, ForwardIt end)
	{
		ForwardIt pivot(begin), iter1(begin), iter2(begin);
		
		for (iter1++; iter1 != end; iter1++)
		{
			if (*iter1 < *pivot)
			{
				iter2++;
				util::swap(*iter1, *iter2);
			}
		}

		util::swap(*pivot, *iter2);
		return ++iter2;
	}

	void quick_sort(int arr[], int low, int high)
	{
		if (low >= high)
			return;

		int pi = partition(arr, low, high);

		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}

	int get_next_gap(int gap)
	{
		gap = (gap * 10) / 13;

		if (gap < 1) return 1;
		return gap;
	}

	void heapify(int* arr, int size, int index)
	{
		int left   = (2 * index) + 1;
		int right  = (2 * index) + 2;
		int temp = index;

		if (left < size && arr[left] > arr[index])
			temp = left;

		if (right < size && arr[right] > arr[temp])
			temp = right;

		if (temp != index)
		{
			swap(arr[index], arr[temp]);
			heapify(arr, size, temp);
		}
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
void selection_sort(T(&arr)[size])
{
	int min(0);
	for (int i(0); i < size - 1; ++i)
	{
		min = i;
		for (int j(i+1); j < size; ++j)
			if (arr[j] < arr[min])
				min = j;

		util::swap(arr[i], arr[min]);
	}
}

template <typename Iterator>
void selection_sort(Iterator begin, Iterator end)
{
	Iterator min = begin;
	for (auto iter1(begin); iter1 != end; iter1++)
	{
		min = iter1;
		for (auto iter2(iter1); iter2 != end; iter2++)
		{
			if (*iter2 < *min)
				min = iter2;
		}

		util::swap(*iter1, *min);
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

template <typename ForwardIt>
void merge_sort(ForwardIt begin, ForwardIt end)
{
	typename ForwardIt::difference_type dist = distance(begin, end);
	if (dist < 2) return;

	ForwardIt mid_it = next(begin, dist / 2);

	merge_sort(begin, mid_it);
	merge_sort(mid_it, end);

	util::merge(begin, end, mid_it);
}

template <typename ForwardIt>
void merge_sort_mt(ForwardIt begin, ForwardIt end)
{
	typename ForwardIt::difference_type dist = distance(begin, end);
	if (dist < 2) return;

	ForwardIt mid_it = next(begin, dist / 2);

	std::thread th(merge_sort<ForwardIt>, begin, mid_it);
	merge_sort(mid_it, end);

	th.join();
	merge(begin, end, mid_it);
}

template <typename T, size_t size>
void quick_sort(T(&arr)[size])
{
	util::quick_sort(arr, 0, size - 1);
}

template <typename ForwardIt>
void quick_sort(ForwardIt begin, ForwardIt end)
{
	if (util::distance(begin,end) < 2)
		return;

	ForwardIt mid = util::partition(begin, end);

	quick_sort(begin, mid);
	quick_sort(mid, end);
}

template <typename ForwardIt>
void quick_sort_mt(ForwardIt begin, ForwardIt end)
{
	if (distance(begin, end) < 2) return;

	ForwardIt mid = partition(begin, end);

	std::thread th(quick_sort<ForwardIt>, begin, mid);
	quick_sort(mid, end);
	th.join();
}

template <typename T, size_t size>
void insertion_sort(T(&arr)[size])
{
	for (int i(1); i < size; ++i)
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j)
			util::swap(arr[j-1], arr[j]);
}

template <typename Iterator>
void insertion_sort(Iterator begin, Iterator end)
{
	for (auto iter1(begin); iter1 != end; ++iter1)
		for (auto iter2(iter1), iter3(iter1); iter2 != begin && *(--iter3) > *iter2; --iter2)
			util::swap(*iter2, *iter3);
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

template <typename T, size_t size>
void heap_sort(T(&arr)[size])
{
	for (int i = (size / 2) - 1; i >= 0; --i)
		util::heapify(arr, size, i);

	for (int heap_size(size-1); heap_size > 0; --heap_size)
	{
		util::swap(arr[0], arr[heap_size]);
		util::heapify(arr, heap_size, 0);
	}
}