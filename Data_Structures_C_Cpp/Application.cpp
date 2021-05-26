#include <iostream>
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"


int main(int argc, char** args) {
	
	SinglyLinkedListTest::InsertToHeadTest();
	SinglyLinkedListTest::InsertToNthNodeTest();
	SinglyLinkedListTest::DeleteNthNodeTest();
	SinglyLinkedListTest::ReverseTheListTest();
	SinglyLinkedListTest::PrintRecursivelyTest();
	SinglyLinkedListTest::ReverseTheListRecursivelyTest();
	SinglyLinkedListTest::getMiddleElementTest();

	DoublyLinkedListTest::InsetAtHeadTest();
	DoublyLinkedListTest::InsetAtTailTest();

	return 0;
}