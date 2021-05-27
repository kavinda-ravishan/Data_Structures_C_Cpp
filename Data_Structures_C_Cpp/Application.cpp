#include <iostream>
//#include "SinglyLinkedList.h"
//#include "DoublyLinkedList.h"

template <typename T>
struct Node
{
	T m_data;
	Node<T>* nextPtr;

	Node(T data):nextPtr(nullptr),m_data(data){}
};

template <typename T>
class LinkedList{
protected:
	Node<T>* m_headPtr;
	Node<T>* GetANewNode(T data) const;
public:
	LinkedList();
	void Traverse(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const;
};

template <typename T>
class Stack : public LinkedList<T>{
private:
	bool m_isEmpty;
public:
	Stack();
	bool isEmpty() const;
	void Push(T data);
	void Pop();
};

template <typename T>
class List :public Stack<T>{
private:
	Node<T>* GetNthPtr(int index) const;
};

int main(int argc, char** args) {
	

	Stack<int> stack;
	stack.Push(10);
	stack.Push(20);
	stack.Push(30);
	stack.Push(40);
	stack.Push(50);
	stack.Traverse(
		[](int data) {std::cout << data << " "; }, 
		[]() {std::cout << "List : "; }, 
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.isEmpty() << std::endl;
	

	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Pop();
	stack.Traverse(
		[](int data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << stack.isEmpty() << std::endl;

	List<char> list;
	list.Push('a');
	list.Push('b');
	list.Push('c');
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << list.isEmpty() << std::endl;
	
	list.Pop();
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << list.isEmpty() << std::endl;

	list.Pop();
	list.Pop();
	list.Pop();
	list.Push('a');
	list.Push('b');
	list.Push('c');
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << list.isEmpty() << std::endl;

	list.Pop();
	list.Pop();
	list.Pop();
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << list.isEmpty() << std::endl;
	
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
		ptr = ptr->nextPtr;
	}

	callbackEnd();
}

// --- Stack --- //

template<typename T>
Stack<T>::Stack():m_isEmpty(true){}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return m_isEmpty;
}

template<typename T>
void Stack<T>::Push(T data)
{
	Node<T>* newNodePtr = this->GetANewNode(data);
	newNodePtr->nextPtr = this->m_headPtr;
	this->m_headPtr = newNodePtr;

	m_isEmpty = false;
}

template<typename T>
void Stack<T>::Pop()
{
	Node<T>* deleteNode = this->m_headPtr;
	if (this->m_headPtr == nullptr) return;
	this->m_headPtr = this->m_headPtr->nextPtr;
	delete deleteNode;

	if(this->m_headPtr == nullptr) m_isEmpty = true;
}

// --- List --- //

template<typename T>
Node<T>* List<T>::GetNthPtr(int index) const
{
	Node<T> *temp = this->m_headPtr;
	for (int i = 0; i < index; i++)
	{
		temp = temp->nextPtr;
	}

	return temp;
}