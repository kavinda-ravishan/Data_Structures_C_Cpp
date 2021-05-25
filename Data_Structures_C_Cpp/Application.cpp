#include <iostream>
#include "LinkedList.h"

template <typename T>
struct NodeD
{
	T data;
	NodeD<T>* nextPtr;
	NodeD<T>* prevPtr;
};

template <typename T>
class DoublyLinkedList{

private:
	NodeD<T>* m_headPtr;
	NodeD<T>* m_tailPtr;
	NodeD<T>* getNewNode(T data);
public:
	DoublyLinkedList();

	void TraverseHeadToTail(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)());

	void TraverseTailToHead(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)());

	void insertAtHead(T data);

	void insertAtTail(T data);
};


template <typename T>
void PrintListHeadToTail(DoublyLinkedList<T> list);
template <typename T>
void PrintListTailToHead(DoublyLinkedList<T> list);
void InsetAtHeadTest();
void InsetAtTailTest();

int main(int argc, char** args) {
	
	InsetAtHeadTest();
	InsetAtTailTest();

	return 0;
}

// --------------- Test --------------- //

template <typename T>
void PrintListHeadToTail(DoublyLinkedList<T> list) {
	list.TraverseHeadToTail(
		[](T data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
}

template <typename T>
void PrintListTailToHead(DoublyLinkedList<T> list) {
	list.TraverseTailToHead(
		[](T data) {std::cout << data << " "; },
		[]() {std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
}

void InsetAtHeadTest() {

	std::cout << " --- Insert At Head --- " << std::endl;

	DoublyLinkedList<double> list;

	list.insertAtHead(10.1);
	list.insertAtHead(20.2);
	list.insertAtHead(30.3);

	PrintListHeadToTail<double>(list);
	PrintListTailToHead<double>(list);

	std::cout << std::endl;
}

void InsetAtTailTest()
{
	std::cout << " --- Insert At Tail --- " << std::endl;

	DoublyLinkedList<double> list;

	list.insertAtTail(101.1);
	list.insertAtTail(202.2);
	list.insertAtTail(303.3);

	PrintListHeadToTail<double>(list);
	PrintListTailToHead<double>(list);

	std::cout << std::endl;
}

// --------------- Test --------------- //

template<typename T>
NodeD<T>* DoublyLinkedList<T>::getNewNode(T data)
{
	NodeD<T>* newNodePtr = new NodeD<T>;
	newNodePtr->nextPtr = nullptr;
	newNodePtr->prevPtr = nullptr;
	newNodePtr->data = data;
	return newNodePtr;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() :m_headPtr(nullptr), m_tailPtr(nullptr) {}

template<typename T>
void DoublyLinkedList<T>::TraverseHeadToTail(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) {

	callbackStart();

	NodeD<T>* tempPtr = m_headPtr;

	while (tempPtr != nullptr)
	{
		callback(tempPtr->data);
		tempPtr = tempPtr->nextPtr;
	}

	callbackEnd();
}

template<typename T>
void DoublyLinkedList<T>::TraverseTailToHead(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)()) {

	callbackStart();

	NodeD<T>* tempPtr = m_tailPtr;

	while (tempPtr != nullptr)
	{
		callback(tempPtr->data);
		tempPtr = tempPtr->prevPtr;
	}

	callbackEnd();
}

template<typename T>
void DoublyLinkedList<T>::insertAtHead(T data) {

	NodeD<T>* newNodePtr = getNewNode(data);

	if (m_headPtr == nullptr) {
		m_headPtr = newNodePtr;
		m_tailPtr = newNodePtr;
		return;
	}
	m_headPtr->prevPtr = newNodePtr;
	newNodePtr->nextPtr = m_headPtr;
	m_headPtr = newNodePtr;
}

template<typename T>
void DoublyLinkedList<T>::insertAtTail(T data)
{
	NodeD<T>* newNodePtr = getNewNode(data);

	if (m_headPtr == nullptr) {
		m_headPtr = newNodePtr;
		m_tailPtr = newNodePtr;
		return;
	}
	m_tailPtr->nextPtr = newNodePtr;
	newNodePtr->prevPtr = m_tailPtr;
	m_tailPtr = newNodePtr;
}
