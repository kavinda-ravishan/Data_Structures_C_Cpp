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
	
	LinkList():m_head(nullptr){}

	Node* getNthPointer(int index) {

		Node* temp = m_head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp;
	}

	void Insert(int data, int index) {

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

	void Insert(int data) {

		Node* temp = new Node;
		temp->data = data;
		temp->next = m_head;
		m_head = temp;
	}

	void Print() {

		Node* temp = m_head;

		std::cout << "List is : ";
		while (temp != nullptr) {

			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}
};

void InsertToHeadTest();
void InsertToNthPoint();

int main(int argc, char** args) {

	//InsertToHeadTest();
	InsertToNthPoint();

	return 0;
}

void InsertToHeadTest() {

	LinkList list;

	int n = 0;
	int x = 0;
	std::cout << "how many numbers : ";
	std::cin >> n;

	for (int i = 0; i < n; i++) {

		std::cout << "Enter the number : ";
		std::cin >> x;
		list.Insert(x);
		list.Print();
	}

	std::cout << list.getNthPointer(0)->data << std::endl;
}

void InsertToNthPoint() {

	LinkList list;

	list.Insert(2, 0);
	list.Insert(3, 1);
	list.Insert(4, 0);
	list.Insert(5, 1);
	list.Print(); //4, 5, 2, 3
}