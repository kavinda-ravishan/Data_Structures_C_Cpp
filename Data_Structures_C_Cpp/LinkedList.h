#pragma once

struct Node
{
	Node* next;
	int data;
};

class LinkedList {
private:
	Node* m_head;
	Node* getNthPointer(int index);
public:
	LinkedList();
	Node* getHead();
	void updateHead(Node* p) {
		m_head = p;
	}
	int getElement(int index);
	void Insert(int data, int index);
	void Insert(int data);
	void Delete(int index);
	void Reverse();
	void Traverse(void(*callback)(int data), void(*callbackStart)(), void(*callbackEnd)());
};

static class LinkedListTest {
public:
	static void PrintList(LinkedList list);
	static void InsertToHeadTest();
	static void InsertToNthNodeTest();
	static void DeleteNthNodeTest();
	static void ReverseTheListTest();
	static void PrintRecursively(Node* p);
	static void PrintRecursivelyInReverseOrder(Node* p);
	static void PrintRecursivelyTest();
	static void ReverseTheListRecursively(Node* p, LinkedList* list);
	static void ReverseTheListRecursivelyTest();
};
