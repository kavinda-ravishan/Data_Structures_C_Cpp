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
	Node<T>* m_tailPtr;
	int m_size;
	Node<T>* GetANewNode(T data) const;
	Node<T>* GetNthPtr(int index) const;
public:
	LinkedList();
	int GetSize() const;
	void Traverse(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) const;
};

template <typename T>
class Stack : public LinkedList<T>{
public:
	void Push(T data);
	void Pop();
};

template <typename T>
class List :public Stack<T>{};

int main(int argc, char** args) {

	Stack<int> stack;
	stack.Push(10);
	stack.Push(20);
	stack.Push(30);
	stack.Push(40);
	stack.Push(50);
	std::cout << "Size : " << stack.GetSize() << std::endl;
	stack.Traverse(
		[](int data) {std::cout << data << " "; }, 
		[]() {std::cout << "List : "; }, 
		[]() {std::cout << std::endl; }
	);

	List<char> list;
	list.Push('a');
	list.Push('b');
	list.Push('c');
	std::cout << "Size : " << list.GetSize() << std::endl;
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	
	list.Pop();
	std::cout << "Size : " << list.GetSize() << std::endl;
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);

	list.Pop();
	list.Pop();
	list.Pop();
	list.Push('a');
	list.Push('b');
	list.Push('c');
	std::cout << "Size : " << list.GetSize() << std::endl;
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);

	return 0;
}

// --- LinkedList --- //

template<typename T>
LinkedList<T>::LinkedList() :m_headPtr(nullptr), m_tailPtr(nullptr), m_size(0) {}

template<typename T>
Node<T>* LinkedList<T>::GetANewNode(T data) const
{
	return new Node<T>(data);
}

template<typename T>
Node<T>* LinkedList<T>::GetNthPtr(int index) const
{
	Node<T> *temp = this->m_headPtr;
	for (int i = 0; i < index; i++)
	{
		temp = temp->nextPtr;
	}

	return temp;
}

template<typename T>
int LinkedList<T>::GetSize() const
{
	return m_size;
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
void Stack<T>::Push(T data)
{
	Node<T>* newNodePtr = this->GetANewNode(data);
	this->m_size++;
	if (this->m_headPtr == nullptr) {
		this->m_headPtr = newNodePtr;
		this->m_tailPtr = newNodePtr;
		return;
	}
	this->m_tailPtr->nextPtr = newNodePtr;
	this->m_tailPtr = newNodePtr;
}

template<typename T>
void Stack<T>::Pop()
{
	if (this->m_headPtr == nullptr) return;
	
	this->m_size--;

	if (this->m_headPtr->nextPtr == nullptr) {
		delete this->m_tailPtr;
		this->m_headPtr = nullptr;
		this->m_tailPtr = nullptr;
		return;
	}

	delete this->m_tailPtr;
	this->m_tailPtr = this->GetNthPtr(this->m_size - 1);
	this->m_tailPtr->nextPtr = nullptr;
}

// --- List --- //