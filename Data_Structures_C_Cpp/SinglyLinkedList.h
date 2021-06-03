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
	NodeS* GetHead();
	void UpdateHead(NodeS* p);
	int GetElement(int index);
	void Insert(int data, int index);
	void Insert(int data);
	void Delete(int index);
	void Reverse();
	void Traverse(void(*callback)(int data), void(*callbackStart)(), void(*callbackEnd)());
	int GetMiddleElement();
};

class SinglyLinkedListTest {
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
	static void GetMiddleElementTest();
	static void TestAll();
};
