#pragma once
#include"Heap.h"
#include<vector>
class Dijkstra
{													//start = 0   finish = 3
public:											//	  index							  		  		  					distance	0 1 2 3 
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
	struct edge
	{
		int neighbour = -1;// с кем соединено
		int dist = -1; // расстояние

		edge(int ch = -1, int dis = -1)
		{
			neighbour = ch;
			dist = dis;
		}

		bool operator<(const edge& x) const
		{
			return dist < x.dist;
		}
	};


	struct dist
	{
		int insert_index = -1;
		int distance = -1;
		bool operator==(const dist& x)
		{
			return (insert_index == x.insert_index && distance == x.distance);
		}
	};

	int count; //число вершин index
	std::vector<dist> distance;
	std::vector < bool > visit;
	DHeap<Node> heap;
	

	Dijkstra(int nv) : distance(nv), visit(nv) {
		for (int i = 0; i < distance.size(); i++)
		{
			distance[i].distance = -1;
			distance[i].insert_index = -1;
		}
	for (int i = 0; i < visit.size(); i++)
	{
		visit[i] = 0;
	}
	}


	std::vector<dist>& Algorithm(int st, const std::vector<std::vector<edge>>& v)
	{
		int start_value = st;// индекс строки в v
		distance[start_value].insert_index = heap.Insert_ret(Node(st,0));
		distance[start_value].distance = 0;
		while (heap.Get_size() != 0)
		{		
			Node element = heap.Getmax();
			//visit[element.index] = true;
				for (int i = 0; i < v[element.index].size(); i++)
				{

					if (distance[v[element.index][i].neighbour].distance == -1)
					{
						int new_dist = distance[element.index].distance + v[element.index][i].dist;

						Node neighbour(v[element.index][i].neighbour,new_dist);
						distance[v[element.index][i].neighbour].insert_index = heap.Insert_ret(neighbour);
						distance[v[element.index][i].neighbour].distance = new_dist;

					}
					else
					{
						if (distance[v[element.index][i].neighbour].distance > distance[element.index].distance + v[element.index][i].dist)
						{
							Node neighbour(v[element.index][i].neighbour, distance[element.index].distance + v[element.index][i].dist);
							heap.DecreaseKey(distance[v[element.index][i].neighbour].insert_index, neighbour);
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