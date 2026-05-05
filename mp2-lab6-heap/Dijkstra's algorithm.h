#pragma once
#include"Heap.h"
#include<vector>
class Dijkstra
{													//start = 0   finish = 3
public:											//	  index				  0		  1		  2		  3				distance	0 1 2 3 
	struct Node										//					0	(0,0)	(1,1)	(1,2)	(0,0)					0 1 2 2
	{												//					1	(1,1)	(0,0)	(0,0)	(1,1)
		int index;									//					2	(1,2)	(0,0)	(0,0)	(1,1)
		int min_distance = 0;							//				3	(0,0)	(1,1)	(1,1)	(0,0)
		Node(int ind, int dist)
		{
			index = ind;
			min_distance = dist;
		}
		Node()
		{
			index = -1;
			min_distance = 0;
		}
		bool operator>(const Node& x) const
		{
			return min_distance > x.min_distance;
		}
		bool operator<(const Node& x) const
		{
			return min_distance < x.min_distance;
		}
	};
	struct edge
	{
		int check = -1;// соединено ли
		int dist = -1; // рассто€ние
		edge()
		{
			check = -1;
			dist = -1;
		}
		edge(int ch, int dis)                                       
		{
			check = ch;
			dist = dis;
		}
		edge& operator=(const edge& x)
		{
			check = x.check;
			dist = x.dist;
			return *this;
		}
		bool operator<(const edge& x) const
		{
			return dist < x.dist;
		}
	};
	int start_index;
	int finish_index;	
	int count; //число вершин index
	std::vector<std::vector<edge>> adjacency_matrix;	
	std::vector<int> distance;                       
	std::vector < bool > visit;
	DHeap<Node> heap;
	std::vector<int> index_in_heap;
	Dijkstra(int c, int st, int fin,std::vector<std::vector<edge>> v)
	{
		count = c;
		start_index = st;
		finish_index = fin;
		adjacency_matrix.resize(v.size());
		for (int i = 0; i < v.size(); i++) 
		{
			adjacency_matrix[i].resize(v[i].size());  // идем по столбцам
			for (int j = 0; j < v[i].size(); j++) 
			{
				adjacency_matrix[i][j] = v[i][j];// по строке
			}
		}
		distance.resize(v.size());
		for (int i = 0; i < v.size(); i++)
		{
			if (i != start_index)
			{
				distance[i] = -1;
			}
			else
			{
				distance[i] = 0;
			}
		}
		visit.resize(v.size());
		for (int i = 0; i < v.size(); i++)
		{
			visit[i] = 0;
		}
		Node a(start_index, 0);
		heap.Insert(a);
		index_in_heap.resize(v.size());
		for (int i = 0; i < v.size(); i++)
		{
			index_in_heap[i] = -1;
		}
	}
	void Insert_heap(edge x,int index, int current)
	{

		Node tmp(index, x.dist);
		if ((distance[index] != -1 && distance[index] > x.dist)|| distance[index] == -1)
		{
			distance[index] = x.dist;
		}
		index_in_heap[index] = heap.Insert_ret(tmp);
	}
	int Minimum(Node element,int current_index)
	{
		int index_min = -1;
		for (int i = 0; i < adjacency_matrix.size(); i++)
		{
			if (adjacency_matrix[element.index][i].check != 0)
			{
				if (visit[i] == 0)
				{

					Insert_heap(adjacency_matrix[element.index][i], i,current_index); // херню вставл€ю

				}
				if ((index_min == -1 || adjacency_matrix[element.index][i] < adjacency_matrix[element.index][index_min]) && (index_min!=current_index))
				{
					int tmp = index_min;
					index_min = i;
					if (index_min == current_index)
					{
						index_min = tmp;
					}
				}
			}

		}
		return index_min;
	}
	int Algorithm()
	{
		Node element = heap.Getmax();
		int current_index = start_index;
		visit[start_index] = true;
		int k = 0;
		while (heap.Get_size() != 0)
		{

		//	int min_index = Minimum(element,current_index); // нашли мин соседа
		//	if (k != 0)
		//	{
		//		current_index = element.index;
		//	}
		//	if (min_index !=-1 && adjacency_matrix[element.index][min_index].check == 1 && distance[min_index] >= distance[element.index] + adjacency_matrix[element.index][min_index].dist)
		//	{
		//		distance[min_index] = adjacency_matrix[element.index][min_index].dist+ distance[element.index];
		//		heap.Delete(index_in_heap[min_index]);
		//		Node a(min_index, distance[min_index]);
		//		index_in_heap[min_index] = heap.Insert_ret(a);
		//	}
		//	if (min_index == finish_index || min_index == element.index)
		//	{
		//		element = heap.Getmax();
		//		if (element.index == -1)
		//		{
		//			element.index = start_index;
		//			k = 0;
		//			//current_index = sta
		//		}
		//		visit[element.index] = true; // 1 когда беру элемент из кучи
		//		//current_index = heap.Getmax().index;
		//	}
		//	else
		//	{
		//		//current_index = element.index;
		//		//current_index = min_index;
		//		Node b(min_index, distance[min_index]);
		//		//int min_index = Minimum(b);
		//		//element = heap.Get_element(index_in_heap[min_index]);
		//		element = b;
		//		k++;
		//	}


		//}
		return distance[finish_index];
	}
	~Dijkstra()
	{

	}
};														