#include <iostream>

struct Node
{
	Node* next;
	int data;
};

class LinkList {
private:
	Node* m_head;
	
public:
	
	LinkList();

	Node* getNthPointer(int index);

	void Insert(int data, int index);

	void Insert(int data);

	void Delete(int index);

	void Print();
};

void InsertToHeadTest();
void InsertToNthNode();
void DeleteNthNode();

int main(int argc, char** args) {

	InsertToHeadTest();
	InsertToNthNode();
	DeleteNthNode();

	return 0;
}


LinkList::LinkList() :m_head(nullptr) {}

Node* LinkList::getNthPointer(int index) {

	Node* temp = m_head;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp;
}

void LinkList::Insert(int data) {

	Node* temp = new Node;
	temp->data = data;
	temp->next = m_head;
	m_head = temp;
}

void LinkList::Insert(int data, int index) {

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

void LinkList::Delete(int index) {

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

void LinkList::Print() {

	Node* temp = m_head;

	std::cout << "List is : ";
	while (temp != nullptr) {

		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}


void InsertToHeadTest() {

	LinkList list;

	list.Insert(2);
	list.Print();
	list.Insert(4);
	list.Print();
	list.Insert(6);
	list.Print();
	list.Insert(5);
	list.Print();

	int index = 0;

	std::cout << "Value of index ( " << index << " ) : " << list.getNthPointer(0)->data << std::endl;
}

void InsertToNthNode() {

	LinkList list;

	list.Insert(2, 0);
	list.Insert(3, 1);
	list.Insert(4, 0);
	list.Insert(5, 1);
	list.Print(); //4, 5, 2, 3
}

void DeleteNthNode() {

	LinkList list;

	list.Insert(2);
	list.Insert(4);
	list.Insert(6);
	list.Insert(5);
	list.Print();

	list.Delete(1);
	list.Print();

	list.Delete(0);
	list.Print();

	list.Delete(1);
	list.Print();

}
