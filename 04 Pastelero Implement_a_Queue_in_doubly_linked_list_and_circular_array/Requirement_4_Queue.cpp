#include "doubly_linked_list_Queue.h"
#include "circ_array_Queue.h"
#include "user_friendly.h"

//driver code for stack implementation using linked list
//Data type used is integer but it can be by changing the datatype at declaring Queues
int main() 
{
	int val;
	int choice;
	Doubly_Stack<int> first;

	mMenu:
		clear_screen();
		cout << endl
		<< "==============MAIN MENU==============\n"
		<< "1 > Queue Using Doubly Linked-List\n"
		<< "2 > Queue Using Circular Array\n"
		<< "3 > Exit\n"
		<< "=====================================\n";
		choice = input();

	//Size Checker for Circular Array
	//To avoid overflow	
	val = 0;
	if (choice == 2)
	{
		val = arrSizeChecker();
	}

	//If circ array is not chosen, its size will be ZERO.
	Queue_Circ<int> second(val);

	switch(choice)
	{
		case 1:
			//Exits when choosing 6th option.
			while(1) 
			{
				pause();
				clear_screen();
				menu(1);
				choice = input();

				switch(choice) {
					case 1:
						clear_screen();
						cout << "=====[Enter the Value]=====\n";
						val = input();
						first.enQueue(val); //Since Queue is a first in first out method
						break;
					case 2:
						clear_screen();
						first.deQueue();
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
						cout << endl
						<< "--------------Sub-Choices-------------\n"
						<< "1 > List Queue starting from front\n"
						<< "2 > List Queue starting from back\n"
						<< "--------------------------------------\n";
						choice = input();

						switch (choice)
						{
							case  1: 
								first.listNode();
								break;
							case  2: 
								first.listNodeBack();
								break;
						}
					
						break;
					case 5:
						clear_screen();
						cout << endl
						<< "--------------Sub-Choices-------------\n"
						<< "1 > Check if Empty.\n"
						<< "2 > Check the size of Queue.\n"
						<< "3 > Value at Rear.\n"
						<< "4 > Value at Front.\n"
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
								cout << "\n[Queue Size: " << first.size() << "]\n";
								break;
							case 3:
								if (!first.isEmpty())
										cout << "[Last Value: " << first.wBack() << "]\n";
									else
										cout << "[EMPTY]\n";
								break;
							case 4:
								if (!first.isEmpty())
										cout << "[First Value: " << first.wFront() << "]\n";
									else
										cout << "[EMPTY]\n";
								break;
						}
						break;
					case 6:
						//to free all memory used for linked-list
						first.deleteAll();
						goto mMenu;
					default:
						cout << "\n[CHOICES: 1 - 5 only | ENTER: 6 to Exit]\n";
						break;
				}
			}
			break;

			case 2:
				
				//Exits when choosing 6th option.
				while(1) {
					pause();
					clear_screen();
					menu(0);
					choice = input();

					switch(choice) {
						case 1:
							clear_screen();
							cout << "=====[Enter the Value]=====\n";
							val = input();
							second.enQueue(val); //Since queue is a first in first out method
							break;
						case 2:
							clear_screen();
							second.deQueue();
							cout << "NEW STACK:\n";
							second.list();
							break;
						case 3:
							clear_screen();
							cout << "==[Enter the Value to Find]==\n";
							val = input();
							second.find(val);
							break;
						case 4:
							clear_screen();
							second.list();
							break;
						case 5:
							clear_screen();
							cout << endl
							<< "--------------Sub-Choices-------------\n"
							<< "1 > Check if Empty.\n"
							<< "2 > Check the size of Queue.\n"
							<< "3 > Value at Rear.\n"
							<< "4 > Value at Front.\n"
							<< "5 > Circular Printing.\n"
							<< "--------------------------------------\n";
							choice = input();

							switch(choice) 
							{
								case 1:
									if (second.isEmpty())
									{
										cout << "[Empty]\n";
									}
									else
									{
										cout << "[Not Empty]\n";
									}
									break;
								case 2:
									cout << "[Queue Size: " << second.aSize() << "]\n";
									break;
								case 3:
									if (!second.isEmpty())
										cout << "[Last Value: " << second.wBack() << "]\n";
									else
										cout << "[EMPTY]\n";
									break;
								case 4:
									if (!second.isEmpty())
										cout << "[First Value: " << second.wFront() << "]\n";
									else
										cout << "[EMPTY]\n";
									break;
								case 5:
									cout << "[Enter the Position to start Printing]\n";
									val = input();
									second.circPrint(val);
									break;
							}
							break;
						case 6:	
							goto mMenu;
						default:
							cout << "\n[CHOICES: 1 - 5 only | ENTER: 6 to Exit]\n";
							break;
					}
				}
				break;
			case 3:
				return 0;	
			default:
				cout << "\n[Choices are only 1 and 2, Enter 3 to Exit.]\n";
				pause();
				goto mMenu;
	}	
}