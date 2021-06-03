#include <iostream>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "LinkedList.h"


template <typename T>
struct BinTreeNode
{
	T m_data;
	BinTreeNode<T>* m_leftPtr;
	BinTreeNode<T>* m_rightPtr;

	BinTreeNode(T data);
};


int main(int argc, char** args) {
	
	BinTreeNode<int>* node = new BinTreeNode<int>(10);

	std::cout << "Data : " << node->m_data << std::endl;
	std::cout << "Left : " << node->m_leftPtr << std::endl;
	std::cout << "Right : " << node->m_rightPtr << std::endl;

	SinglyLinkedListTest::TestAll();
	DoublyLinkedListTest::TestAll();
	StackQueuTest::TestAll();

	return 0;
}

// --- Node --- //

template<typename T>
BinTreeNode<T>::BinTreeNode(T data) :m_leftPtr(nullptr), m_rightPtr(nullptr), m_data(data) {}