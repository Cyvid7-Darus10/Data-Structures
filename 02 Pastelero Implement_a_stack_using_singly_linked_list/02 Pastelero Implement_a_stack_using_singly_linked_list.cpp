#include "02 Pastelero Stack_singly_linked_list.h"

//driver code for stack implementation using linked list
int main() 
{
	//initializing the linked_list for integers
	//to use linked list for other data type, 
	//manually change the Doubly_linked_list class definition
	//remove input checker and change the variable val data type
	Linked_list<int> first;
	int val;
	int choice;

	//Exits when choosing 6th option.
	while(1) {
		pause();
		clear_screen();
		cout << endl
		<< "            STACK Data Structure             \n"
		<< "=====================MENU====================\n"
		<< "1 > Insertion"
		<< "\t\t4 > Show List\n"
		<< "2 > Deletion"
		<< "\t\t5 > More Functions\n"
		<< "3 > Find a Node"
		<< "\t\t6 > Exit\n"
		<< "=============================================\n";
		choice = input();
		switch(choice) {
			case 1:
				clear_screen();
				cout << "=====[Enter the Value]=====\n";
				val = input();
				first.stackPush(val); //Since stack is a last in first out method
				break;
			case 2:
				clear_screen();
				first.stackPop();
				cout << "NEW STACK:\n";
				first.listNode();
				break;
			case 3:
				clear_screen();
				cout << "==[Enter the Value to Find]==\n";
				val = input();
				first.findNode(val);
				break;
			case 4:
				clear_screen();
				first.listNode();
				break;
			case 5:
				clear_screen();
				cout << endl
				<< "--------------Sub-Choices-------------\n"
				<< "1 > Check if Empty.\n"
				<< "2 > Check the size of Stack.\n"
				<< "--------------------------------------\n";
				choice = input();

				switch(choice) 
				{
					case 1:
						if (first.isEmpty())
						{
							cout << "[Empty]\n";
						}
						else
						{
							cout << "[Not Empty]\n";
						}
						break;
					case 2:
						first.size();
						break;
				}
				break;
			case 6:
				return 0;
			default:
				cout << "[CHOICES: 1 - 5 only | ENTER: 6 to Exit]\n";
				break;
		}
	}
}
