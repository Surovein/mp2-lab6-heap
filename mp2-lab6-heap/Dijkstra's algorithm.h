#pragma once
#include"Heap.h"
#include<vector>
struct Node										//					0	(1,1)	(2,1)	(3,5)					`				0 1 2 2
{												//					1	(0,1)	(3,1)
	int index;									//					2	(0,2)	(3,1)
	int min_distance = 0;												//				3	(1,1)	(2,1)	(0,5)
	Node(int ind, int dist)
	{
		index = ind;
		min_distance = dist;
	}
	bool operator == (const Node& x)
	{

		return (index == x.index && min_distance == x.min_distance);
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


template<typename T>
class DHeapBoostWrapper    // нужна только для моего типа, чтобы был общий интерфейс
{
private:
	DHeap<T, std::greater<T>> heap; 

public:
	using handle_type = int;  // тип для идентификации элемента в куче

	handle_type push(const T& value) 
	{
		return heap.Insert_ret(value);
	}

	void update(handle_type h, const T& value) 
	{
		heap.DecreaseKey(h, value);
	}

	T top() const 
	{
		return heap.GetTop();
	}

	void pop() 
	{
		heap.Delete(0);
	}

	bool empty() const 
	{
		return heap.Get_size() == 0;
	}

	size_t size() const 
	{
		return heap.Get_size();
	}
};





template < typename theap> class  Dijkstra
{													//start = 0   finish = 3
public:											//	  index							  		  		  					distance	0 1 2 3 

	struct edge
	{
		int neighbour = -1;// с кем соединено
		int dist = -1; // расстояние

		edge(int ch = -1, int dis = -1)
		{
			neighbour = ch;
			dist = dis;
		}

		bool operator<(const edge& x) const   /// handle это аналог Insert_index
		{
			return dist < x.dist;
		}
	};


	struct dist
	{
		//int insert_index = -1;   // берём тип из класса theap
		typename theap::handle_type handle{};
		int distance = -1;
		bool operator==(const dist& x)
		{
			return (handle == x.handle && distance == x.distance);
		}
	};

	int count; //число вершин index
	std::vector<dist> distance;
	std::vector < bool > visit;
	theap heap; // DHeap<Node> heap
	

	Dijkstra(int nv) : distance(nv), visit(nv) {
		for (int i = 0; i < distance.size(); i++)
		{
			distance[i].distance = -1;
			//distance[i].insert_index = -1;
		}
	for (int i = 0; i < visit.size(); i++)
	{
		visit[i] = 0;
	}
	}


	std::vector<dist>& Algorithm(int st, const std::vector<std::vector<edge>>& v)
	{
		int start_value = st;// индекс строки в v
		distance[start_value].handle = heap.push(Node(st,0)); // insert_index -> handle Insert_ret -> push
		distance[start_value].distance = 0;
		while (!heap.empty())
		{		
			Node element = heap.top();
			heap.pop();
			//visit[element.index] = true;
				for (int i = 0; i < v[element.index].size(); i++)
				{

					if (distance[v[element.index][i].neighbour].distance == -1)
					{
						int new_dist = distance[element.index].distance + v[element.index][i].dist;

						Node neighbour(v[element.index][i].neighbour,new_dist);
						distance[v[element.index][i].neighbour].handle = heap.push(neighbour);
						distance[v[element.index][i].neighbour].distance = new_dist;

					}
					else
					{
						if (distance[v[element.index][i].neighbour].distance > distance[element.index].distance + v[element.index][i].dist)
						{
							Node neighbour(v[element.index][i].neighbour, distance[element.index].distance + v[element.index][i].dist);
							heap.update(distance[v[element.index][i].neighbour].handle, neighbour);
							distance[v[element.index][i].neighbour].distance = distance[element.index].distance + v[element.index][i].dist;
						}
					}
				}

		}
		return distance;

	}
	~Dijkstra()
	{

	}
};														