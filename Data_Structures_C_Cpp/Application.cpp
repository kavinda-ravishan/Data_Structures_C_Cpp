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

int main(int argc, char** args) {

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


	return 0;
}