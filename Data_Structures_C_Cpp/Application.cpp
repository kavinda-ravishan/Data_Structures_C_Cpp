#include <iostream>
#include "LinkedList.h"
#include "DoublyLinkedList.h"


int main(int argc, char** args) {
	
	LinkedListTest::InsertToHeadTest();
	LinkedListTest::InsertToNthNodeTest();
	LinkedListTest::DeleteNthNodeTest();
	LinkedListTest::ReverseTheListTest();
	LinkedListTest::PrintRecursivelyTest();
	LinkedListTest::ReverseTheListRecursivelyTest();
	LinkedListTest::getMiddleElementTest();

	DoublyLinkedListTest::InsetAtHeadTest();
	DoublyLinkedListTest::InsetAtTailTest();

	return 0;
}