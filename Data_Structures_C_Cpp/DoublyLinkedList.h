#pragma once

template <typename T>
struct NodeD
{
	T data;
	NodeD<T>* nextPtr;
	NodeD<T>* prevPtr;
};

template <typename T>
class DoublyLinkedList {

private:
	NodeD<T>* m_headPtr;
	NodeD<T>* m_tailPtr;
	NodeD<T>* GetNewNode(T data);
public:
	DoublyLinkedList();

	void TraverseHeadToTail(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)());
	void TraverseTailToHead(void(*callback)(T data), void(*callbackStart)(), void(*callbackEnd)());
	void InsertAtHead(T data);
	void InsertAtTail(T data);
};

static class DoublyLinkedListTest {
public:
	template <typename T>
	static void PrintListHeadToTail(DoublyLinkedList<T> list);
	template <typename T>
	static void PrintListTailToHead(DoublyLinkedList<T> list);
	static void InsetAtHeadTest();
	static void InsetAtTailTest();
	static void TestAll();
};