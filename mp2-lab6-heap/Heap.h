#pragma once
#pragma once
#include <vector>
template <typename tval, class Comparator = std::greater<tval>>
class DHeap
{
protected:
	std::vector<tval> data;
	int d;
	int last_free = 0;

	Comparator c;

public:
	DHeap()
	{
		last_free = 0;
		d = 2;
		data.resize(d*8);
	}
	DHeap(int size, int n)
	{
		last_free = 0;
		d = n;
		data.resize(size);
	}
	DHeap(std::vector<tval>& vec, int n)
	{
		data = vec;
		last_free = vec.size();
		d = n;
	}
	void Insert(tval val)
	{
		if (last_free == data.size())
		{
			Rehash();
		}
		data[last_free] = val;
		surfacing(last_free);
		last_free++;
	}
	int Get_size()
	{
		return data.size();
	}
	void Delete(int index)
	{
		if (index >= 0 && index < last_free)
		{
			tval tmp = data[index];
			data[index] = data[last_free - 1];
			last_free--;
			if (index != 0 && data[index] > data[(index - 1) / d])
			{
				surfacing(index);
			}
			else
			{
				Dive(index);
			}
		}
	}
	int  Child_index(int index)
	{
		int index_max = index * d + 1;
		if (index_max >= data.size())// нет детей
		{
			return -1;
		}
		tval max_child = data[index * d + 1];
		int last_child_index = index * d + d;
		if (last_child_index >= data.size()) /// вдруг детей меньше d
		{
			last_child_index = data.size()-1;
		}
		for (int k = index * d + 2; k <= last_child_index; k++)
		{
			if (c( data[k], max_child))
				
				
//				data[k] > max_child)
			{
				max_child = data[k];
				index_max = k;
			}
		}
		return index_max;
	}
	void Dive(int index)
	{
		int i = index;
		int index_max_child = Child_index(index);// максимум наверху
		if (index_max_child == -1) // ищем первый элемент у которого есть дети 
		{
			return;
		}
		while (c(data[index_max_child], data[i]))    //(data[i] < data[index_max_child])
		{
			//bool check = ( c(data[index_max_child], data[i]) == (data[i] < data[index_max_child]));
			tval tmp = data[i];
			data[i] = data[index_max_child];
			data[index_max_child] = tmp;
			i = index_max_child;
			index_max_child = Child_index(i);
			if (index_max_child == -1)
			{
				return;
			}
		}
	}
	void surfacing(int index)
	{
		if (index == 0)
		{
			return;
		}
		int i = (index - 1) / d;
		while (i >= 0 && c(data[index], data[i]))
	//	while (i >= 0 && data[index] > data[i])
		{
			//bool check = c(data[i], data[index]);
			tval tmp = data[i];
			data[i] = data[index];
			data[index] = tmp;
			index = i;
			i = (i - 1) / d;
		}

	}
	DHeap heapify(std::vector<tval>& mas, int n)
	{
		DHeap heap(mas, n);// n - кол во веток  n = d
		for (int i = (mas.size() - 1) / n; i >= 0; i--)
		{
			heap.Dive(i);
		}
		return heap;
	}
	void Rehash()
	{
		std::vector<tval> vec;
		vec.resize(data.size() * 2);
		for (int i = 0; i < last_free; i++)
		{
			vec[i] = data[i];
		}
		std::swap(vec, data);

	}
	tval Getmax()
	{
		if (last_free == 0)
		{
			throw 1;
		}
		tval max = data[0];
		Delete(0);
		return max;
	}
	tval Get_element(int index)
	{
		return data[index];
	}
	~DHeap()
	{

	}
};