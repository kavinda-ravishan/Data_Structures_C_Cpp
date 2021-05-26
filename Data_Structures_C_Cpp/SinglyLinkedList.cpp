#include <iostream>
#include "SinglyLinkedList.h"

// --------------- Class --------------- //

SinglyLinkedList::SinglyLinkedList() :m_head(nullptr) {}

NodeS* SinglyLinkedList::getNthPointer(int index) {

	NodeS* temp = m_head;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp;
}

NodeS* SinglyLinkedList::GetHead() {
	return m_head;
}

void SinglyLinkedList::UpdateHead(NodeS* p) {
	m_head = p;
}

int SinglyLinkedList::GetElement(int index) {

	return getNthPointer(index)->data;
}

void SinglyLinkedList::Insert(int data) {

	NodeS* temp = new NodeS;
	temp->data = data;
	temp->next = m_head;
	m_head = temp;
}

void SinglyLinkedList::Insert(int data, int index) {

	NodeS *temp = new NodeS();
	temp->data = data;
	temp->next = nullptr;

	if (index == 0) {
		temp->next = m_head;
		m_head = temp;
		return;
	}

	NodeS* temp2 = getNthPointer(index - 1);
	temp->next = temp2->next;
	temp2->next = temp;
}

void SinglyLinkedList::Delete(int index) {

	if (index == 0) {
		NodeS* temp = m_head;
		m_head = temp->next;
		delete temp;
		return;
	}

	NodeS* temp = getNthPointer(index - 1);
	NodeS* temp2 = temp->next;

	temp->next = temp2->next;
	delete temp2;
}

void SinglyLinkedList::Reverse() {

	NodeS* current = m_head;
	NodeS* prev = nullptr;
	NodeS* next = nullptr;

	while (current != nullptr)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	m_head = prev;
}

void SinglyLinkedList::Traverse(void(*callback)(int data), void(*callbackStart)(), void(*callbackEnd)()) {

	callbackStart();

	NodeS* temp = m_head;

	while (temp != nullptr) {

		callback(temp->data);
		temp = temp->next;
	}

	callbackEnd();
}

int SinglyLinkedList::GetMiddleElement() {

	if (m_head == nullptr) return 0;

	NodeS* fast = m_head;
	NodeS* slow = m_head;

	while (fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast == nullptr) break;
	}

	return slow->data;
}

// --------------- Test --------------- //

void SinglyLinkedListTest::PrintList(SinglyLinkedList list) {
	list.Traverse(
		[](int data) { std::cout << data << " "; },
		[]() { std::cout << "List : "; },
		[]() {std::cout << std::endl; }
	);
}

void SinglyLinkedListTest::InsertToHeadTest() {

	std::cout << " --- Insert To Head --- " << std::endl;

	SinglyLinkedList list;

	list.Insert(2);
	PrintList(list);
	list.Insert(4);
	PrintList(list);
	list.Insert(6);
	PrintList(list);
	list.Insert(5);
	PrintList(list);

	int index = 0;

	std::cout << "Value of index ( " << index << " ) : " << list.GetElement(0) << std::endl;
	std::cout << std::endl;
}

void SinglyLinkedListTest::InsertToNthNodeTest() {

	std::cout << " --- Insert To Nth Node --- " << std::endl;

	SinglyLinkedList list;

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

void SinglyLinkedListTest::DeleteNthNodeTest() {

	std::cout << " --- Delete Nth Node --- " << std::endl;

	SinglyLinkedList list;

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

void SinglyLinkedListTest::ReverseTheListTest() {

	std::cout << " --- Reverse The List --- " << std::endl;

	SinglyLinkedList list;

	list.Insert(2);
	list.Insert(4);
	list.Insert(6);
	list.Insert(5);
	PrintList(list);

	list.Reverse();
	PrintList(list);

	std::cout << std::endl;
}

void SinglyLinkedListTest::PrintRecursively(NodeS* p) {

	if (p == nullptr) return;
	std::cout << p->data << " ";
	PrintRecursively(p->next);
}

void SinglyLinkedListTest::PrintRecursivelyInReverseOrder(NodeS* p) {

	if (p == nullptr) return;
	PrintRecursivelyInReverseOrder(p->next);
	std::cout << p->data << " ";
}

void SinglyLinkedListTest::PrintRecursivelyTest() {

	std::cout << " --- Print Recursively --- " << std::endl;

	SinglyLinkedList list;

	list.Insert(2);
	list.Insert(4);
	list.Insert(6);
	list.Insert(5);

	std::cout << "List : ";
	PrintRecursively(list.GetHead());

	std::cout << std::endl;

	std::cout << "List In Reverse Order: ";
	PrintRecursivelyInReverseOrder(list.GetHead());

	std::cout << std::endl;
	std::cout << std::endl;
}

void SinglyLinkedListTest::ReverseTheListRecursively(NodeS* p, SinglyLinkedList* list) {

	while (p->next == nullptr)
	{
		list->UpdateHead(p);
		return;
	}
	ReverseTheListRecursively(p->next, list);
	p->next->next = p;
	p->next = nullptr;
}

void SinglyLinkedListTest::ReverseTheListRecursivelyTest() {
	std::cout << " --- Reverse The List Recursively --- " << std::endl;

	SinglyLinkedList list;

	list.Insert(2);
	list.Insert(4);
	list.Insert(6);
	list.Insert(5);

	PrintList(list);

	ReverseTheListRecursively(list.GetHead(), &list);

	PrintList(list);

	std::cout << std::endl;
}

void SinglyLinkedListTest::GetMiddleElementTest()
{
	std::cout << " --- Get Middle ElementT --- " << std::endl;

	SinglyLinkedList list;

	list.Insert(1);
	list.Insert(2);
	list.Insert(3);
	list.Insert(4);
	list.Insert(5);
	list.Insert(6);
	list.Insert(7);

	SinglyLinkedListTest::PrintList(list);

	std::cout << "Middle Element : " << list.GetMiddleElement() << std::endl;
	std::cout << std::endl;
}

void SinglyLinkedListTest::TestAll()
{
	InsertToHeadTest();
	InsertToNthNodeTest();
	DeleteNthNodeTest();
	ReverseTheListTest();
	PrintRecursivelyTest();
	ReverseTheListRecursivelyTest();
	GetMiddleElementTest();
}
