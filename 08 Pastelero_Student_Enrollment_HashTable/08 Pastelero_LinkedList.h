#include <iostream>

using namespace std;

template <class T>
class Node 
{
	public:
		T data;
		Node* next;
		Node* prev;
};

template <class T>
class LinkedList
{
	public:
		Node<T> *head;
		Node<T> *tail;
		int numNode; //for counting the number of Nodes
	
		//initialization
		LinkedList() {	head = NULL;
						tail = NULL;
						numNode = -1; }; //-1 because index is starting at 0. 
								//Adding a Node will put it at 0 index.

		//insertion functions
		void insertEnd(T); //O(1)
		void insertBeginning(T val);
		
		//deletions functions
		void deleteBeginning(); //O(1)
		void deleteEnd(); //O(1)
		void deleteAtPos(int); //O(n)

		//extra functions
		bool findNode(int); //O(n)
		int findNodePos(int); //O(n)
		bool isEmpty(); //O(1)
		int size(); //O(1)

		//destructor
		~LinkedList(){};
};

template <class T>
void LinkedList<T>::insertBeginning(T val) {
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	newNode->prev = NULL;

	if (head == NULL) {
		newNode->next = NULL;
		head = tail = newNode;
	} else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	numNode++;
}

template <class T>
void LinkedList<T>::insertEnd(T val) {
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	newNode->next = NULL;

	if (head == NULL) {
		insertBeginning(val);
	} else {
		Node<T> *copy = tail;
		copy->next = newNode;
		newNode->prev = copy;
		tail = newNode;
		numNode++;
	}
}

template <class T>
void LinkedList<T>::deleteBeginning() 
{
	if (!head) {
		return;
	} else {
		T data;
		Node<T> *copy = head;
		if (head == tail) {
			data = head->data;
			head = tail = NULL;
			free(copy);
		} else {
			data = copy->data;
			head = copy->next;
			head->prev = NULL;
			free(copy);
		}	
		numNode--;
	}
}

template <class T>
void LinkedList<T>::deleteEnd() {
	if (!head) {
		return;
	} else {
		T data;
		Node<T> *copy = tail;
		if (tail == head) {
			data = head->data;
			head = tail = NULL;
			free(copy);
		} 
		else {
			data = copy->data;
			tail = copy->prev;
			tail->next = NULL;
			free(copy);
		}	
		numNode--;
	}
}

template <class T>
void LinkedList<T>::deleteAtPos(int pos) {
	if (pos < 0) {
		return;
	}
	else if (head == NULL) {
		return;
	} 
	else if (pos == 0) {
		deleteBeginning();
	} 
	else if (pos == numNode) {
		deleteEnd();
	} 
	else if (numNode < pos) {
		return;
	}
	else 
	{
		Node<T> *copy = head;
		for (int i = 0; i < pos - 1; i++) {
			copy = copy->next;
		}
		Node<T>* temp = copy->next;
		T data = temp->data;
		copy->next->next->prev = copy;
		copy->next = copy->next->next;

		free(temp);
		numNode--;
	}
}


template <class T>
bool LinkedList<T>::findNode(int val)  {
	Node<T> *copy = head;
	while (copy) {
		if (copy->data.first == val) {
			return true;
		}
		copy = copy->next;
	}
	return false;
}

template <class T>
int LinkedList<T>::findNodePos(int val) {
	int pos = 0;
	Node<T> *copy = head;
	while (copy) {
		if (copy->data.first == val) {
			return pos;
		}
		copy = copy->next;
		pos++;
	}
	return 0;
}

template <class T>
bool LinkedList<T>::isEmpty() {
	if (head != NULL) { 
		return false;
	}
	return true;
}

template <class T>
int LinkedList<T>::size() {
	return numNode + 1;
}
