#include <iostream>
#include <cstdlib>

using namespace std;

//Last update: OCT 5, 2020, 10:30PM
/*
		    'Doubly Linked List'
Name: Cyrus David G. Pastelero
Subject: CMSC 123 - Data Structures

Code Description:
A doubly linked list is a more complex type of linked list,
which contains a pointer to the next as well as the previous 
Node in the sequence. This allows for reverse traversal anywhere in list.
*/

/*
	Functions below are used for:
	- Easy to read terminal
	- Although system calls are awful for portability
	- I used it for user friendliness sake and for design aspect, 
	- I used different ways for it to work in both linux and windows.
*/
void clear_screen()
{
	#ifdef WINDOWS
		std::system("cls");
	#else
		// Assume POSIX
		std::system ("clear");
	#endif
}

void pause(void)
{
	/*
	On Windows:
		pause > nul
	On linux:
		echo Press any key to continue ...; read x
	*/
    system("echo =[Press Enter to Continue]= && ( read x 2> nul; rm nul || pause > nul )");
    return;
}

//This function is used for input validation
int input()
{
	string num;
	bool isCorrect = true;

	do {
		if(!isCorrect) 
		{
			cout << "[WRONG INPUT]\n";
		}

		isCorrect = true;
		cout <<"Enter only integer inputs:";
		cin >> num;

		long int lNum;
		if (num.length() <= 11)
		{
			//iterates throughout the string and check wether everything is a number
			int size = num.length();
			for (int i = 0; i < size; i++)
			{
				if (i == 0 && num[i] == '-')
				{
					continue;
				}
				if(!isdigit(num[i]))
				{
					isCorrect = false;
					break;
				}
			}

			if(!isCorrect) 
			{
				continue;
			}
			
			//to avoid overflow, input is converted into long and
			//check wether it exceeds the in variable limit.
			lNum = stol(num);
			if (lNum < -2147483648 || lNum > 2147483647)
			{
				cout << "[Input is too Big]\n";
				isCorrect = false;
				continue;	
			}
		}
		else
		{
			cout << "[Input is too Big]\n";
			isCorrect = false;
			continue;	
		}

	} while (!isCorrect);

	return stoi(num);
}

//the structure of the doubly linked list
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
class Doubly_linked_list 
{
	private:
		Node<T> *head;
		Node<T> *tail;
		int numNode; //for counting the number of Nodes
	public:

		//initialization
		Doubly_linked_list() {	head = NULL;
					tail = NULL;
					numNode = -1; }; //-1 because index is starting at 0. 
							//Adding a Node will put it at 0 index.

		//insertion functions
		void insertBeginning(T); //O(1)
		void insertEnd(T); //O(1)
		void insertAtPos(T, int); //O(n)

		//deletions functions
		void deleteBeginning(); //O(1)
		void deleteEnd(); //O(1)
		void deleteAtPos(int); //O(n)
		void deleteSpecific(T); //O(n)

		//extra functions
		void listNodeFront(); //O(n)
		void listNodeBack(); //O(n)
		void findNode(T); //O(n)
		bool isEmpty(); //O(1)
		void size(); //O(1)

		//destructor
		~Doubly_linked_list(){};
};

template <class T>
void Doubly_linked_list<T>::insertBeginning(T val) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	newNode->prev = NULL;

	if (head == NULL) 
	{
		newNode->next = NULL;
		head = tail = newNode;
	} 
	else 
	{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	cout << "\n[SUCCESS: Inserting at Beginning]\n";
	numNode++;
}

template <class T>
void Doubly_linked_list<T>::insertEnd(T val) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	newNode->next = NULL;

	if (head == NULL) 
	{
		insertBeginning(val);
	} 
	else 
	{
		Node<T> *copy = tail;
		copy->next = newNode;
		newNode->prev = copy;
		tail = newNode;
		cout << "\n[SUCCESS: Inserting at End]\n";
		numNode++;
	}
}

template <class T>
void Doubly_linked_list<T>::insertAtPos(T val, int pos) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;	

	if (pos == 0) 
	{
		//since it is the first Node
		insertBeginning(val);
	} 
	else if (numNode + 1 == pos) 
	{
		insertEnd(val);
	}
	else if (numNode < pos) 
	{
		cout << "[Exceeds limit]\n";
		return;
	} 
	else 
	{
		Node<T> *copy = head;
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
void Doubly_linked_list<T>::deleteBeginning() 
{
	//If head is NULL = True else if NULL = False
	if (!head) 
	{
		cout << "[Already Empty]\n";
	} 
	else 
	{
		T data;
		Node<T> *copy = head;
		if (head == tail) //means it is the last Node
		{
			data = head->data;
			head = tail = NULL;
			free(copy);
		}
		else 
		{
			data = copy->data;
			head = copy->next;
			head->prev = NULL;
			free(copy);
		}	
		cout << "\n[SUCCESS: Deleting " << data << " at beginning.]\n";
		numNode--;
	}
}

template <class T>
void Doubly_linked_list<T>::deleteEnd() 
{
	if (head == NULL) 
	{
		cout << "[Already Empty.]\n";
	} 
	else 
	{
		T data;
		Node<T> *copy = tail;
		if (tail == head) //means it is the last Node
		{
			data = head->data;
			head = tail = NULL;
			free(copy);
		} 
		else 
		{
			data = copy->data;
			tail = copy->prev;
			tail->next = NULL;
			free(copy);
		}	
		cout << "\n[SUCCESS: Deleting " << data << " at end.]\n";
		numNode--;
	}
}

template <class T>
void Doubly_linked_list<T>::deleteAtPos(int pos) 
{
	if (pos < 0)
	{
		cout << "[Cannot access this position.]\n";
		return;
	}
	else if (head == NULL) 
	{
		cout << "[Already Empty.]\n";
	} 
	else if (pos == 0) 
	{
		deleteBeginning();
	} 
	else if (pos == numNode) 
	{
		deleteEnd();
	} 
	else if (numNode < pos) 
	{
		cout << "exceeds limit\n";
	}
	else 
	{
		Node<T> *copy = head;
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
void Doubly_linked_list<T>::deleteSpecific(T val) 
{
	if (head == NULL) 
	{
		cout << "[The List is Empty]\n";
	} 
	else 
	{
		cout << "\n[NOTE]First number that match is to be deleted.\n";
		int pos = 0;
		Node<T> *copy = head;
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

		if (copy == head) 
		{
			deleteBeginning();
		} 
		else if (!copy->next) 
		{
			deleteEnd();
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
void Doubly_linked_list<T>::listNodeFront() 
{
	if (head == NULL) 
	{
		cout << "[Empty List]\n";
	}
	else
	{
		cout << "List: ";
		cout << "HEAD -> ";
		Node<T> *copy = head;
		while (copy) 
		{
			cout << copy->data << " -> ";
			copy = copy->next;
		}
		cout << "TAIL\n";
		cout << endl;
	}
}

template <class T>
void Doubly_linked_list<T>::listNodeBack() 
{
	if (head == NULL) 
	{
		cout << "[Empty List]\n";
	}
	else
	{
		cout << "List: ";
		Node<T> *copy = tail;
		cout << "TAIL -> ";
		while (copy) 
		{
			cout << copy->data << " -> ";
			copy = copy->prev;
		}
		cout << "HEAD\n";
	}
}

template <class T>
void Doubly_linked_list<T>::findNode(T val) 
{
	Node<T> *copy = head;
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
bool Doubly_linked_list<T>::isEmpty()
{
	if (head != NULL)
	{ 
		return false;
	}
	return true;
}

template <class T>
void Doubly_linked_list<T>::size()
{
	cout << "\nThe Nodes Number is " << numNode + 1 << ".\n";
}
