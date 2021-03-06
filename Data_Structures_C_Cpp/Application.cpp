/*
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "BinarySearchTree.h"
*/

#include <iostream>
#include <vector>
#include <array>

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

void Graph_1(){

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

	std::vector<Edge<int, int>> edgeList = {
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

	printl("");
}

void Graph_2() {
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

	const unsigned int SIZE_MAT = 8;

	bool adjacencyMatrix[SIZE_MAT][SIZE_MAT] = {
		{false, true , true , true , false, false, false, false},
		{true , false, false, false, true , true , false, false},
		{true , false, false, false, false, false, true , false},
		{true , false, false, false, false, false, false, true },
		{false, true , false, false, false, false, false, true },
		{false, true , false, false, false, false, false, true },
		{false, false, true , false, false, false, false, true },
		{false, false, false, true , true , true , true , false}
	};

	for (int i = 0; i < SIZE_MAT; i++) {

		print(vertexList[i].m_vertex);
		print(" : ");

		for (int j = 0; j < SIZE_MAT; j++) {

			if (adjacencyMatrix[i][j]) {
				print(vertexList[j].m_vertex);
				print(" ");
			}
		}
		printl("");
	}
	printl("");

}

void Graph_3() {
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

	std::vector<std::vector<int>> adjacencyList = {
		std::vector<int>{ 1,2,3 },
		std::vector<int>{ 0,4,5 },
		std::vector<int>{ 0,6 },
		std::vector<int>{ 0,7 },
		std::vector<int>{ 1,7 },
		std::vector<int>{ 1,7 },
		std::vector<int>{ 2,7 },
		std::vector<int>{ 3,6,4,5 }
	};

	for (int i = 0; i < adjacencyList.size(); i++) {

		print(vertexList[i].m_vertex);
		print(" : ");
		for (int j = 0; j < adjacencyList[i].size(); j++) {

			print(vertexList[adjacencyList[i][j]].m_vertex);
			print(" ");
		}
		printl("");
	}
	printl("");

}

int main(int argc, char** args) {

	Graph_1();
	Graph_2();
	Graph_3();


	return 0;
}



