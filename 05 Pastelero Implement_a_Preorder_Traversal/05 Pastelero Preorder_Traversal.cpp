#include "05 Pastelero User_friendly.h"
#include "05 Pastelero Preorder_Traversal.h"

void eraseVert();

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
				gotoxy(81, 4);
				std::cout << "[Enter the Value]";
				val = input();
				if(first.grow(val)) {
					gotoxy(46, 7);
					std::cout << "[Success at inserting " << val << "]";
				} else {
					gotoxy(46, 7);
					std::cout << "[Unsuccessful]";
				}
				break; 
			case 1:
				gotoxy(1, 1);
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				first.print(6);
				val = input();
				if (first.ungrow(val)) {
					gotoxy(46, 27);
					std::cout << "[Succes at deleting " << val << "]";
					gotoxy(64, 4);
					std::cout << "[ NEW  TREE ]";
					first.print(1);
				} else {
					gotoxy(46, 7);
					std::cout << "[Unsecessful]";
				}
				eraseVert();
				break;
			case 2:
				gotoxy(76, 4);	
				std::cout << "[Enter the Value to Find]";
				val = input();
				gotoxy(45, 8);
				if (!first.find(val, 1)) {
					gotoxy(46, 7);
					std::cout << "[NOT FOUND]";
				}
				break;
			case 3:
				choice = menu(2);
				color(15);
				switch (choice)
				{
					case 0: 
						gotoxy(85, 4);
						std::cout << "[ 2D  PRINT ]";
						gotoxy(46, 7);
						first.print(1);
						break;
					case 1:
						gotoxy(59, 4);	
						std::cout << "[PRE-ORDER TRAVERSAL]";
						gotoxy(46, 7);
						first.print(2);
						break;
					case 2:
						gotoxy(60, 4);	
						std::cout << "[IN-ORDER TRAVERSAL]";
						gotoxy(46, 7);
						first.print(3);
						break;
					case 3:
						gotoxy(59, 4);	
						std::cout << "[POST-ORDER TRAVERSAL]";
						gotoxy(46, 7);
						first.print(4);
						break;
					case 4:
						gotoxy(58, 4);	
						std::cout << "[BREATH FIRST TRAVERSAL]";
						gotoxy(46, 7);
						first.print(5);
						break;
					case 5:
						gotoxy(85, 4);
						std::cout << "[ 2D  PRINT ]";
						gotoxy(1, 1);
						std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
						first.print(6);
						break;
				}
				break;
			case 4:
				
				choice = menu(3);

				switch(choice) 
				{
					case 0:
						if (first.isEmpty()) {
							gotoxy(46, 7);
							std::cout << "[Empty]";
						} else {
							gotoxy(46, 7);
							std::cout << "[Not Empty]";
						}
						break;
					case 1:
						gotoxy(46, 7);
						std::cout << "[DATA QUANTITY: " << first.numData() << "]";
						break;
					case 2:
						if (!first.isEmpty()) {
								gotoxy(46, 7);
								std::cout << "[HEIGHT: " << first.depthCheck() << "]";
						} else {
								gotoxy(46, 7);
								std::cout << "[EMPTY]";
						}
						break;
					case 3:
						gotoxy(46, 7);
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
		gotoxy(12, 20);
		std::cout << "[DATA QUANTITY: " << first.numData() << "]";
		gotoxy(46, 15);
		first.print(1);
		gotoxy(1, 1);
		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		first.print(6);
		pause();
	}

}



void eraseVert() {
	gotoxy(1, 39);
	std::cout << "\xB2                                  ";
	gotoxy(1, 38);
	std::cout << "\xB2                                  ";
	gotoxy(1, 37);
	std::cout << "\xB2                                   ";
	gotoxy(1, 36);
	std::cout << "\xB2                                   ";
	gotoxy(1, 35);
	std::cout << "\xB2                                   ";
	gotoxy(1, 34);
	std::cout << "\xB2                                   ";
	gotoxy(1, 33);
	std::cout << "\xB2                                   ";
	gotoxy(1, 32);
	std::cout << "\xB2                                   ";
	gotoxy(1, 33);
	std::cout << "\xB2                                   ";
	gotoxy(1, 31);
	std::cout << "\xB2                                   ";
	gotoxy(1, 30);
	std::cout << "\xB2                                   ";
	gotoxy(1, 29);
	std::cout << "\xB2                                   ";
	gotoxy(1, 28);
	std::cout << "\xB2                                   ";
	gotoxy(1, 27);
	std::cout << "\xB2                                   ";
	gotoxy(1, 26);
	std::cout << "\xB2                                   ";
	gotoxy(1, 25);
	std::cout << "\xB2                                   ";
	gotoxy(1, 24);
	std::cout << "\xB2                                   ";
}