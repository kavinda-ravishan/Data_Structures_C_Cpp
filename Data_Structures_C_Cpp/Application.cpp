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
	bool Search(T data, BinaryTreeNode<T>* rootPtr) const;
public:
	BinarySearchTree();

	void Insert(T data);
	void InsertRec(T data);
	bool SearchRec(T data) const;
};

int main(int argc, char** args) {
	
	BinarySearchTree<int> tree;
	tree.InsertRec(15);
	tree.InsertRec(10);
	tree.InsertRec(20);
	tree.InsertRec(25);
	tree.Insert(16);
	tree.Insert(11);
	tree.Insert(21);
	tree.Insert(26);

	std::cout << "Search for Number {" << 15 << "} : " << tree.SearchRec(15) << std::endl;
	std::cout << "Search for Number {" << 26 << "} : " << tree.SearchRec(26) << std::endl;
	std::cout << "Search for Number {" << 16 << "} : " << tree.SearchRec(16) << std::endl;

	std::cout << "Search for Number {" << 17 << "} : " << tree.SearchRec(17) << std::endl;
	std::cout << "Search for Number {" << 27 << "} : " << tree.SearchRec(27) << std::endl;
	std::cout << "Search for Number {" << 18 << "} : " << tree.SearchRec(18) << std::endl;

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
BinaryTreeNode<T>* BinarySearchTree<T>::Insert(T data, BinaryTreeNode<T>* rootPtr)
{
	if (rootPtr == nullptr) {
		rootPtr = GetANewNode(data);
	}
	else if (data <= rootPtr->m_data) {
		rootPtr->m_leftPtr = Insert(data, rootPtr->m_leftPtr);
	}
	else {
		rootPtr->m_rightPtr = Insert(data, rootPtr->m_rightPtr);
	}
	return rootPtr;
}

template<typename T>
bool BinarySearchTree<T>::Search(T data, BinaryTreeNode<T>* rootPtr) const
{
	if (rootPtr == nullptr) return false;
	else if (rootPtr->m_data == data) return true;
	else if (data <= rootPtr->m_data) return Search(data, rootPtr->m_leftPtr);
	else return Search(data, rootPtr->m_rightPtr);
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
bool BinarySearchTree<T>::SearchRec(T data) const
{
	return Search(data, m_rootPrt);
}

