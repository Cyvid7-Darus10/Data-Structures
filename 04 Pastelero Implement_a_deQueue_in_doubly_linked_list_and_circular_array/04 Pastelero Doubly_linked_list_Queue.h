#include <iostream>
#include <cstdlib>

using namespace std;

//Last update: OCT 12, 2020, 6:39PM
/*
		    'Doubly nexted List'
Name: Cyrus David G. Pastelero
Subject: CMSC 123 - Data Structures

Code Description:
A doubly nexted list is a more complex type of nexted list,
which contains a pointer to the next as well as the previous 
Node in the sequence. This allows for reverse traversal anywhere in list.
*/

//the structure of the doubly nexted list
template <class T>
class Node 
{
	public:
		T data;
		Node* next;
		Node* prev;
};

//class definition
template <class T>
class Doubly_Stack 
{
	private:
		Node<T> *front;
		Node<T> *rear;
		int numNode; //for counting the number of Nodes
	public:

		//initialization
		Doubly_Stack() {	front = NULL;
					rear = NULL;
					numNode = -1; }; //-1 because index is starting at 0. 
							//Adding a Node will put it at 0 index.

		//insertion functions
		void insertFront(T); //O(1)
		void enQueue(T); //O(1)
		void insertAtPos(T, int); //O(n)

		//deletions functions
		void deQueue(); //O(1)
		void deleteBack(); //O(1)
		void deleteAtPos(int); //O(n)
		void deleteSpecific(T); //O(n)

		//extra functions
		void listNode(); //O(n)
		void listNodeBack(); //O(n)
		void findNode(T); //O(n)
		bool isEmpty(); //O(1)
		int size(); //O(1)
		void deleteAll(); //O(1)used after exiting the singly nexted list
		T wBack(); //O(1)
		T wFront(); //O(1)
	
		

		//destructor
		~Doubly_Stack(){};
};

template <class T>
void Doubly_Stack<T>::insertFront(T val) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	newNode->prev = NULL;

	if (front == NULL) 
	{
		newNode->next = NULL;
		front = rear = newNode;
	} 
	else 
	{
		newNode->next = front;
		front->prev = newNode;
		front = newNode;
	}
	cout << "\n[SUCCESS: Inserting at Beginning]\n";
	numNode++;
}

template <class T>
void Doubly_Stack<T>::enQueue(T val) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	newNode->next = NULL;

	if (front == NULL) 
	{
		insertFront(val);
	} 
	else 
	{
		Node<T> *copy = rear;
		copy->next = newNode;
		newNode->prev = copy;
		rear = newNode;
		cout << "\n[SUCCESS: Enueueing]\n";
		numNode++;
	}
}

template <class T>
void Doubly_Stack<T>::insertAtPos(T val, int pos) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;	

	if (pos == 0) 
	{
		//since it is the first Node
		insertFront(val);
	} 
	else if (numNode + 1 == pos) 
	{
		enQueue(val);
	}
	else if (numNode < pos) 
	{
		cout << "[Exceeds limit]\n";
		return;
	} 
	else 
	{
		Node<T> *copy = front;
		for (int i = 0; i < pos - 1; i++) 
		{
			copy = copy->next;
		}

		newNode->next = copy->next;
		copy->next->prev = newNode;
		copy->next = newNode;
		newNode->prev = copy;
		cout << "\n[SUCCESS: Inserting " << val << " at position " << pos << "]\n"; 
		numNode++;
	}
}

template <class T>
void Doubly_Stack<T>::deQueue() 
{
	//If front is NULL = True else if NULL = False
	if (!front) 
	{
		cout << "[Already Empty]\n";
	} 
	else 
	{
		T data;
		Node<T> *copy = front;
		if (front == rear) //means it is the last Node
		{
			data = front->data;
			front = rear = NULL;
			free(copy);
		}
		else 
		{
			data = copy->data;
			front = copy->next;
			front->prev = NULL;
			free(copy);
		}	
		cout << "\n[SUCCESS: Dequeueing " << data << " at beginning.]\n";
		numNode--;
	}
}

template <class T>
void Doubly_Stack<T>::deleteBack() 
{
	if (front == NULL) 
	{
		cout << "[Already Empty.]\n";
	} 
	else 
	{
		T data;
		Node<T> *copy = rear;
		if (rear == front) //means it is the last Node
		{
			data = front->data;
			front = rear = NULL;
			free(copy);
		} 
		else 
		{
			data = copy->data;
			rear = copy->prev;
			rear->next = NULL;
			free(copy);
		}	
		cout << "\n[SUCCESS: Deleting " << data << " at end.]\n";
		numNode--;
	}
}

template <class T>
void Doubly_Stack<T>::deleteAtPos(int pos) 
{
	if (pos < 0)
	{
		cout << "[Cannot access this position.]\n";
		return;
	}
	else if (front == NULL) 
	{
		cout << "[Already Empty.]\n";
	} 
	else if (pos == 0) 
	{
		deQueue();
	} 
	else if (pos == numNode) 
	{
		deleteBack();
	} 
	else if (numNode < pos) 
	{
		cout << "exceeds limit\n";
	}
	else 
	{
		Node<T> *copy = front;
		for (int i = 0; i < pos - 1; i++) 
		{
			copy = copy->next;
		}
		Node<T>* temp = copy->next;
		T data = temp->data;
		copy->next->next->prev = copy;
		copy->next = copy->next->next;

		free(temp);
		cout << "\n[SUCCESS: Deleting " << data << " at position " << pos << ".]" << endl;
		numNode--;
	}
}

template <class T>
void Doubly_Stack<T>::deleteSpecific(T val) 
{
	if (front == NULL) 
	{
		cout << "[The List is Empty]\n";
	} 
	else 
	{
		cout << "\n[NOTE]First number that match is to be deleted.\n";
		int pos = 0;
		Node<T> *copy = front;
		while (copy->data != val) 
		{
			pos++;
			if (!copy->next) 
			{
				cout << "[Does not exit.]\n";
				return;
			}
			copy = copy->next;
		}

		if (copy == front) 
		{
			deQueue();
		} 
		else if (!copy->next) 
		{
			deleteBack();
		} 
		else 
		{
			copy->next->prev = copy->prev;
			copy->prev->next = copy->next;
			free(copy);
			cout << "[NOTE]Position starts at ZERO.\n";
			cout << "[SUCCESS: Deleting " << val << " at position " << pos << ".]" << endl;
			numNode--; 
		}
	}
}

template <class T>
void Doubly_Stack<T>::listNode() 
{
	if (front == NULL) 
	{
		cout << "[Empty List]\n";
		return;
	}
	int pos = 0;
	cout << "Queue:\n"
		 << "Position\tValue\n";
 	Node<T> *copy = front;
	while (copy) 
	{
		cout << "------------------------------\n"
			 << "    " << pos << "     |      " << copy->data << endl;
		pos++;
		copy = copy->next;
	}
	cout << "------------------------------\n";
}

template <class T>
void Doubly_Stack<T>::listNodeBack() 
{
	if (front == NULL) 
	{
		cout << "[Empty List]\n";
		return;
	}
	int pos = size() - 1;
	cout << "Queue:\n"
	<< "Position\tValue\n";
	Node<T> *copy = rear;
	while (copy) 
	{
		cout << "------------------------------\n"
			 << "    " << pos << "     |      " << copy->data << endl;
		pos--;
		copy = copy->prev;
	}
	cout << "------------------------------\n";
}

template <class T>
void Doubly_Stack<T>::findNode(T val) 
{
	Node<T> *copy = front;
	int pos = 0;
	bool notFound = true;
	cout << "\n[NOTE]Position starts at ZERO.\n";
	while (copy) 
	{
		if (copy->data == val) 
		{
			cout << "|Found at position: " << pos << " |\n";	
			notFound = false;
		}
		pos++;
		copy = copy->next;
	}

	if(notFound)
	{
		cout << "[Not Found!]\n";
	}
}

template <class T>
bool Doubly_Stack<T>::isEmpty() 
{
	if (front != NULL) 
		return false;
	return true;
}

template <class T>
int Doubly_Stack<T>::size()
{
	return numNode + 1;
}

template <class T>
void Doubly_Stack<T>::deleteAll()
{
	Node<T>* copy = front;
	while (copy)
	{
		front = copy->next;
		free(copy);
		copy = front;
	}
	numNode = -1;
}

template <class T>
T Doubly_Stack<T>::wBack() {
	return rear->data;
}

template <class T>
T Doubly_Stack<T>::wFront() {
	return front->data;
}
