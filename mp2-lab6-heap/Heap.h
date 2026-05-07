#pragma once
#pragma once
#include <vector>
template <typename tval, class Comparator = std::less<tval>> // less // greater
class DHeap
{
public:
	struct Node
	{
		int number_in_mas = -1; // индекс в index_in_heap
		tval value;
		Node& operator = (const Node& x)
		{
			number_in_mas = x.number_in_mas;
			value = x.value;
			return *this;
		}
	};
	std::vector<Node> data;
	int d;
	int last_free = 0;
	std::vector<int> index_in_heap;
	Comparator c;
	int count = 0;			// вставка index_in_heap[count] = ... , count++

public:
	DHeap()
	{
		last_free = 0;
		d = 2;
		data.resize(d*8);
		index_in_heap.resize(d * 8,-1);
	}
	DHeap(int size, int n)
	{
		last_free = 0;
		d = n;
		data.resize(size);
		index_in_heap.resize(size, -1);

	}
	DHeap(std::vector<tval>& vec, int n)
	{
		d = n;
		data.resize(vec.size());
		index_in_heap.resize(vec.size(), -1);
		count = 0;

		for (int i = 0; i < vec.size(); i++)
		{
			data[i].value = vec[i];
			data[i].number_in_mas = count;
			index_in_heap[count] = i;
			count++;
		}
		//data = vec;
		last_free = vec.size();

	}
	void Insert(tval val)
	{
		if (last_free == data.size())
		{
			Rehash();
		}
		data[last_free].value = val;
		data[last_free].number_in_mas = count;
		index_in_heap[count] = last_free;
		count++;
		surfacing(last_free, data[last_free].number_in_mas);
		last_free++;
	}
	int Insert_ret(tval val)
	{
		if (last_free == data.size())
		{
			Rehash();
		}
		data[last_free].value = val;
		data[last_free].number_in_mas = count;
		index_in_heap[count] = last_free;
		int tmp_count = count;
		count++;
		surfacing(last_free, data[last_free].number_in_mas);
		last_free++;
		return tmp_count ;
	}
	int Get_size()
	{
		return last_free;
	}
	int Get_data_size()
	{
		return data.size();
	}
	void Delete(int index)
	{
		if (index >= 0 && index < last_free)
		{

			int delete_ind = data[index].number_in_mas;
			index_in_heap[delete_ind] = -1;

			data[index] = data[last_free-1];
			index_in_heap[data[index].number_in_mas] = index;

			last_free--;
			if (index != 0 && data[index].value > data[(index - 1) / d].value)
			{
				surfacing(index, data[index].number_in_mas);
			}
			else
			{
				Dive(index, data[index].number_in_mas);
			}
		}
	}
	int  Child_index(int index)
	{
		int index_max = index * d + 1;
		if (index_max >= last_free)// нет детей
		{
			return -1;
		}
		tval max_child = data[index * d + 1].value;
		int last_child_index = index * d + d;
		if (last_child_index >= last_free) /// вдруг детей меньше d
		{
			last_child_index = last_free -1;
		}
		for (int k = index * d + 2; k <= last_child_index; k++)
		{
			if (c( data[k].value, max_child))
				
				
//				data[k] > max_child)
			{
				max_child = data[k].value;
				index_max = k;
			}
		}
		return index_max;
	}
	void Dive(int index, int index_in_mas)
	{
		int i = index;
		int index_max_child = Child_index(index);// максимум наверху
		if (index_max_child == -1) // ищем первый элемент у которого есть дети 
		{
			index_in_heap[index_in_mas] = index;
			return;
		}
		index_in_heap[index_in_mas] = index;
		while (c(data[index_max_child].value, data[i].value))    //(data[i] < data[index_max_child])
		{
			//bool  = ( c(data[index_max_child], data[i]) == (data[i] < data[index_max_child]));
			
			tval tmp = data[i].value;
			data[i].value = data[index_max_child].value;
			data[index_max_child].value = tmp; 


			int tmp_id = data[i].number_in_mas;
			data[i].number_in_mas = data[index_max_child].number_in_mas;
			data[index_max_child].number_in_mas = tmp_id; 

			index_in_heap[tmp_id] = index_max_child;
			index_in_heap[data[i].number_in_mas] = i;

			i = index_max_child;
			index_max_child = Child_index(i);
			if (index_max_child == -1)
			{
				//dex_in_heap[index_in_mas] = i;
				return;
			}
		}
		
	}
	void surfacing(int index, int index_in_mas)
	{
		if (index == 0)
		{
			index_in_heap[index_in_mas] = index;
			return;
		}
		int i = (index - 1) / d;
		index_in_heap[index_in_mas] = index;

		while (i >= 0 && c(data[index].value, data[i].value))
		{

			tval tmp = data[i].value;


			data[i].value = data[index].value;
			data[index].value = tmp;

			int tmp_id = data[i].number_in_mas;
			data[i].number_in_mas = data[index].number_in_mas;
			data[index].number_in_mas = tmp_id;

			index_in_heap[tmp_id] = index;
			index_in_heap[data[i].number_in_mas] = i;

			index = i;
			i = (i - 1) / d;
		}
	}
	DHeap heapify(std::vector<tval>& mas, int n)
	{
		DHeap heap(mas, n);// n - кол во веток  n = d
		for (int i = (mas.size() - 1) / n; i >= 0; i--)
		{
			heap.Dive(i,heap.data[i].number_in_mas);
		}
		return heap;
	}
	void Rehash()
	{
		std::vector<Node> vec;
		vec.resize(data.size() * 2);
		std::vector<int> tmp;
		tmp.resize(index_in_heap.size() * 2,-1);
		for (int i = 0; i < last_free; i++)
		{
			vec[i] = data[i];
		}
		for (int i = 0; i < count; i++)
		{
			tmp[i] = index_in_heap[i];
		}
		std::swap(vec, data);
		std::swap(tmp, index_in_heap);

	}
	tval Getmax()
	{
		if (last_free == 0)
		{
			throw 1;
		}
		tval max = data[0].value;
		Delete(0);
		return max;
	}
	tval Get_element(int index)
	{
		return data[index].value;
	}

	void DecreaseKey(int insert_ret_index, tval newp)
	{
		if (insert_ret_index < count)
		{
			int index = index_in_heap[insert_ret_index];
			if (index != -1)
			{
				data[index].value = newp;
				if (index != 0 && data[index].value > data[(index - 1) / d].value)
				{
					surfacing(index, data[index].number_in_mas);
				}
				else
				{
					Dive(index, data[index].number_in_mas);
				}
			}

		}
	}
	tval element(int index)
	{
		return data[index_in_heap[index]].value;  // count == номер - > index_in_heap[номер] - > data[index_in_heap]
	}
	~DHeap()
	{

	}
};