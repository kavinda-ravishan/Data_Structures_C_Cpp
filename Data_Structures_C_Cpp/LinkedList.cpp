#include <iostream>
#include "LinkedList.h"

// --- LinkedList --- //

template<typename T>
LinkedList<T>::LinkedList() :m_headPtr(nullptr) {}

template<typename T>
LinkedList<T>::~LinkedList(){}

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

// --- Stack --- //

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

// --- Queue --- //

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

// --- Queue Array --- //

template<typename T, const int Size>
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

template<typename T, const int Size>
void QueueArray<T, Size>::TraverseArray(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const
{
	callbackStart();

	for (int i = 0; i < Size; i++)
	{
		callback(m_queue[i]);
	}

	callbackEnd();
}

template<typename T, int Size>
bool QueueArray<T, Size>::IsEmpty() const
{
	if (m_front == -1 && m_rear == -1) return true;
	else return false;
}

template<typename T, int Size>
bool QueueArray<T, Size>::IsFull() const
{
	if ((m_rear + 1) % Size == m_front) return true;
	else return false;
}

template<typename T, int Size>
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

template<typename T, int Size>
void QueueArray<T, Size>::DeQueue()
{
	if (IsEmpty()) return;
	else if (m_front == m_rear) {
		m_front = -1;
		m_rear = -1;
	}
	else m_front = (m_front + 1) % Size;
}

template<typename T, int Size>
T QueueArray<T, Size>::Front() const
{
	if (IsEmpty()) return T();
	else m_queue[m_front];
}

// --- Test --- //

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
