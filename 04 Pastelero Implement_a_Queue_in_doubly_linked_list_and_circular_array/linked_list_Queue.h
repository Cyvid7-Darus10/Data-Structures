#include <iostream>

#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))

using namespace std;

//Last update: OCT 12, 2020, 6:00PM
/*
					'Linked List for Queue'
Name: Cyrus David G. Pastelero
Subject: CMSC 123 - Data Structures

Code Description:
Queue is a linear data structure which unlike the stack is open at both ends.
It follows the FIF(First In First Out) principle, which means that the
element that is inserted first is removed first.
*/

//The structure
template <class T>
class Node {
	public:
		T data;
		Node* link;
};

//Class definitions
template <class T>
class Queue_Linked {
	private:
		Node<T> *front;
		Node<T> *rear;
		int numNode; //for counting the number of nodes
	public:

		//initialization
		Queue_Linked<T>() { front = NULL;
							rear = NULL;
							numNode = -1; }; //starts at negative, for indexing purposes. 
									//Starts at zero when adding a Node.

		//Queue functions
		void enQueue(int); //O(1)
		void deQueue(); //O(1)

		//unused function
		void deleteBack(); //0(n)
		void deleteAtPos(int); //O(n)
		void insertAtPos(int, int); //O(n)
		void insertFront(int); //O(1)

		//extra functions
		void listNode(); //O(n)
		void findNode(T); //O(n)
		bool isEmpty(); //O(1)
		int size(); //O(1)
		void deleteAll(); //O(1)used after exiting the singly linked list
		T wBack(); //O(1)
		T wFront(); //O(1)
		
		//destructor
		~Queue_Linked<T>(){};
};

template <class T>
void Queue_Linked<T>::insertFront(int val) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;

	//if the front pointer is empty, make newNode as front
	if (front == NULL) 
	{
		newNode->link = NULL;
		front = rear = newNode;
	} 
	else 
	{
		newNode->link = front;
		front = newNode;
	}
	
	numNode++;
	cout << "\n[SUCCESS: Inserting at front]\n";
}

template <class T>
void Queue_Linked<T>::enQueue(int val) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	newNode->link = NULL;
	
	//if the front pointer is empty, make newNode as front
	if (front == NULL) 
	{
		front = rear = newNode;
	} 
	else 
	{
		Node<T> *copy = rear;
		copy->link = newNode;
		rear = newNode;
	}

	numNode++;
	cout << "\n[SUCCESS: Enqueueing]\n";
}

template <class T>
void Queue_Linked<T>::insertAtPos(int val, int pos) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;

	if (pos == 0) 
	{
		insertFront(val);
	} 
	else if (size() == pos) 
	{
		enQueue(val); 
	} 
	else if (size() <= pos) 
	{
		cout << "exceeds limit\n";
	} 
	else 
	{
		Node<T> *copy = front;

		rep (i, pos -1)
		{
			copy = copy->link;
		}
		
		//inserting the Node
		newNode->link = copy->link;
		copy->link = newNode;

		cout << "\n[SUCCESS: Inserting " << val << " at position " << pos << ".]\n"; 
		numNode++;
	}
}

template <class T>
void Queue_Linked<T>::deQueue() 
{
	if (front == NULL) 
	{
		cout << "[Already Empty]\n";
	} 
	else 
	{
		Node<T> *copy = front;
		int data = copy->data;
		if (copy->link == NULL) 
		{
			front = NULL;
			free(copy);
		} 
		else 
		{
			front = copy->link;
			free(copy);
		}	
		cout << "\n[SUCCESS: Dequeueing " << data << ".]\n";
		numNode--;
	}
}

template <class T>
void Queue_Linked<T>::deleteBack() 
{
	if (front == NULL) 
	{
		cout << "[Already Empty]\n";
	} 
	else 
	{
		int data;
		Node<T> *copy = front;
		if (copy->link == NULL) 
		{
			data = front->data;
			front = NULL;
		} 
		else 
		{
			while (copy) 
			{
				if (copy->link->link == NULL) 
				{
					copy->link = NULL;
					rear = copy;
				}
				data = copy->data;
				copy = copy->link;
			}
		}
		free(copy);	
		cout << "\n[SUCCESS: Deleting " << data << " at rear.]\n";
		numNode--;
	}
}

template <class T>
void Queue_Linked<T>::deleteAtPos(int pos) 
{
	Node<T> *copy = front;
	if (pos < 0)
	{
		cout << "[Cannot Access]\n";
	}
	else if (front == NULL) 
	{
		cout << "[Already Empty]\n";
	} 
	else if (pos == 0) 
	{
		deQueue();
	} 
	else if (pos == numNode) 
	{
		deleteBack();
	} 
	else if (pos >= size()) 
	{
		cout << "[Exceeds limit.]\n";
	} 
	else 
	{
		rep (i, pos - 1)
		{
			copy = copy->link;
		}
		Node<T>* temp = copy->link;
		int data = temp->data;
		copy->link = copy->link->link;
		free(temp);
		
		cout << "\n[SUCCESS: Deleting " << data << " at " << pos << ".]\n";
		numNode--;
	}
}

template <class T>
void Queue_Linked<T>::listNode() 
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
		copy = copy->link;
	}
	cout << "------------------------------\n";
}

template <class T>
void Queue_Linked<T>::findNode(T val) 
{
	Node<T> *copy = front;
	int pos = 0;
	bool notFound = true;

	cout << "\n[NOTE] Position starts at ZERO.\n";
	while (copy) 
	{
		if (copy->data == val) 
		{
			cout << "|Found at position: " << pos << "|\n";	
			notFound = false;
		}
		pos++;
		copy = copy->link;
	}
	
	if(notFound)
	{
		cout << "[Not Found!]\n";
	}
}

template <class T>
bool Queue_Linked<T>::isEmpty() 
{
	if (front != NULL) 
		return false;
	return true;
}

template <class T>
int Queue_Linked<T>::size()
{
	return numNode + 1;
}

template <class T>
void Queue_Linked<T>::deleteAll()
{
	Node<T>* copy = front;
	while (copy)
	{
		front = copy->link;
		free(copy);
		copy = front;
	}
	numNode = -1;
}

template <class T>
T Queue_Linked<T>::wBack() {
	return rear->data;
}

template <class T>
T Queue_Linked<T>::wFront() {
	return front->data;
}