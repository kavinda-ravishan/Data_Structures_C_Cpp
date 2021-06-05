#include <iostream>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "LinkedList.h"


template <typename T>
struct BinaryTreeNode
{
	T m_data;
	BinaryTreeNode<T>* m_leftPtr;
	BinaryTreeNode<T>* m_rightPtr;

	BinaryTreeNode(T data);
};

template <typename T>
class BinarySearchTree {
private:
	BinaryTreeNode<T>* m_rootPrt;
	BinaryTreeNode<T>* GetANewNode(T data) const;
public:
	BinarySearchTree();

	void Insert(T data);
};

int main(int argc, char** args) {
	
	BinarySearchTree<int> tree;
	tree.Insert(15);
	tree.Insert(10);
	tree.Insert(20);
	tree.Insert(25);

	return 0;
}

// --- BinaryTreeNode --- //

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(T data) :m_leftPtr(nullptr), m_rightPtr(nullptr), m_data(data) {}

// --- BinarySearchTree --- //

template<typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::GetANewNode(T data) const
{
	return new BinaryTreeNode<T>(data);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree():m_rootPrt(nullptr){}

template<typename T>
void BinarySearchTree<T>::Insert(T data)
{
	if (m_rootPrt == nullptr) {
		m_rootPrt = GetANewNode(data);
		return;
	}

	BinaryTreeNode<T>* tempPtr = m_rootPrt;
	while (true)
	{
		if (data <= tempPtr->m_data) {
			if (tempPtr->m_leftPtr == nullptr) {
				tempPtr->m_leftPtr = GetANewNode(data);
				return;
			}
			tempPtr = tempPtr->m_leftPtr;
		}
		else{
			if (tempPtr->m_rightPtr == nullptr) {
				tempPtr->m_rightPtr = GetANewNode(data);
				return;
			}
			tempPtr = tempPtr->m_rightPtr;
		}
	}
}
