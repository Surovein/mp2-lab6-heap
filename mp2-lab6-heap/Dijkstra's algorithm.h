#pragma once
#include"Heap.h"
#include<vector>
class Dijkstra
{													//start = 0   finish = 3
public:											//	  index							  		  		  					distance	0 1 2 3 
	struct Node										//					0	(1,1)	(2,1)	(3,5)					`				0 1 2 2
	{												//					1	(0,1)	(3,1)
		int index;									//					2	(0,2)	(3,1)
		int min_distance = 0;							//				3	(1,1)	(2,1)	(0,5)
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



	int count; //число вершин index
	//std::vector<std::vector<edge>> adjacency_matrix;
	std::vector<int> distance;
	std::vector < bool > visit;
	DHeap<Node> heap;
	

	Dijkstra(int nv) : distance(nv), visit(nv) {
		for (int i = 0; i < distance.size(); i++)
		{
			distance[i] = -1;
		}
	for (int i = 0; i < visit.size(); i++)
	{
		visit[i] = 0;
	}
	}


	int Algorithm(int st, const std::vector<std::vector<edge>>& v)
	{
		int start_index = st;
		heap.Insert(Node(st, 0));
		
		while (heap.Get_size() != 0)
		{		
			Node element = heap.Getmax();
			visit[start_index] = true;
		}

	}
	~Dijkstra()
	{

	}
};														