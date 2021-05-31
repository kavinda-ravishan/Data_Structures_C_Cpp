#include <iostream>
//#include "SinglyLinkedList.h"
//#include "DoublyLinkedList.h"

template <typename T>
struct Node
{
	T m_data;
	Node<T>* m_nextPtr;

	Node(T data):m_nextPtr(nullptr),m_data(data){}
};

template <typename T>
class LinkedList{
protected:
	Node<T>* m_headPtr;
	Node<T>* GetANewNode(T data) const;
public:
	LinkedList();
	void Traverse(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const;
	void Traverse(T(*callback)(T data, int index)) const;
};

template <typename T>
class Stack : public LinkedList<T>{
public:
	bool isEmpty() const;
	void Push(T data);
	void Pop();
	T Top() const;
	void Reverse();
};

void Test();

bool CheckBalancedParentheses(const char *expression, Stack<char> &stack);
void CheckBalancedParenthesesTest();

int charToInt(char c);
int Operation(int operand_1, int operand_2, char operator_char);
void PostfixEvaluation();
void PrefixEvaluation();

void CycleDetectionAlgorithm();

enum Operators
{
	Subtraction = 0,
	Addition,
	Division,
	Multiplication,
	Undefined
};
Operators GetOperator(char c) {

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
void InfixToPostfix();


int main(int argc, char** args) {
	
	InfixToPostfix();

	//CycleDetectionAlgorithm();
	//PrefixEvaluation();
	//PostfixEvaluation();
	//CheckBalancedParenthesesTest();
	//Test();

	return 0;
}

// --- LinkedList --- //

template<typename T>
LinkedList<T>::LinkedList() :m_headPtr(nullptr) {}

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
bool Stack<T>::isEmpty() const
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
	while (!stack.isEmpty())
	{
		tempPtr->m_nextPtr = stack.Top();
		stack.Pop();
		tempPtr = tempPtr->m_nextPtr;
	}
	tempPtr->m_nextPtr = nullptr;
}



void Test()
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
	std::cout << "Is the list Empty : " << stack.isEmpty() << std::endl;
	std::cout << "Top : " << stack.Top() << std::endl;

	stack.Reverse();
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.isEmpty() << std::endl;
	std::cout << "Top : " << stack.Top() << std::endl;

	stack.Traverse([](int data, int index) { return data + index; });
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);

	std::cout << "Poped items : ";
	while(!stack.isEmpty()){
		stack.Pop();
	}
	std::cout << std::endl;
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.isEmpty() << std::endl;
	std::cout << "Top : " << stack.Top() << std::endl;

	for (int i = 0; i < 20; i++) {
		stack.Push(i * 10);
	}
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.isEmpty() << std::endl;
	std::cout << "Top : " << stack.Top() << std::endl;
}

bool CheckBalancedParentheses(const char *expression, Stack<char> &stack) {
	int i = 0;

	while (expression[i] != 0)
	{
		char c = expression[i];

		if (c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}') {
			if (c == '[' || c == '(' || c == '{') {
				stack.Push(c);
			}
			else {
				if (stack.isEmpty()) {
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

	if (stack.isEmpty()) return true;
	else return false;
}

void CheckBalancedParenthesesTest() {

	Stack<char> stack;

	const char* text = "{ [ (a+b) + (b+c) ] }";

	CheckBalancedParentheses(text, stack);

	if (stack.isEmpty()) {
		std::cout << "Balanced" << std::endl;
	}
	else
	{
		std::cout << "Not Balanced" << std::endl;
	}

}

int charToInt(char c) {

	return (int)c - 48;
}

int Operation(int operand_1, int operand_2, char operator_char) {
	if (operator_char == '+') return operand_1 + operand_2;
	if (operator_char == '-') return operand_1 - operand_2;
	if (operator_char == '*') return operand_1 * operand_2;
}

void PostfixEvaluation() {

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

void PrefixEvaluation()
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

void CycleDetectionAlgorithm() {
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

void InfixToPostfix()
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
			while (!stack.isEmpty() && (GetOperator(stack.Top()) > GetOperator(expression[i])) && stack.Top() != '(')
			{
				postfix.Push(stack.Top());
				stack.Pop();
			}
			stack.Push(expression[i]);
		}
	}
	while (!stack.isEmpty())
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
