/*
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "BinarySearchTree.h"
*/

#include <iostream>
#include <vector>

#define print(x) std::cout<<x
#define printl(x) std::cout<<x<<std::endl

template<typename V>
struct Vertex
{
	V m_vertex;

	Vertex(V vertex)
		:m_vertex(vertex){}
};

template<typename V, typename W>
struct Edge
{
	V m_startVertex;
	V m_endVertex;
	W m_weight;

	Edge(V startVertex, V endVertex, W weight)
		:m_startVertex(startVertex), m_endVertex(endVertex),m_weight(weight) {}
};

                         
int main(int argc, char** args) {

	std::vector<Vertex<char>> vertexList = {
		Vertex<char>('A'), // 0
		Vertex<char>('B'), // 1
		Vertex<char>('C'), // 2
		Vertex<char>('D'), // 3
		Vertex<char>('E'), // 4
		Vertex<char>('F'), // 5
		Vertex<char>('G'), // 6
		Vertex<char>('H')  // 7
	};

	std::vector<Edge<int,int>> edgeList = {
		Edge<int, int>(0, 1, 5),
		Edge<int, int>(0, 2 ,7),
		Edge<int, int>(0, 3, 3),
		Edge<int, int>(1, 4, 2),
		Edge<int, int>(1, 5, 10),
		Edge<int, int>(2, 6, 1),
		Edge<int, int>(3, 7, 11),
		Edge<int, int>(4, 7, 9),
		Edge<int, int>(5, 7, 4),
		Edge<int, int>(6, 7, 6)
	};

	for (int i = 0; i < edgeList.size(); i++) {
		print(vertexList[edgeList[i].m_startVertex].m_vertex);
		print(", ");
		print(vertexList[edgeList[i].m_endVertex].m_vertex);
		print(" - ");
		printl(edgeList[i].m_weight);
	}

/*
                      5
				A ----------- B
			7  / \  3      2 / \ 10
			  /   \         /   \
			 C     D       E     F
		   1 |   11 \   9 /     /
			 G       \   /     /
			 |_________H _____/ 4
                6
*/

	return 0;
}



