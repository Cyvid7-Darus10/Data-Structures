#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <windows.h>
#include <conio.h>


//Functions used for Design
void gotoxy(int,int);
void color(int);  
void pause();
int input();
void welcome();
int menu(int);
void box();


COORD coord = {0, 0};
void gotoxy (int x, int y) {
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clear_screen()
{
	#ifdef _WIN32
		std::system("cls");
	#else
		// Assume POSIX
		std::system ("clear");
	#endif
}

void welcome()
{
	color(15);
	gotoxy(42,1);
	std::cout << "WELCOME TO BINARY SEARCH TREE";

	gotoxy(10,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

	for (int i = 3; i <=23; i++) {
		gotoxy(10,i);
		printf("\xB2");
	}
	for (int i = 3; i <=23; i++) {
		gotoxy(105,i);
		printf("\xB2");
	}

	
	gotoxy(46,5);
	color(2);
	std::cout <<  "Binary Search Tree:" ;
		
	gotoxy(13,7);
	color(15);
	printf("\xB2 The smallest element will always be the one found by following the subtrees to the left");
	gotoxy(13,8);
	printf("  until you reach a leaf.");
	gotoxy(13,9);
	printf("\xB2 Similarly, the largest is found by traveling to the right until a leaf is reached.");

	gotoxy(43,11);
	color(3);
	std::cout <<  "Functions In this Program:" ;
		
	gotoxy(13,13);
	color(15);
	printf("\xB2 Insertion \t\t\t \xB2 Deletion \t\t\t \xB2 Find a Node");
	gotoxy(13,15);
	printf("\xB2 Show List \t\t\t \xB2 More Functions");
	gotoxy(13,16);
	printf("%c%cList Tree Graphically \t\t %c%cCheck if Empty",200,205,200,205);
	gotoxy(13,17);
	printf("%c%cPrint Nodes in Pre-order \t %c%cCheck the number of Datas",200,205,200,205);
	gotoxy(13,18);
	printf("%c%cPrint Nodes in In-order \t \t %c%cCheck the Height of Tree",200,205,200,205);
	gotoxy(13,19);
	printf("%c%cPrints Node in Post-order \t %c%cCheck what Type of Tree",200,205,200,205);
	gotoxy(13,20);
	printf("%c%cBreath First Traversal \t \t ",200,205);

	color(11);
	gotoxy(43,25);
	printf("\xB2\xB2PRESS ENETER TO CONINUE\xB2\xB2");

	color(15);	
	gotoxy(10,23);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");


	char key;
	while (true) {
		key = _getch();
		if (key == '\r') {
			break;
		}
	}
}

void pause()
{
	gotoxy(15,25);
	color(11);
	printf("\xB2\xB2PRESS ENETER TO CONINUE\xB2\xB2");

	char key;
	while (true) {
		key = _getch();
		if (key == '\r') {
			break;
		}
	}
}



//This function is used for input validation
int input()
{
	std::string num;
	bool isCorrect = true, isBig = false, wrongInput = false;
	int intNum;

	do {
		//WARNINGS
		if(wrongInput) {
			gotoxy(55, 7);		
			std::cout << "[WRONG INPUT]";
		}
		if(isBig) {
			gotoxy(55, 7);		
			std::cout << "[INPUT IS TOO BIG]";
		}
		//reinitializing the values
		isCorrect = true;
		isBig = false;
		wrongInput = false;

		gotoxy(70,5);
		std::cout <<"                                    "; //clears inputs
		gotoxy(55,5);
		std::cout <<"Enter only integer inputs:";
		
		num.clear();
		getline(std::cin, num); //used getline for checking spaces
		
		//clears warnings
		gotoxy(55, 7);		
		std::cout << "                              ";

		if (num.length() <= 11) {
			//iterates throughout the std::string and check wether everything is a number
			int size = num.length();
			for (int i = 0; i < size; i++) {
				if (i == 0 && num[i] == '-') {
					continue;
				}
				if (!isdigit(num[i])) {
					isCorrect = false;
					wrongInput = true;
					break;
				}
			}

			if (wrongInput) {
				continue;
			}
			
			//to avoid overflow, input is converted into long and
			//check wether it exceeds the int variable limit.
			try {
				intNum = stol(num);
			} catch (std::exception& e) {
				isBig = true;
				isCorrect = false;
				continue;
			}

			if (intNum < -2147483648 || intNum > 2147483647) {
				isBig = true;
				isCorrect = false;
				continue;	
			}
		} else {
			isBig = true;
			isCorrect = false;
			continue;	
		}

	} while (!isCorrect);

	return stoi(num);
}

int menu(int type) 
{
	std::string Menu1[6] = {"Insertion", "Deletion", "Find a Node", 
							"Show List", "More Functions", "Exit" };

	std::string Menu2[5] = {"List Tree Graphically", "Print Nodes in Preorder", 
							"Print Nodes in In-Order", "Print Nodes in Post-Order", "Breath First Traversal"};

	std::string Menu3[4] = {"Check if Empty", "Check the Number of Datas", 
					"Check the Height of Tree", "Check What Type of Tree"};

	std::string types[3] = {"MAIN MENU", "SUB MENU" };
	std::string *menuType;

	int arrS, typeI;
	switch (type) {
		case 1:
			menuType = Menu1;
			typeI = 0;
			arrS = 6;
			break;
		case 2:
			menuType = Menu2;
			typeI = 1;
			arrS = 5;
			break;
		case 3:
			menuType = Menu3;
			typeI = 1;
			arrS = 4;
			break;
	}

	int pointer = 0, val;
	bool stop = false;
	char key;

	while (!stop) {
		system("cls");
		gotoxy(0,0);	
		color(7);

		box();
		gotoxy(28,3);
		std::cout << types[typeI];


		for (int i = 0; i < arrS; ++i) {
			if (i == pointer) {
				gotoxy(13,5 + i*2);
				color(11);
				printf("\xDB\xDB\xDB\xDB\xB2 %d.", i + 1);
				std::cout << menuType[i];
			}
			else {
				gotoxy(13,5 + i*2);
				color(15);
				printf("\xDB\xDB\xDB\xDB\xB2 %d.", i + 1);
				std::cout << menuType[i];
			}
		}

	
		while (true) {
			key = _getch();
			if (key == 72) {
				pointer -= 1;
				if (pointer == -1) {
					pointer = arrS - 1;
				}
				break;
			} else if (key == 80) {
				pointer += 1;
				if (pointer == arrS)
				{
					pointer = 0;
				}
				break;
			} else if (key == '\r') {
				stop = true;
				break;
			}
		}
	}
	color(15);
	return pointer;
}

void box() 
{
	gotoxy(10,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2                \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

	gotoxy(13,3);
	for (int i = 3; i <=20; i++) {
		gotoxy(10,i);
		printf("\xB2");
	}
	for (int i = 3; i <=30; i++) {
		gotoxy(52,i);
		printf("\xB2");
	}

	gotoxy(35,1);
	std::cout << "BINARY SEARCH TREE | Pastelero | CMSC-123";
	gotoxy(10,20);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");


	gotoxy(52,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 DISPLAY \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(52,6);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(52,30);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	for (int i = 3; i <=30; i++) {
		gotoxy(106,i);
		printf("\xB2");
	}

}
