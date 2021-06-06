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
	BinaryTreeNode<T>* Insert(T data, BinaryTreeNode<T>* rootPtr);
public:
	BinarySearchTree();

	void Insert(T data);
	void InsertRec(T data);
};

int main(int argc, char** args) {
	
	BinarySearchTree<int> tree;
	tree.InsertRec(15);
	tree.InsertRec(10);
	tree.InsertRec(20);
	tree.InsertRec(25);

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

template<typename T>
void BinarySearchTree<T>::InsertRec(T data)
{
	m_rootPrt = Insert(data, m_rootPrt);
}

template<typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::Insert(T data, BinaryTreeNode<T>* rootPtr)
{
	if (rootPtr == nullptr) {
		rootPtr = GetANewNode(data);
	}
	else if (data <= rootPtr->m_data) {
		rootPtr->m_leftPtr = Insert(data, rootPtr->m_leftPtr);
	}
	else{
		rootPtr->m_rightPtr = Insert(data, rootPtr->m_rightPtr);
	}
	return rootPtr;
}
