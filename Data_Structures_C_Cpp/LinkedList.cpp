#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() :m_head(nullptr) {}

Node* LinkedList::getNthPointer(int index) {

	Node* temp = m_head;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp;
}

Node* LinkedList::getHead() {
	return m_head;
}

int LinkedList::getElement(int index) {

	return getNthPointer(index)->data;
}

void LinkedList::Insert(int data) {

	Node* temp = new Node;
	temp->data = data;
	temp->next = m_head;
	m_head = temp;
}

void LinkedList::Insert(int data, int index) {

	Node *temp = new Node();
	temp->data = data;
	temp->next = nullptr;

	if (index == 0) {
		temp->next = m_head;
		m_head = temp;
		return;
	}

	Node* temp2 = getNthPointer(index - 1);
	temp->next = temp2->next;
	temp2->next = temp;
}

void LinkedList::Delete(int index) {

	if (index == 0) {
		Node* temp = m_head;
		m_head = temp->next;
		delete temp;
		return;
	}

	Node* temp = getNthPointer(index - 1);
	Node* temp2 = temp->next;

	temp->next = temp2->next;
	delete temp2;
}

void LinkedList::Reverse() {

	Node* current = m_head;
	Node* prev = nullptr;
	Node* next = nullptr;

	while (current != nullptr)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	m_head = prev;
}

void LinkedList::Traverse(void(*callback)(int data), void(*callbackStart)(), void(*callbackEnd)()) {

	callbackStart();

	Node* temp = m_head;

	while (temp != nullptr) {

		callback(temp->data);
		temp = temp->next;
	}

	callbackEnd();
}


void LinkedListTest::PrintList(LinkedList list) {
	list.Traverse(
		[](int data) { std::cout << data << " "; },
		[]() { std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
}

void LinkedListTest::InsertToHeadTest() {

	std::cout << " --- Insert To Head --- " << std::endl;

	LinkedList list;

	list.Insert(2);
	PrintList(list);
	list.Insert(4);
	PrintList(list);
	list.Insert(6);
	PrintList(list);
	list.Insert(5);
	PrintList(list);

	int index = 0;

	std::cout << "Value of index ( " << index << " ) : " << list.getElement(0) << std::endl;
	std::cout << std::endl;
}

void LinkedListTest::InsertToNthNodeTest() {

	std::cout << " --- Insert To Nth Node --- " << std::endl;

	LinkedList list;

	list.Insert(2, 0);
	PrintList(list);
	list.Insert(3, 1);
	PrintList(list);
	list.Insert(4, 0);
	PrintList(list);
	list.Insert(5, 1);
	PrintList(list); //4, 5, 2, 3

	std::cout << std::endl;
}

void LinkedListTest::DeleteNthNodeTest() {

	std::cout << " --- Delete Nth Node --- " << std::endl;

	LinkedList list;

	list.Insert(2);
	list.Insert(4);
	list.Insert(6);
	list.Insert(5);
	PrintList(list);

	list.Delete(1);
	PrintList(list);

	list.Delete(0);
	PrintList(list);

	list.Delete(1);
	PrintList(list);

	std::cout << std::endl;
}

void LinkedListTest::ReverseTheListTest() {

	std::cout << " --- Reverse The List --- " << std::endl;

	LinkedList list;

	list.Insert(2);
	list.Insert(4);
	list.Insert(6);
	list.Insert(5);
	PrintList(list);

	list.Reverse();
	PrintList(list);

	std::cout << std::endl;
}

void LinkedListTest::PrintRecursively(Node* p) {

	if (p == nullptr) return;
	std::cout << p->data << " ";
	PrintRecursively(p->next);
}

void LinkedListTest::PrintRecursivelyInReverseOrder(Node* p) {

	if (p == nullptr) return;
	PrintRecursivelyInReverseOrder(p->next);
	std::cout << p->data << " ";
}

void LinkedListTest::PrintRecursivelyTest() {

	std::cout << " --- Print Recursively --- " << std::endl;

	LinkedList list;

	list.Insert(2);
	list.Insert(4);
	list.Insert(6);
	list.Insert(5);

	std::cout << "List : ";
	PrintRecursively(list.getHead());

	std::cout << std::endl;

	std::cout << "List In Reverse Order: ";
	PrintRecursivelyInReverseOrder(list.getHead());

	std::cout << std::endl;
	std::cout << std::endl;
}

void LinkedListTest::ReverseTheListRecursively(Node* p, LinkedList* list) {

	while (p->next == nullptr)
	{
		list->updateHead(p);
		return;
	}
	ReverseTheListRecursively(p->next, list);
	p->next->next = p;
	p->next = nullptr;
}

void LinkedListTest::ReverseTheListRecursivelyTest() {
	std::cout << " --- Reverse The List Recursively --- " << std::endl;

	LinkedList list;

	list.Insert(2);
	list.Insert(4);
	list.Insert(6);
	list.Insert(5);

	PrintList(list);

	ReverseTheListRecursively(list.getHead(), &list);

	PrintList(list);
}

