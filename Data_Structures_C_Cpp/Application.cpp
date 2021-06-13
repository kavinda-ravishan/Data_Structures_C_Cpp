#include <stack>
#include <queue>
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
	BinaryTreeNode<T>* m_rootPrt;
	BinaryTreeNode<T>* GetANewNode(T data) const;
	BinaryTreeNode<T>* Insert(T data, BinaryTreeNode<T>* rootPtr);
	bool Search(T data, BinaryTreeNode<T>* rootPtr) const;
	T GetMin(BinaryTreeNode<T>* rootPtr) const;
	T GetMax(BinaryTreeNode<T>* rootPtr) const;
	void TraversePostorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const;
	void TraversePreorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const;
	void TraverseInorder(BinaryTreeNode<T>* rootPrt, void(*callBack)(T data)) const;
	int FindHeight(BinaryTreeNode<T>* rootPtr) const;

public:
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
	void TraversePreorder(void(*callBack)(T data)) const;
	void TraversePostorder(void(*callBack)(T data)) const;
	T Traverse(T(*callBack)(T data, T returnValue)) const;
	void Traverse(void(*callBack)(T* data)) const;
	int FindHeightRec() const;
	void LevelOrderTraverse(void(*callBack)(T data)) const;
};

void Insert_Search_Max_Min_Test();
void Print_Postorder_Preorder_Inorder_Levelorder_Test();
void Find_Height_Test();
void Traverse_Test();

int main(int argc, char** args) {
	
	Insert_Search_Max_Min_Test();
	Print_Postorder_Preorder_Inorder_Levelorder_Test();
	Find_Height_Test();
	Traverse_Test();

	return 0;
}

// --- BinaryTreeNode --- //

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(T data) :m_leftPtr(nullptr), m_rightPtr(nullptr), m_data(data) {}

// --- BinarySearchTree --- //

//  private //
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
int BinarySearchTree<T>::FindHeight(BinaryTreeNode<T>* rootPtr) const
{
	if (rootPtr == nullptr) return -1;

	int leftHeight = FindHeight(rootPtr->m_leftPtr);
	int rightHeight = FindHeight(rootPtr->m_rightPtr);

	if (leftHeight > rightHeight) return leftHeight + 1;
	else return rightHeight + 1;
}

// public //

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
	if (m_rootPrt == nullptr) return;

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

template<typename T>
void BinarySearchTree<T>::TraversePreorder(void(*callBack)(T data)) const
{
	if (m_rootPrt == nullptr) return;

	BinaryTreeNode<T>* curr = m_rootPrt;

	std::stack<BinaryTreeNode<T>*> s;

	while (!s.empty() || curr != nullptr) {
		/* Print left children while exist
		   and keep pushing right into the
		   stack. */
		while (curr != nullptr) {

			callBack(curr->m_data);

			if (curr->m_rightPtr)
				s.push(curr->m_rightPtr);

			curr = curr->m_leftPtr;
		}

		/* We reach when curr is NULL, so We
		   take out a right child from stack */
		if (s.empty() == false) {
			curr = s.top();
			s.pop();
		}
	}
}

template<typename T>
void BinarySearchTree<T>::TraversePostorder(void(*callBack)(T data)) const
{
	if (m_rootPrt == nullptr) return;

	BinaryTreeNode<T>* node;

	std::stack<BinaryTreeNode<T>*> s1, s2;
	// push root to first stack
	s1.push(m_rootPrt);

	// Run while first stack is not empty
	while (!s1.empty()) {
		// Pop an item from s1 and push it to s2
		node = s1.top();
		s1.pop();
		s2.push(node);

		// Push left and right children
		// of removed item to s1
		if (node->m_leftPtr)
			s1.push(node->m_leftPtr);
		if (node->m_rightPtr)
			s1.push(node->m_rightPtr);
	}

	// Print all elements of second stack
	while (!s2.empty()) {
		node = s2.top();
		s2.pop();
		callBack(node->m_data);
	}
}

template<typename T>
T BinarySearchTree<T>::Traverse(T(*callBack)(T data, T returnValue)) const
{
	T returnValue = T();

	if (m_rootPrt == nullptr) return T();

	BinaryTreeNode<T>* curr = m_rootPrt;
	std::stack<BinaryTreeNode<T>*> s;

	while (curr != nullptr || s.empty() == false)
	{
		while (curr != nullptr)
		{
			s.push(curr);
			curr = curr->m_leftPtr;
		}
		curr = s.top();
		s.pop();

		returnValue = callBack(curr->m_data, returnValue);

		curr = curr->m_rightPtr;
	}

	return returnValue;
}

template<typename T>
void BinarySearchTree<T>::Traverse(void(*callBack)(T *data)) const
{
	if (m_rootPrt == nullptr) return;

	BinaryTreeNode<T>* curr = m_rootPrt;
	std::stack<BinaryTreeNode<T>*> s;

	while (curr != nullptr || s.empty() == false)
	{
		while (curr != nullptr)
		{
			s.push(curr);
			curr = curr->m_leftPtr;
		}
		curr = s.top();
		s.pop();

		callBack(&(curr->m_data));

		curr = curr->m_rightPtr;
	}
}

template<typename T>
int BinarySearchTree<T>::FindHeightRec() const
{
	return FindHeight(m_rootPrt);
}

template<typename T>
void BinarySearchTree<T>::LevelOrderTraverse(void(*callBack)(T data)) const
{
	if (m_rootPrt == nullptr) return;

	std::queue<BinaryTreeNode<T>*> q;
	q.push(m_rootPrt);

	while (!q.empty()) {

		callBack(q.front()->m_data);
		
		if (q.front()->m_leftPtr) q.push(q.front()->m_leftPtr);
		if (q.front()->m_rightPtr) q.push(q.front()->m_rightPtr);

		q.pop();
	}
}

// --- Test --- //

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

void Print_Postorder_Preorder_Inorder_Levelorder_Test()
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
	    	  ___|___
	    	 |       |
	    	10       20
	       __|__    __|__
	      |     |  |     |
	      4    11  16   25
	    __|            __|__
	   |              |     |
	   3             21     26
	    
	*/

	std::cout << "Postorder Rec : ";
	tree.TraverseRec(Order::Postorder, [](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Postorder     : ";
	tree.TraversePostorder([](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Preorder Rec  : ";
	tree.TraverseRec(Order::Preorder, [](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Postorder     : ";
	tree.TraversePreorder([](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Inorder Rec   : ";
	tree.TraverseRec(Order::Inorder, [](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Inorder       : ";
	tree.TraverseInorder([](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Levelorder    : ";
	tree.LevelOrderTraverse([](int data) {std::cout << data << " "; });
	std::cout << std::endl;

}

void Find_Height_Test()
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
	tree.Insert(30);

	/*
				 15
			  ___|___
			 |       |
			10       20
		   __|__    __|__
		  |     |  |     |
		  4    11  16   25
		__|            __|__
	   |              |     |
	   3             21     26
							|__
							   |
							   30
	*/

	std::cout << "Height : " << tree.FindHeightRec() << std::endl;
}

void Traverse_Test()
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
	tree.Insert(30);

	/*
				 15
			  ___|___
			 |       |
			10       20
		   __|__    __|__
		  |     |  |     |
		  4    11  16   25
		__|            __|__
	   |              |     |
	   3             21     26
							|__
							   |
							   30
	*/

	std::cout << "Inorder : ";
	tree.TraverseInorder([](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Sum : " << tree.Traverse([](int data, int returnVal) {return data + returnVal; }) << std::endl;

	tree.Traverse(
		[](int* data)
	{
		*data = *data + 1;
	}
	);

	std::cout << "Inorder : ";
	tree.TraverseInorder([](int data) {std::cout << data << " "; });
	std::cout << std::endl;

	std::cout << "Sum : " << tree.Traverse([](int data, int returnVal) {return data + returnVal; }) << std::endl;

	std::cout << "Number of nodes : " << tree.Traverse([](int data, int returnVal) {return returnVal + 1; }) << std::endl;
}
