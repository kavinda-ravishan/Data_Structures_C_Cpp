#include <stack>
#include <iostream>

/*
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "LinkedList.h"
*/

template <typename T>
struct BinaryTreeNode
{
	T m_data;
	BinaryTreeNode<T>* m_leftPtr;
	BinaryTreeNode<T>* m_rightPtr;

	BinaryTreeNode(T data);
};

enum Order
{
	Postorder = 0,
	Preorder,
	Inorder
};

template <typename T>
class BinarySearchTree {
private:
	//BinaryTreeNode<T>* m_rootPrt;

	BinaryTreeNode<T>* GetANewNode(T data) const;
	BinaryTreeNode<T>* Insert(T data, BinaryTreeNode<T>* rootPtr);
	bool Search(T data, BinaryTreeNode<T>* rootPtr) const;
	T GetMin(BinaryTreeNode<T>* rootPtr) const;
	T GetMax(BinaryTreeNode<T>* rootPtr) const;
	void TraversePostorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const;
	void TraversePreorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const;
	void TraverseInorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const;
public:
	BinaryTreeNode<T>* m_rootPrt;

	BinarySearchTree();
	void Insert(T data);
	void InsertRec(T data);
	bool Search(T data) const;
	bool SearchRec(T data) const;
	T GetMin() const;
	T GetMinRec() const;
	T GetMax() const;
	T GetMaxRec() const;
	void TraverseRec(Order order, void(*callBack)(T data)) const;
	void TraverseInorder(void(*callBack)(T data)) const;
};

void Insert_Search_Max_Min_Test();

void Print_Postorder_Preorder_Inorder_Test();

int main(int argc, char** args) {
	
	//Insert_Search_Max_Min_Test();
	Print_Postorder_Preorder_Inorder_Test();
	
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
T BinarySearchTree<T>::GetMin(BinaryTreeNode<T>* rootPtr) const
{
	if (rootPtr == nullptr) return T();
	
	if (rootPtr->m_leftPtr == nullptr) return rootPtr->m_data;
	else return GetMin(rootPtr->m_leftPtr);

}

template<typename T>
T BinarySearchTree<T>::GetMax(BinaryTreeNode<T>* rootPtr) const
{
	if (rootPtr == nullptr) return T();

	if (rootPtr->m_rightPtr == nullptr) return rootPtr->m_data;
	else return GetMax(rootPtr->m_rightPtr);
}

template<typename T>
void BinarySearchTree<T>::TraversePostorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const
{
	if (rootPrt == nullptr) return;

	TraversePostorder(rootPrt->m_leftPtr, callBack);
	TraversePostorder(rootPrt->m_rightPtr, callBack);
	callBack(rootPrt->m_data);
}

template<typename T>
void BinarySearchTree<T>::TraversePreorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const
{
	if (rootPrt == nullptr) return;

	callBack(rootPrt->m_data);
	TraversePreorder(rootPrt->m_leftPtr, callBack);
	TraversePreorder(rootPrt->m_rightPtr, callBack);
}

template<typename T>
void BinarySearchTree<T>::TraverseInorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const
{
	if (rootPrt == nullptr) return;

	TraverseInorder(rootPrt->m_leftPtr, callBack);
	callBack(rootPrt->m_data);
	TraverseInorder(rootPrt->m_rightPtr, callBack);
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
bool BinarySearchTree<T>::Search(T data) const
{
	BinaryTreeNode<T>* tempPtr = m_rootPrt;

	while (tempPtr != nullptr)
	{
		if (data == tempPtr->m_data) return true;
		else if (data <= tempPtr->m_data) tempPtr = tempPtr->m_leftPtr;
		else tempPtr = tempPtr->m_rightPtr;
	}
	return false;
}

template<typename T>
bool BinarySearchTree<T>::SearchRec(T data) const
{
	return Search(data, m_rootPrt);
}

template<typename T>
T BinarySearchTree<T>::GetMin() const
{
	if(m_rootPrt == nullptr) return T();

	BinaryTreeNode<T>* tempPtr = m_rootPrt;

	while (tempPtr->m_leftPtr != nullptr)
	{
		tempPtr = tempPtr->m_leftPtr;
	}

	return tempPtr->m_data;
}

template<typename T>
T BinarySearchTree<T>::GetMinRec() const
{
	return GetMin(m_rootPrt);
}

template<typename T>
T BinarySearchTree<T>::GetMax() const
{
	if (m_rootPrt == nullptr) return T();

	BinaryTreeNode<T>* tempPtr = m_rootPrt;

	while (tempPtr->m_rightPtr != nullptr)
	{
		tempPtr = tempPtr->m_rightPtr;
	}

	return tempPtr->m_data;
}

template<typename T>
T BinarySearchTree<T>::GetMaxRec() const
{
	return GetMax(m_rootPrt);
}

template<typename T>
void BinarySearchTree<T>::TraverseRec(Order order, void(*callBack)(T data)) const
{
	switch (order)
	{
	case Order::Postorder:
		TraversePostorder(m_rootPrt, callBack);
		break;
	case Order::Preorder:
		TraversePreorder(m_rootPrt, callBack);
		break;
	case Order::Inorder:
		TraverseInorder(m_rootPrt, callBack);
		break;
	default:
		break;
	}
}

template<typename T>
void BinarySearchTree<T>::TraverseInorder(void(*callBack)(T data)) const
{
	BinaryTreeNode<T>* curr = m_rootPrt;

	std::stack<BinaryTreeNode<T>*> s;

	while (curr != nullptr || s.empty() == false)
	{
		// Reach the left most Node of the curr Node
		while (curr != nullptr)
		{
			/* place pointer to a tree node on
			   the stack before traversing
			   the node's left subtree */
			s.push(curr);
			curr = curr->m_leftPtr;
		}

		// Current must be NULL at this point
		curr = s.top();
		s.pop();

		callBack(curr->m_data);

		/* we have visited the node and its
		   left subtree.  Now, it's right
		   subtree's turn */
		curr = curr->m_rightPtr;

	}
}

void Insert_Search_Max_Min_Test()
{
	BinarySearchTree<int> tree;

	int number = 0;

	number = 15; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;
	number = 26; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;
	number = 16; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;

	number = 17; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;
	number = 27; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;
	number = 18; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;

	number = 15; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;
	number = 26; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;
	number = 16; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;

	number = 17; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;
	number = 27; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;
	number = 18; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;

	std::cout << "Min : " << tree.GetMin() << std::endl;
	std::cout << "Max : " << tree.GetMax() << std::endl;

	std::cout << "Min : " << tree.GetMinRec() << std::endl;
	std::cout << "Max : " << tree.GetMaxRec() << std::endl;

	tree.InsertRec(15);
	tree.InsertRec(10);
	tree.InsertRec(20);
	tree.InsertRec(25);
	tree.Insert(16);
	tree.Insert(11);
	tree.Insert(21);
	tree.Insert(26);

	number = 15; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;
	number = 26; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;
	number = 16; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;

	number = 17; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;
	number = 27; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;
	number = 18; std::cout << "Is {" << number << "} exist : " << (tree.SearchRec(number) ? "Yes" : "No") << std::endl;

	number = 15; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;
	number = 26; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;
	number = 16; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;

	number = 17; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;
	number = 27; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;
	number = 18; std::cout << "Is {" << number << "} exist : " << (tree.Search(number) ? "Yes" : "No") << std::endl;

	std::cout << "Min : " << tree.GetMin() << std::endl;
	std::cout << "Max : " << tree.GetMax() << std::endl;

	std::cout << "Min : " << tree.GetMinRec() << std::endl;
	std::cout << "Max : " << tree.GetMaxRec() << std::endl;
}

void Print_Postorder_Preorder_Inorder_Test()
{
	BinarySearchTree<int> tree;

	tree.Insert(15);
	tree.Insert(10);
	tree.Insert(4);
	tree.Insert(20);
	tree.Insert(3);
	tree.Insert(25);
	tree.Insert(16);
	tree.Insert(11);
	tree.Insert(21);
	tree.Insert(26);

	/*
			15
		  __|__
		 |     |
		10    20
	   _|_    _|_
	  |   |  |   |
	  4  11  16 25
	 _|         _|_
	|          |   |
	3          21 26

	*/

	std::cout << "Postorder Rec : ";
	tree.TraverseRec(Order::Postorder, [](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Preorder Rec : ";
	tree.TraverseRec(Order::Preorder, [](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Inorder Rec : ";
	tree.TraverseRec(Order::Inorder, [](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Inorder     : ";
	tree.TraverseInorder([](int data) {std::cout << data << " "; });
	std::cout << std::endl;
}
