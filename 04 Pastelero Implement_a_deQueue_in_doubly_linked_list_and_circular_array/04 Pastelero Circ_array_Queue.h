#include <iostream>

using namespace std;

#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))

//Last update: OCT 3, 2020, 5:33PM
/*
					'Circular Array for Queue'
Name: Cyrus David G. Pastelero
Subject: CMSC 123 - Data Structures

Code Description:
Queue is a linear data structure which unlike the stack is open at both ends.
It follows the FIF(First In First Out) principle, which means that the
element that is inserted first is removed first.
*/

//The structure
template <class T>
class Queue_Circ 
{
	public:
		int front, rear;
		T* arr;
		int size;

		Queue_Circ<T>(int s) { size = s;
							   arr = new T[size];
							   rear = 0;
							   front = -1; };

		//functions
		void enQueue(T); //O(1)
		void deQueue(); //O(1)
		void find(T);

		//extra functions
		void list(); //O(n)
		bool isEmpty(); //O(1)
		int aSize();	//O(1)
		T wFront(); //O(1) what value is at front
		T wBack(); //O(1) what value is at back
		void circPrint(int);
		void loopPrint(int, int, int*);
};

template <class T>
void Queue_Circ<T>::enQueue(T val)
{
	if ((front == 0 && rear == size) || 
	 (rear == front && front != 0))
	{
		cout << "[Already Full]\n";
	}
	else
	{
		if (front == -1)
		{
			front = rear = 0;
			arr[rear] = val;
			++rear;
		}
		else if (rear >= size) 
		{
			rear = 0;
			arr[rear] = val;
			++rear;
		}
		else
		{
			arr[rear] = val;
			++rear;
		}
	}
}

template <class T>
void Queue_Circ<T>::deQueue()
{
	if (isEmpty())
	{
		cout << "[Already Empty]\n";
	}
	else
	{
		T data = arr[front];
		if (front == size - 1 && rear < front)
		{
			front = 0;
		}
		else
		{
			++front;
			if (front == rear)
			{
				front = -1;
				rear = 0;
			}
		}		
		cout << "[SUCCESS: Dequeueing " << data << ".]\n";
	}
}

template <class T>
void Queue_Circ<T>::list()
{
	int pos = 0;
	if (isEmpty())
	{
		cout << "[Empty]\n";
		return;
	}

	cout << "Queue:\n";
	cout << "Position\tValue\n";
	if (rear <= front)
	{
		loopPrint(front, size, &pos);
		loopPrint(0, rear, &pos);
	}
	else
	{
		loopPrint(front, rear, &pos);
	}
	cout << "------------------------------\n";
}

template <class T>
bool Queue_Circ<T>::isEmpty()
{
	if (front == -1)
	{
		return true;
	}
	return false;
}

template <class T>
void Queue_Circ<T>::find(T val)
{
	int position = 0;
	bool notFound = true;

	cout << "[NOTE] Position starts at Zero.\n";
	if (rear <= front)
	{		
		reu(i, front, size)
		{
			if (arr[i] == val)
			{
				notFound = false;
				cout << "|Found at position: " << position << "|\n";
			}
			position++;
		}
		rep(i, rear)
		{
			if (arr[i] == val)
			{
				notFound = false;
				cout << "|Found at position: " << position << "|\n";
			}
			position++;
		}
	}
	else
	{
		reu (i, front, rear)
		{
			if (arr[i] == val)
			{
				notFound = false;
				cout << "|Found at position: " << position << "|\n";
			}
			position++;
		}
	}

	if (notFound)
	{	
		cout << "[Not Found]\n";
	}
}

template <class T>
int Queue_Circ<T>::aSize(){
	int s;
	if (front == -1)
	{
		s = 0;
	}
	else if (front < rear)
	{
		s = rear - front;
	}
	else
	{
		s = size - front + rear; 
	}
	return s;
}

template <class T>
T Queue_Circ<T>::wFront()
{
	return arr[front];
}

template <class T>
T Queue_Circ<T>::wBack()
{
	return arr[rear - 1];
}

template<class T>
void Queue_Circ<T>::circPrint(int start)
{
	if (isEmpty())
	{
		cout << "Cannot Print Circularly: EMPTY\n";
		return;	
	} 
	else if (start >= aSize() || start < 0)
	{
		cout << "[Out of Reach Position]\n";
		return;
	}
	else if (start == 0)
	{
		list();
		return;
	}

	start += front;
	if (start >= size)
	{
		start -= size;
	}

	int pos = 0;
	cout << "Queue:\n";
	cout << "Position\tValue\n";
	if (rear <= front)
	{
		if (start > front)
		{
			loopPrint(start, size, &pos);
			loopPrint(0, rear, &pos);
			loopPrint(front, start, &pos);
		}
		else
		{
			loopPrint(start, rear, &pos);
			loopPrint(front, size, &pos);
			loopPrint(0, start, &pos);
		}
	}
	else
	{
		loopPrint(start, rear, &pos);
		loopPrint(front, start, &pos);
	}
	cout << "------------------------------\n";
}

template <class T>
void Queue_Circ<T>::loopPrint(int str, int end, int *pos)
{	
	reu(i,str,end)
	{
		cout << "------------------------------\n"
			<< "    " << *pos << "     |      " << arr[i] << endl;
		*pos += 1;
	}
}