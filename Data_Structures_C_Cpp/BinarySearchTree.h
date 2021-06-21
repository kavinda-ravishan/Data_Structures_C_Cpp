#pragma once

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
	bool IsBinarySearchTree(BinaryTreeNode<T>* rootPtr) const;
	bool IsSubTreeGeater(BinaryTreeNode<T>* rootPtr, T data) const;
	bool IsSubTreeLesser(BinaryTreeNode<T>* rootPtr, T data) const;
	bool IsBinarySearchTree(BinaryTreeNode<T>* rootPtr, T minValue, T maxValue) const;
	BinaryTreeNode<T>* Delete(BinaryTreeNode<T>* rootPtr, T data);
public:
	BinarySearchTree();
	BinaryTreeNode<T>* GetRoot() const;
	void Insert(T data);
	void InsertRec(T data);
	bool Search(T data) const;
	BinaryTreeNode<T>* Find(T data) const;
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
	bool IsBinarySearchTreeRec() const;
	bool IsBinarySearchTree(T minValue, T maxValue) const;
	void Delete(T data);
	BinaryTreeNode<T>* GetSuccessor(T data);
};

class BinarySearchTreeTest {
public:
	static void Insert_Search_Max_Min_Test();
	static void Print_Postorder_Preorder_Inorder_Levelorder_Test();
	static void Find_Height_Test();
	static void Traverse_Test();
	static void Is_Binary_Search_Tree_Test();
	static void Delete_Test();
	static void Find_Successor_Test();
	static void Test_All();
};