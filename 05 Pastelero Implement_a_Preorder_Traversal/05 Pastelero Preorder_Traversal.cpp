#include "05 Pastelero User_friendly.h"
#include "05 Pastelero Preorder_Traversal.h"

int main() 
{
	int val, choice;
	bool stop = false;
	BST first;
	
	clear_screen();
	welcome();

	//Exits when choosing 6th option.
	while(!stop) {
		choice = menu(1);
		switch(choice) {
			case 0:
				gotoxy(70, 4);	
				std::cout << "[Enter the Value]";
				val = input();
				if(first.grow(val)) {
					gotoxy(55, 7);
					std::cout << "[Success at inserting " << val << "]";
				} else {
					gotoxy(55, 7);
					std::cout << "[Unsuccessful]";
				}
				break; 
			case 1:
				val = input();
				if (first.ungrow(val)) {
					gotoxy(55, 27);
					std::cout << "[Succes at deleting " << val << "]";
					gotoxy(73, 4);
					std::cout << "[ NEW  TREE ]";
					first.print(1);
				} else {
					gotoxy(55, 7);
					std::cout << "[Unsecessful]";
				}
				break;
			case 2:
				gotoxy(70, 4);	
				std::cout << "[Enter the Value to Find]";
				val = input();
				gotoxy(54, 8);
				if (!first.find(val, 1)) {
					gotoxy(55, 7);
					std::cout << "[NOT FOUND]";
				}
				break;
			case 3:
				choice = menu(2);
				color(15);
				switch (choice)
				{
					case 0: 
						gotoxy(73, 4);
						std::cout << "[ 2D  PRINT ]";
						gotoxy(55, 7);
						first.print(1);
						break;
					case 1:
						gotoxy(68, 4);	
						std::cout << "[PRE-ORDER TRAVERSAL]";
						gotoxy(55, 7);
						first.print(2);
						break;
					case 2:
						gotoxy(69, 4);	
						std::cout << "[IN-ORDER TRAVERSAL]";
						gotoxy(55, 7);
						first.print(3);
						break;
					case 3:
						gotoxy(68, 4);	
						std::cout << "[POST-ORDER TRAVERSAL]";
						gotoxy(55, 7);
						first.print(4);
						break;
					case 4:
						gotoxy(67, 4);	
						std::cout << "[BREATH FIRST TRAVERSAL]";
						gotoxy(55, 7);
						first.print(5);
						break;
				}
				break;
			case 4:
				
				choice = menu(3);

				switch(choice) 
				{
					case 0:
						if (first.isEmpty()) {
							gotoxy(55, 7);
							std::cout << "[Empty]";
						} else {
							gotoxy(55, 7);
							std::cout << "[Not Empty]";
						}
						break;
					case 1:
						gotoxy(55, 7);
						std::cout << "[DATA QUANTITY: " << first.numData() << "]";
						break;
					case 2:
						if (!first.isEmpty()) {
								gotoxy(55, 7);
								std::cout << "[HEIGHT: " << first.depthCheck() << "]";
						} else {
								gotoxy(55, 7);
								std::cout << "[EMPTY]";
						}
						break;
					case 3:
						gotoxy(55, 7);
						first.checkType();
				}
				break;
			case 5:
				stop = true;
				break;
			default:
				std::cout << "[CHOICES: 0 - 4 only | ENTER: 5 to Exit]";
				break;
		}
		pause();
	}

}
