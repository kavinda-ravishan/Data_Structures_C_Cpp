#pragma once

struct NodeS
{
	NodeS* next;
	int data;
};

class SinglyLinkedList {
private:
	NodeS* m_head;
	NodeS* getNthPointer(int index);
public:
	SinglyLinkedList();
	NodeS* getHead();
	void updateHead(NodeS* p);
	int getElement(int index);
	void Insert(int data, int index);
	void Insert(int data);
	void Delete(int index);
	void Reverse();
	void Traverse(void(*callback)(int data), void(*callbackStart)(), void(*callbackEnd)());

	int getMiddleElement();
};

static class SinglyLinkedListTest {
public:
	static void PrintList(SinglyLinkedList list);
	static void InsertToHeadTest();
	static void InsertToNthNodeTest();
	static void DeleteNthNodeTest();
	static void ReverseTheListTest();
	static void PrintRecursively(NodeS* p);
	static void PrintRecursivelyInReverseOrder(NodeS* p);
	static void PrintRecursivelyTest();
	static void ReverseTheListRecursively(NodeS* p, SinglyLinkedList* list);
	static void ReverseTheListRecursivelyTest();
	static void getMiddleElementTest();
};
