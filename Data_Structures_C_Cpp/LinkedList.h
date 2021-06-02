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
	void EnQueue(T data); // push
	void DeQueue(); // pop
	T Front() const; // peek
	bool IsEmpty() const;
};

template<typename T, const int Size>
class QueueArray {
private:
	T m_queue[Size];
	int m_front;
	int m_rear;
public:
	QueueArray() :m_front(-1), m_rear(-1) {}
	void Traverse(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const;
	void TraverseArray(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const;
	void EnQueue(T data); // push
	void DeQueue(); // pop
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

static class StackQueuTest {
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
