#include <iostream>
#include <cstdlib>
#include <ctype.h>

using namespace std;

/*
	Functions below are used for:
	- Easy to read terminal
	- Although system calls are awful for portability
	- I used it for user friendliness sake and for design aspect, 
	- I used different ways for it to work in both linux and windows.
*/
void clear_screen()
{
	#ifdef _WIN32
		std::system("cls");
	#else
		// Assume POSIX
		std::system ("clear");
	#endif
}

void pause()
{
    cout << "\nPress Enter to Continue...";
    cin.ignore();
    cin.get();
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

void menu(int type)
{
    string description;
    if (type == 1)
    {
        description = "Queue - Doubly Linked List";
    }
    else
    {
        description = "Queue - Circular Array";
    }
    
	cout << endl
    << "[ " << description << " ]\n"
    << "=====================MENU====================\n"
    << "1 > Insertion"
    << "\t\t4 > Show List\n"
    << "2 > Deletion"
    << "\t\t5 > More Functions\n"
    << "3 > Find a Node"
    << "\t\t6 > Exit\n"
    << "=============================================\n";
}

int arrSizeChecker() {
    bool rightSize = false;
    int size;
    while (!rightSize)
    {
        rightSize = true;
        cout << "[Give the Size for the Queue]\n";
        size = input();
        if (size > 10000 || size <= 0)
        {
            rightSize = false;
            cout << "[Change the Size of Queue to Avoid Error]\n";
        }
    }
    return size;
}
