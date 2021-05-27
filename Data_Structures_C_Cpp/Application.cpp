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
};

template <typename T>
class List :public Stack<T>{
private:
	Node<T>* GetNthPtr(int index) const;
};

int main(int argc, char** args) {
	

	Stack<int> stack;
	for (int i = 0; i < 20; i++) {
		stack.Push(i*11);
	}
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


	for (int i = 0; i < 30; i++) {
		stack.Pop();
	}
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
	std::cout << "Top : " << list.Top() << std::endl;
	
	list.Pop();
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << list.isEmpty() << std::endl;
	std::cout << "Top : " << list.Top() << std::endl;

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
	std::cout << "Top : " << list.Top() << std::endl;

	list.Pop();
	list.Pop();
	list.Pop();
	list.Pop();
	list.Pop();
	list.Traverse(
		[](char data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
	std::cout << "Is the list Empty : " << list.isEmpty() << std::endl;
	std::cout << "Top : " << list.Top() << std::endl;
	
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
	this->m_headPtr = this->m_headPtr->m_nextPtr;
	delete deleteNode;
}

template<typename T>
T Stack<T>::Top() const
{
	if (this->m_headPtr == nullptr) return T();
	return this->m_headPtr->m_data;
}

// --- List --- //

template<typename T>
Node<T>* List<T>::GetNthPtr(int index) const
{
	Node<T> *temp = this->m_headPtr;
	for (int i = 0; i < index; i++)
	{
		temp = temp->m_nextPtr;
	}

	return temp;
}