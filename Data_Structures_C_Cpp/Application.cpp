#include <iostream>

/*
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
*/

template <typename T>
struct Node
{
	T m_data;
	Node<T>* m_nextPtr;

	Node(T data) :m_nextPtr(nullptr), m_data(data) {}
};

template <typename T>
class LinkedList {
protected:
	Node<T>* m_headPtr;
	Node<T>* GetANewNode(T data) const;
public:
	LinkedList();
	virtual ~LinkedList();
	void Traverse(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const;
	void Traverse(T(*callback)(T data, int index)) const;
};

template <typename T>
class Stack : public LinkedList<T> {
public:
	bool IsEmpty() const;
	void Push(T data);
	void Pop();
	T Top() const;
	void Reverse();
};

template <typename T>
class Queue : public LinkedList<T> {
private:
	Node<T> *m_tailPtr;
public:
	void EnQueue(T data); // Push
	void DeQueue(); // Pop
	T Front() const; // peek
	bool IsEmpty() const;
};

template<typename T, const unsigned int Size>
class QueueArray {
private:
	T m_queue[Size];
	int m_front;
	int m_rear;
public:
	QueueArray() :m_front(-1), m_rear(-1) {}
	int ArraySize() const;
	void Traverse(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const;
	void TraverseArray(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const;
	void EnQueue(T data); // Push
	void DeQueue(); // Pop
	T Front() const; // peek
	bool IsEmpty() const;
	bool IsFull() const;
};

enum Operators
{
	Subtraction = 0,
	Addition,
	Division,
	Multiplication,
	Undefined
};

class StackQueuTest {
public:
	static void StackTest();
	static bool CheckBalancedParentheses(const char *expression, Stack<char> &stack);
	static void CheckBalancedParenthesesTest();
	static int charToInt(char c);
	static int Operation(int operand_1, int operand_2, char operator_char);
	static void PostfixEvaluationTest();
	static void PrefixEvaluationTest();
	static void InfixToPostfixTest();
	static void CycleDetectionAlgorithmTest();
	static Operators GetOperator(char c);
	static void QueueArrayTest();
	static void QueueLinkedListTest();
	static void TestAll();
};

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
	
	
	StackQueuTest::TestAll();

	Insert_Search_Max_Min_Test();
	Print_Postorder_Preorder_Inorder_Levelorder_Test();
	Find_Height_Test();
	Traverse_Test();
	

	return 0;
}

#pragma region BinaryTreeNode

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(T data) :m_leftPtr(nullptr), m_rightPtr(nullptr), m_data(data) {}

#pragma endregion

#pragma region BinaryTreeNode

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
BinarySearchTree<T>::BinarySearchTree() :m_rootPrt(nullptr) {}

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
		else {
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
	if (m_rootPrt == nullptr) return T();

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

	Stack<BinaryTreeNode<T>*> s;

	while (curr != nullptr || s.IsEmpty() == false)
	{
		// Reach the left most Node of the curr Node
		while (curr != nullptr)
		{
			/* place pointer to a tree node on
			   the stack before traversing
			   the node's left subtree */
			s.Push(curr);
			curr = curr->m_leftPtr;
		}

		// Current must be NULL at this point
		curr = s.Top();
		s.Pop();

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

	Stack<BinaryTreeNode<T>*> s;

	while (!s.IsEmpty() || curr != nullptr) {
		/* Print left children while exist
		   and keep Pushing right into the
		   stack. */
		while (curr != nullptr) {

			callBack(curr->m_data);

			if (curr->m_rightPtr)
				s.Push(curr->m_rightPtr);

			curr = curr->m_leftPtr;
		}

		/* We reach when curr is NULL, so We
		   take out a right child from stack */
		if (s.IsEmpty() == false) {
			curr = s.Top();
			s.Pop();
		}
	}
}

template<typename T>
void BinarySearchTree<T>::TraversePostorder(void(*callBack)(T data)) const
{
	if (m_rootPrt == nullptr) return;

	BinaryTreeNode<T>* node;

	Stack<BinaryTreeNode<T>*> s1, s2;
	// Push root to first stack
	s1.Push(m_rootPrt);

	// Run while first stack is not IsEmpty
	while (!s1.IsEmpty()) {
		// Pop an item from s1 and Push it to s2
		node = s1.Top();
		s1.Pop();
		s2.Push(node);

		// Push left and right children
		// of removed item to s1
		if (node->m_leftPtr)
			s1.Push(node->m_leftPtr);
		if (node->m_rightPtr)
			s1.Push(node->m_rightPtr);
	}

	// Print all elements of second stack
	while (!s2.IsEmpty()) {
		node = s2.Top();
		s2.Pop();
		callBack(node->m_data);
	}
}

template<typename T>
T BinarySearchTree<T>::Traverse(T(*callBack)(T data, T returnValue)) const
{
	T returnValue = T();

	if (m_rootPrt == nullptr) return T();

	BinaryTreeNode<T>* curr = m_rootPrt;
	Stack<BinaryTreeNode<T>*> s;

	while (curr != nullptr || s.IsEmpty() == false)
	{
		while (curr != nullptr)
		{
			s.Push(curr);
			curr = curr->m_leftPtr;
		}
		curr = s.Top();
		s.Pop();

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
	Stack<BinaryTreeNode<T>*> s;

	while (curr != nullptr || s.IsEmpty() == false)
	{
		while (curr != nullptr)
		{
			s.Push(curr);
			curr = curr->m_leftPtr;
		}
		curr = s.Top();
		s.Pop();

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

	Queue<BinaryTreeNode<T>*> q;
	q.EnQueue(m_rootPrt);

	while (!q.IsEmpty()) {

		callBack(q.Front()->m_data);

		if (q.Front()->m_leftPtr) q.EnQueue(q.Front()->m_leftPtr);
		if (q.Front()->m_rightPtr) q.EnQueue(q.Front()->m_rightPtr);

		q.DeQueue();
	}
}


#pragma endregion

#pragma region TestBinarySearchTree

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

#pragma endregion

#pragma region LinkedList
template<typename T>
LinkedList<T>::LinkedList() :m_headPtr(nullptr) {}

template<typename T>
LinkedList<T>::~LinkedList() {}

template<typename T>
Node<T>* LinkedList<T>::GetANewNode(T data) const
{
	return new Node<T>(data);
}

template<typename T>
void LinkedList<T>::Traverse(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const
{
	callbackStart();

	Node<T>* ptr = m_headPtr;

	while (ptr != nullptr)
	{
		callback(ptr->m_data);
		ptr = ptr->m_nextPtr;
	}

	callbackEnd();
}

template<typename T>
void LinkedList<T>::Traverse(T(*callback)(T data, int index)) const
{
	int index = 0;
	Node<T>* ptr = m_headPtr;

	while (ptr != nullptr)
	{
		ptr->m_data = callback(ptr->m_data, index);
		ptr = ptr->m_nextPtr;
		index++;
	}
}
#pragma endregion

#pragma region Stack

template<typename T>
bool Stack<T>::IsEmpty() const
{
	if (this->m_headPtr == nullptr) return true;
	else return false;

}

template<typename T>
void Stack<T>::Push(T data)
{
	Node<T>* newNodePtr = this->GetANewNode(data);
	newNodePtr->m_nextPtr = this->m_headPtr;
	this->m_headPtr = newNodePtr;
}

template<typename T>
void Stack<T>::Pop()
{
	if (this->m_headPtr == nullptr) return;

	Node<T>* deleteNode = this->m_headPtr;
	T data = deleteNode->m_data;
	this->m_headPtr = this->m_headPtr->m_nextPtr;
	delete deleteNode;
}

template<typename T>
T Stack<T>::Top() const
{
	if (this->m_headPtr == nullptr) return T();
	return this->m_headPtr->m_data;
}

template<typename T>
void Stack<T>::Reverse()
{
	Stack<Node<T>*> stack;
	Node<T>* tempPtr = this->m_headPtr;

	while (tempPtr != nullptr)
	{
		stack.Push(tempPtr);
		tempPtr = tempPtr->m_nextPtr;
	}

	tempPtr = stack.Top();
	this->m_headPtr = tempPtr;
	stack.Pop();
	while (!stack.IsEmpty())
	{
		tempPtr->m_nextPtr = stack.Top();
		stack.Pop();
		tempPtr = tempPtr->m_nextPtr;
	}
	tempPtr->m_nextPtr = nullptr;
}

#pragma endregion

#pragma region Queue

template<typename T>
void Queue<T>::EnQueue(T data)
{
	Node<T>* newNode = this->GetANewNode(data);

	if (this->m_headPtr == nullptr) {
		this->m_headPtr = newNode;
		this->m_tailPtr = newNode;
	}
	else {
		this->m_tailPtr->m_nextPtr = newNode;
		this->m_tailPtr = newNode;
	}
}

template<typename T>
void Queue<T>::DeQueue()
{
	if (this->m_headPtr == nullptr) return;

	if (this->m_headPtr == this->m_tailPtr) {
		delete this->m_headPtr;
		this->m_headPtr = nullptr;
		this->m_tailPtr = nullptr;
	}
	else {
		Node<T>* deleteNodePtr = this->m_headPtr;
		this->m_headPtr = this->m_headPtr->m_nextPtr;
		delete deleteNodePtr;
	}
}

template<typename T>
T Queue<T>::Front() const
{
	if (this->m_headPtr == nullptr) return T();
	else return this->m_headPtr->m_data;
}

template<typename T>
bool Queue<T>::IsEmpty() const
{
	if (this->m_headPtr == nullptr) return true;
	else return false;
}

#pragma endregion

#pragma region QueueArray

template<typename T, const unsigned int Size>
int QueueArray<T, Size>::ArraySize() const
{
	return Size;
}

template<typename T, const unsigned int Size>
void QueueArray<T, Size>::Traverse(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const
{
	callbackStart();

	int i = m_front;
	if (m_front == -1) return;
	do {
		callback(m_queue[i]);
		i = (i + 1) % Size;
	} while (i != (m_rear + 1) % Size);

	callbackEnd();
}

template<typename T, const unsigned int Size>
void QueueArray<T, Size>::TraverseArray(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const
{
	callbackStart();

	for (int i = 0; i < Size; i++)
	{
		callback(m_queue[i]);
	}

	callbackEnd();
}

template<typename T, const unsigned int Size>
bool QueueArray<T, Size>::IsEmpty() const
{
	if (m_front == -1 && m_rear == -1) return true;
	else return false;
}

template<typename T, const unsigned int Size>
bool QueueArray<T, Size>::IsFull() const
{
	if ((m_rear + 1) % Size == m_front) return true;
	else return false;
}

template<typename T, const unsigned int Size>
void QueueArray<T, Size>::EnQueue(T data)
{
	if (IsFull()) return;
	else if (IsEmpty()) {
		m_front = 0;
		m_rear = 0;
	}
	else m_rear = (m_rear + 1) % Size;

	m_queue[m_rear] = data;
}

template<typename T, const unsigned int Size>
void QueueArray<T, Size>::DeQueue()
{
	if (IsEmpty()) return;
	else if (m_front == m_rear) {
		m_front = -1;
		m_rear = -1;
	}
	else m_front = (m_front + 1) % Size;
}

template<typename T, const unsigned int Size>
T QueueArray<T, Size>::Front() const
{
	if (IsEmpty()) return T();
	else m_queue[m_front];
}

#pragma endregion

#pragma region TestLinkedListStackQueue

void StackQueuTest::StackTest()
{
	Stack<int> stack;
	for (int i = 0; i < 20; i++) {
		stack.Push(i * 11);
	}
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.IsEmpty() << std::endl;
	std::cout << "Top : " << stack.Top() << std::endl;

	stack.Reverse();
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.IsEmpty() << std::endl;
	std::cout << "Top : " << stack.Top() << std::endl;

	stack.Traverse([](int data, int index) { return data + index; });
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);

	std::cout << "Poped items : ";
	while (!stack.IsEmpty()) {
		stack.Pop();
	}
	std::cout << std::endl;
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.IsEmpty() << std::endl;
	std::cout << "Top : " << stack.Top() << std::endl;

	for (int i = 0; i < 20; i++) {
		stack.Push(i * 10);
	}
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.IsEmpty() << std::endl;
	std::cout << "Top : " << stack.Top() << std::endl;
}

bool StackQueuTest::CheckBalancedParentheses(const char *expression, Stack<char> &stack) {
	int i = 0;

	while (expression[i] != 0)
	{
		char c = expression[i];

		if (c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}') {
			if (c == '[' || c == '(' || c == '{') {
				stack.Push(c);
			}
			else {
				if (stack.IsEmpty()) {
					stack.Push(c);
					break;
				}
				else {
					if (stack.Top() == '[' && c != ']') break;
					else if (stack.Top() == '(' && c != ')') break;
					else if (stack.Top() == '{' && c != '}') break;
					else {
						stack.Pop();
					}
				}
			}
		}

		i++;
	}

	if (stack.IsEmpty()) return true;
	else return false;
}

void StackQueuTest::CheckBalancedParenthesesTest() {

	Stack<char> stack;

	const char* text = "{ [ (a+b) + (b+c) ] }";

	CheckBalancedParentheses(text, stack);

	if (stack.IsEmpty()) {
		std::cout << "Balanced" << std::endl;
	}
	else
	{
		std::cout << "Not Balanced" << std::endl;
	}

}

int StackQueuTest::charToInt(char c) {

	return (int)c - 48;
}

int StackQueuTest::Operation(int operand_1, int operand_2, char operator_char) {
	if (operator_char == '+') return operand_1 + operand_2;
	if (operator_char == '-') return operand_1 - operand_2;
	if (operator_char == '*') return operand_1 * operand_2;
	else return 0;
}

void StackQueuTest::PostfixEvaluationTest() {

	char expression[] = { '2','3','*','5','4','*','+','9','-' };
	//char expression[] = { '2','3','*','5','4','*','-'};

	Stack<int> stack;

	int size = sizeof(expression);
	for (int i = 0; i < size; i++) {
		if ((int)expression[i] > 48 && (int)expression[i] < 58) {
			stack.Push(charToInt(expression[i]));
		}
		else {
			int operand_2 = stack.Top();
			stack.Pop();
			int operand_1 = stack.Top();
			stack.Pop();

			stack.Push(Operation(operand_1, operand_2, expression[i]));
		}
	}

	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
}

void StackQueuTest::PrefixEvaluationTest()
{
	char expression[] = { '-', '+', '*', '2','3', '*','5','4','9' };

	Stack<int> stack;

	int size = sizeof(expression);
	for (int i = size - 1; i >= 0; i--) {


		if ((int)expression[i] > 48 && (int)expression[i] < 58) {
			stack.Push(charToInt(expression[i]));
		}
		else {
			int operand_1 = stack.Top();
			stack.Pop();
			int operand_2 = stack.Top();
			stack.Pop();

			stack.Push(Operation(operand_1, operand_2, expression[i]));
		}

	}

	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
}

void StackQueuTest::InfixToPostfixTest()
{
	// Infix to postfix
	// operator precedence ( or order of oparation)
	// 1. paracentesis () {} []
	// 2. exponents ( right to left )
	// 3. multiplication and division (left to right)
	// 4. addition and subtraction (left to right)

	//std::cout << GetOperator('-') << std::endl;

	//char expression[] = { '(','(','1','+','2',')','*','3','-','4',')','*','5' };
	char expression[] = { '1','*','(','2','+','3',')' };
	const int size = sizeof(expression);

	Stack<char> postfix;
	Stack<char> stack;

	for (int i = 0; i < size; i++)
	{
		if ((int)expression[i] > 48 && (int)expression[i] < 58) {
			postfix.Push(expression[i]);
		}
		else if (expression[i] == '(') {
			stack.Push(expression[i]);
		}
		else if (expression[i] == ')') {
			while (stack.Top() != '(')
			{
				postfix.Push(stack.Top());
				stack.Pop();
			}
			stack.Pop();
		}
		else {
			while (!stack.IsEmpty() && (GetOperator(stack.Top()) > GetOperator(expression[i])) && stack.Top() != '(')
			{
				postfix.Push(stack.Top());
				stack.Pop();
			}
			stack.Push(expression[i]);
		}
	}
	while (!stack.IsEmpty())
	{
		postfix.Push(stack.Top());
		stack.Pop();
	}

	postfix.Reverse();
	postfix.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
}

void StackQueuTest::CycleDetectionAlgorithmTest() {
	int x[] = { 1,4,3,5,6,1,2 };
	//int x[] = { 1,4,2,3,5,6,2 };

	int slow = x[0];
	int fast = x[0];
	while (true)
	{
		slow = x[slow];

		fast = x[fast];
		fast = x[fast];

		if (fast == slow) {
			std::cout << "Duplicate value : " << x[fast] << std::endl;
			break;
		}
	}
}

Operators StackQueuTest::GetOperator(char c)
{
	switch (c)
	{
	case '-':
		return Operators::Subtraction;
	case '+':
		return Operators::Addition;
	case '/':
		return Operators::Division;
	case '*':
		return Operators::Multiplication;
	default:
		return Operators::Undefined;
	}
}

void StackQueuTest::QueueArrayTest()
{
	QueueArray<int, 3> queue;

	std::cout << "Array Size : " << queue.ArraySize() << std::endl;

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Is Full : " << queue.IsFull() << std::endl;


	queue.EnQueue(11);
	queue.EnQueue(22);
	queue.EnQueue(33);

	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl; }
	);
	queue.TraverseArray(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Array : "; },
		[]() {std::cout << std::endl; }
	);

	queue.DeQueue();

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Is Full : " << queue.IsFull() << std::endl;

	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl; }
	);
	queue.TraverseArray(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Array : "; },
		[]() {std::cout << std::endl; }
	);

	queue.EnQueue(44);
	queue.EnQueue(55);

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Is Full : " << queue.IsFull() << std::endl;

	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl; }
	);
	queue.TraverseArray(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Array : "; },
		[]() {std::cout << std::endl; }
	);

	queue.DeQueue();
	queue.EnQueue(55);

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Is Full : " << queue.IsFull() << std::endl;

	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl; }
	);
	queue.TraverseArray(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Array : "; },
		[]() {std::cout << std::endl; }
	);
}

void StackQueuTest::QueueLinkedListTest()
{
	Queue<int> queue;

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Front : " << queue.Front() << std::endl;
	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl << std::endl; }
	);

	queue.EnQueue(10);
	queue.EnQueue(20);
	queue.EnQueue(30);
	queue.EnQueue(40);

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Front : " << queue.Front() << std::endl;
	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl << std::endl; }
	);

	queue.DeQueue();
	queue.DeQueue();

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Front : " << queue.Front() << std::endl;
	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl << std::endl; }
	);

	queue.DeQueue();
	queue.DeQueue();
	queue.EnQueue(11);

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Front : " << queue.Front() << std::endl;
	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl << std::endl; }
	);

	queue.DeQueue();
	queue.DeQueue();

	std::cout << "Is Empty : " << queue.IsEmpty() << std::endl;
	std::cout << "Front : " << queue.Front() << std::endl;
	queue.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "Queue : "; },
		[]() {std::cout << std::endl << std::endl; }
	);
}

void StackQueuTest::TestAll()
{
	QueueLinkedListTest();
	QueueArrayTest();
	InfixToPostfixTest();
	CycleDetectionAlgorithmTest();
	PrefixEvaluationTest();
	PostfixEvaluationTest();
	CheckBalancedParenthesesTest();
	StackTest();
}

#pragma endregion

