#include <iostream>
#include <cstdlib>
#include <ctype.h>

using namespace std;

//Last update: OCT 5, 2020, 10:54AM
/*
					'Linked List'
Name: Cyrus David G. Pastelero
Subject: CMSC 123 - Data Structures

Code Description:
A linked list is a linear data structure where each element
is a separate object, known as a Node<T>. Each Node<T> contains 
some data and points to th link Node<T> in th structure,
forming a sequence.

The structuree alllows or efficient insertion or removal
of elements from any position as only link is needed to
be modified to point to some other element.

This is used for STACT Data structure, it follow, LIFO
Las In First Out

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

//The structure
template <class T>
class Node {
	public:
		T data;
		Node* link;
};

//Class definitions
template <class T>
class Linked_list {
	private:
		Node<T> *top;
		Node<T> *bottom;
		int numNode; //for counting the number of nodes
	public:

		//initialization
		Linked_list<T>() { top = NULL;
						bottom = NULL;
						numNode = -1; }; //starts at negative, for indexing purposes. 
								//Starts at ZERO when adding a Node<T>.

		//Stack functions:
		void stackPush(T); //O(1)
		void stackPop(); //O(1)
		
		//extra functions
		void listNode(); //O(n)
		void findNode(T); //O(n)
		bool isEmpty(); //O(1)
		void size();

		//unused function
		void insertBottom(T); //O(1) because back is used as pointer for the bottom
		void insertAtPos(T, int); //O(n)
		void deleteBottom(); //0(n) because we still need to iterate starting from top
		void deleteAtPos(int); //O(n)

		//destructor
		~Linked_list<T>(){};
};

template <class T>
void Linked_list<T>::stackPush(T val) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;

	//if the top pointer is empty, make newNode as top
	if (top == NULL) 
	{
		newNode->link = NULL;
		top = bottom = newNode;
	} 
	else 
	{
		newNode->link = top;
		top = newNode;
	}
	
	numNode++;
	cout << "\n[SUCCESS Inserting at Top]\n";
}

template <class T>
void Linked_list<T>::insertBottom(T val) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	newNode->link = NULL;
	
	//if the top pointer is empty, make newNode as top
	if (top == NULL) 
	{
		top = bottom = newNode;
	} 
	else 
	{
		Node<T> *copy = bottom;
		copy->link = newNode;
		bottom = newNode;
	}

	numNode++;
	cout << "\n[SUCCESS Inserting at Bottom]\n";
}

template <class T>
void Linked_list<T>::insertAtPos(T val, int pos) 
{
	Node<T> *newNode = new Node<T>;
	newNode->data = val;

	if (pos == 0) 
	{
		stackPush(val);
	} 
	else if (numNode + 1 == pos) 
	{
		insertBottom(val); 
	} 
	else if (numNode < pos) 
	{
		cout << "[Exceeds limit]\n";
	} 
	else 
	{
		Node<T> *copy = top;
		for (int i = 0; i < pos - 1; i++) 
		{
			copy = copy->link;
		}
		
		//inserting the Node<T>
		newNode->link = copy->link;
		copy->link = newNode;

		cout << "\n[SUCCESS Inserting " << val << " at position " << pos << ".]\n"; 
		numNode++;
	}
}

template <class T>
void Linked_list<T>::stackPop() 
{
	if (top == NULL) 
	{
		cout << "[Already empty.]\n";
	} 
	else 
	{
		T data;
		Node<T> *copy = top;
		data = top->data;
		if (copy->link == NULL) 
		{
			top = NULL;
			free(copy);
		} 
		else 
		{
			top = copy->link;
			free(copy);
		}	
		cout << "\n[SUCCESS Deleting " << data << " at Top.]\n";
		numNode--;
	}
}

template <class T>
void Linked_list<T>::deleteBottom() 
{
	if (top == NULL) 
	{
		cout << "[Already empty.]\n";
	} 
	else 
	{
		T data;
		Node<T> *copy = top;
		if (copy->link == NULL) 
		{
			data = top->data;
			top = NULL;
		} 
		else 
		{
			while (copy) 
			{
				if (copy->link->link == NULL) 
				{
					copy->link = NULL;
					bottom = copy;
				}
				data = copy->data;
				copy = copy->link;
			}
		}
		free(copy);	
		cout << "\n[SUCCESS Deleting " << data << " at Bottom.]\n";
		numNode--;
	}
}

template <class T>
void Linked_list<T>::deleteAtPos(int pos)
{
	Node<T> *copy = top;
	if (pos < 0)
	{
		cout << "[Cannot Access]\n";
	}
	else if (top == NULL) 
	{
		cout << "[Already empty.]\n";
	} 
	else if (pos == 0) 
	{
		stackPop();
	} 
	else if (pos == numNode) 
	{
		deleteBottom();
	} 
	else if (pos > numNode) 
	{
		cout << "Exceeds limit.\n";
	} 
	else 
	{
		for (int i = 0; i < pos - 1; i++) 
		{
		copy = copy->link;
		}
		Node<T>* temp = copy->link;
		T data = temp->data;
		copy->link = copy->link->link;
		free(temp);
		
		cout << "\n[SUCCESS Deleting " << data << " at position " << pos << ".]\n";
		numNode--;
	}
}

template <class T>
void Linked_list<T>::listNode() 
{
	if (top == NULL) 
	{
		cout << "[Empty List]\n";
		return;
	}
	cout << "Stack List:\n";

	int pos = 0;
	Node<T> *copy = top;
	cout << "[Position]      [Value]\n";
	while (copy) 
	{
		cout << "    "<<pos << "      ->   " << copy->data << endl;
		copy = copy->link;
		pos++;
	}
	cout << endl;
}

template <class T>
void Linked_list<T>::findNode(T val) 
{
	Node<T> *copy = top;
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
bool Linked_list<T>::isEmpty() 
{
	if (top != NULL) 
		return false;
	return true;
}

template <class T>
void Linked_list<T>::size()
{
	cout << "\nThe Stack Size is " << numNode + 1 << ".\n";
}
