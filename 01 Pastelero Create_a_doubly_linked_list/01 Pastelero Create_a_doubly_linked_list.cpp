#include "01 Pastelero Doubly_linked_list.h"

//driver code

int main() 
{
	//initializing the linked_list for integers
	//to use linked list for other data type, 
	//manually change the Doubly_linked_list class definition
	//remove input checker and change the variable val data type
	Doubly_linked_list<int> first;
	int val, pos;
	int choice;

	//Exits when choosing 6th option.
	while(1) 
	{
		pause();
		clear_screen();
		cout << endl
		<< "             Doubly-Linked List              \n"
		<< "=====================MENU====================\n"
		<< "1 > Insertion"
		<< "\t\t4 > Show List\n"
		<< "2 > Deletion"
		<< "\t\t5 > More Functions\n"
		<< "3 > Find a Node"
		<< "\t\t6 > Exit\n"
		<< "=============================================\n";
		choice = input();

		switch(choice) 
		{
			case 1:
				clear_screen();
				cout << endl
				<< "--------------Sub-Choices-------------\n"
				<< "1 > Insert at Beginning.\n"
				<< "2 > Insert at End.\n"
				<< "3 > Insert Value at any Position.\n"
				<< "--------------------------------------\n";
				choice = input();

				switch (choice) 
				{
					case 1:
						cout << "=====[Enter the Value]=====\n";
						val = input();
						first.insertBeginning(val);
						break;
					case 2:
						cout << "=====[Enter the Value]=====\n";
						val = input();
						first.insertEnd(val);
						break;
					case 3:
						cout << "=====[Enter the Value]=====\n";
						val = input();
						cout << "==[Position(Starts at 0)]==\n";
						pos = input();
						first.insertAtPos(val, pos);
						break;
				}
				break;
			case 2:
				clear_screen();
				cout << endl
				<< "--------------Sub-Choices-------------\n"
				<< "1 > Delete Beginning.\n"
				<< "2 > Delete End.\n"
				<< "3 > Delete at any Position.\n"
				<< "4 > Delete specific number:\n"
				<< "--------------------------------------\n";
				choice = input();

				switch (choice) 
				{
					case 1:
						first.deleteBeginning();
						break;
					case 2:
						first.deleteEnd();
						break;
					case 3:
						cout << "==[Position(Starts at 0)]==\n";
						pos = input();
						first.deleteAtPos(pos);
						break;
					case 4:
						cout << "=[Enter the value to Delete]=\n";
						val = input();
						first.deleteSpecific(val);
						break;
				}
				cout << "NEW LIST:\n";
				first.listNodeFront();
				break;
			case 3:
				clear_screen();
				cout << "==[Enter the Value to Find]==\n";
				val = input();
				first.findNode(val);
				break;
			case 4:
				clear_screen();
				cout << endl
				<< "--------------Sub-Choices-------------\n"
				<< "1 > List Node starting from head.\n"
				<< "2 > List Node starting from tail.\n"
				<< "--------------------------------------\n";
				choice = input();
				
				switch (choice)
				{
					case 1:
						first.listNodeFront();
						break;
					
					case 2:
						first.listNodeBack();
						break;
				}	
				break;
			case 5:
				clear_screen();
				cout << endl
				<< "--------------Sub-Choices-------------\n"
				<< "1 > Check if Empty.\n"
				<< "2 > Check the number of Nodes.\n"
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
