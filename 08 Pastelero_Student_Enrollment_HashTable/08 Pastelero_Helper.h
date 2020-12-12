#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <conio.h>

void gotoxy(int,int);
void color(int);  
COORD coord = {0, 0};

class Helper {
    public:
        void clear_screen();
        void pause();
        void box();
        int menu(int); 
        void welcome();
        bool inputCheck(int, std::string);
        void reformatInfo(std::string&);
        int returnIntNumInput();
        int studentID();
        void infoHeader();
        std::string returnStringNumInput();
        std::string returnStringWordInput();
};

//------------------------HELPER FUNCTIONS--------------------------

void Helper::clear_screen()
{
	#ifdef _WIN32
		std::system("cls");
	#else
		// Assume POSIX
		std::system ("clear");
	#endif
}

int Helper::returnIntNumInput() {
    std::string num;
	int intNum;
	
    num.clear(); 
    getline(std::cin, num); //used getline for checking spaces

	gotoxy(3,27);
    std::cout << "                                       "; //clear old warnings

    if (num.length() <= 5) {
        //iterates throughout the std::string and check wether everything is a number
        int size = num.length();
        for (int i = 0; i < size; i++) {
            if (!isdigit(num[i])) {
                gotoxy(3,27);
                std::cout << "[Integer Input Only]";
                return -1;
            }
        }
        //to avoid overflow, input is converted into long and
        //check wether it exceeds the int variable limit.
        try {
            intNum = stoi(num);
        } catch (std::exception& e) {
            gotoxy(3,27);
            std::cout << "[Invalid Input]";
            return -1;
        }

    } else {
        gotoxy(3,27);
        std::cout << "[Too Big]";
        return -1;
    }

    gotoxy(3,27);
    std::cout << "                                "; //clear old warnings
	return stoi(num);
}

//Checks double spacing and other characters other than letters
std::string Helper::returnStringWordInput() {
    std::string input;
    int  inputSize;

    input.clear();
    getline(std::cin, input);
	
	gotoxy(3,27);
    std::cout << "                                       "; //clear old warnings

    inputSize  = input.length();

	gotoxy(3,27);
    std::cout << "                                       "; //clear old warnings

    if (inputSize > 25 || inputSize == 0)
    {
        gotoxy(3,27);
        std::cout << "[INVALID INPUT SIZE]";
        return "";
    }

    for (int i = 0; i < inputSize; i++) {
        if (input[i] == ' ') {
            if (i == inputSize - 1 || input[i + 1] == ' ')
            {
                gotoxy(3,27);
                std::cout << "[Must Have No Double Spacing]\n";
                return "";
            } else if (i == 0) {
                gotoxy(3,27);
                std::cout << "[Word Must Not Start with Space]\n";
                return "";
            }
            continue;
        } else if (input[i] == '.') {
			if (i == inputSize - 1 || input[i + 1] == '.')
            {
                gotoxy(3,27);
                std::cout << "[Must Have No Double Dots]\n";
                return "";
            } else if (i == 0) {
                gotoxy(3,27);
                std::cout << "[Word Must Not Start with Dots]\n";
                return "";
            }
            continue;
		}

        if (!isalpha(input[i])) {
            gotoxy(3,27);
            std::cout << "[Wrong Input, Letter Only]\n";
            return "";
        }
    }
    gotoxy(3,27);
    std::cout << "                                       "; //clear old warnings
    return input;
}

std::string Helper::returnStringNumInput() {
	std::string num;
    //reinitializing the values
    num.clear(); 
    getline(std::cin, num); //used getline for checking spaces

	gotoxy(3,27);
    std::cout << "                                       "; //clear old warnings

    if (num.length() <= 11 && num.length() > 0) {
        //iterates throughout the std::string and check wether everything is a number
        int size = num.length();
        for (int i = 0; i < size; i++) {
            if (!isdigit(num[i])) {
                gotoxy(3,27);
                std::cout << "[Wrong Input]";
                return "";
            }
        }
    } else {
        return "";
    }
    gotoxy(3,27);
    std::cout << "                                "; //clear old warnings
    return num;
}

int Helper::studentID() {
    int val;

    do {
        gotoxy(53, 7);
        std::cout << "                                                                    ";
        gotoxy(48, 7);
        std::cout << "Enter Student's ID Number: ";
        val = returnIntNumInput();
    } while (val == -1);
    
    return val;
}

bool Helper::inputCheck(int cType, std::string data) {
    bool isCorrect = false;
        //Naming Check
	if (cType == 1 || cType == 2 || cType == 3) {
			if (data.length() > 2 && data.length() < 17) {
				isCorrect = true;
			}
		//Address Check
	} else if (cType == 7) {
			if (data.length() > 2 && data.length() < 21) {
				isCorrect = true;
			}
		//Gender Check
	} else if (cType == 4) {
        transform(data.begin(), data.end(), data.begin(), ::tolower);
        if (data.compare("male") == 0) {
            isCorrect = true;
        }
        if (data.compare("female") == 0) {
            isCorrect = true;
        }
        //Age Check
    } else if (cType == 5) {
			try {
				if (stoi(data) >= 6 && stoi(data)<= 60) {
					isCorrect = true;
				}
			} catch (std::exception& e) {
				gotoxy(3,27);
				std::cout << "[Invalid Input]";
			}
        //Contact Number Checker
    } else if (cType == 6) {
            isCorrect = true;
            if (data.length() > 11 || data.length() < 9) {
                isCorrect = false;
            }
    }

    return isCorrect;
}

void Helper::reformatInfo(std::string &info) {
    if(!isdigit(info[0])) {
        transform(info.begin(), info.end(), info.begin(), ::tolower);
        info[0] = toupper(info[0]);
        for (int i = 0; info[i] != '\0'; i++) {
            if (info[i] == ' ') {
                info[i + 1] = toupper(info[i + 1]);
            }
        }
    } else {
        std::string copy = "";
        for (int i = 0; info[i] != '\0'; i++) {
            if (info[i] == '-') {
                return;
            }
            if (i == 3 || i == 7) {
                copy += '-';
            }
            copy += info[i];
        }
        info = copy;
    }
}

void Helper::infoHeader() {
    gotoxy(47,5);
    std::cout << " ID     Last Name\t First Name\t   Middle Name\t     Gender  Age  Contact #      Address";
}

void gotoxy (int x, int y) {
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void Helper::welcome() {
	color(15);
	gotoxy(38,1);
	std::cout << "WELCOME TO STUDENT ENROLLMENT SYSTEM";

	gotoxy(10,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

	for (int i = 3; i <=23; i++){
		gotoxy(10,i);
		printf("\xB2");
	}

	for (int i = 3; i <=23; i++) {
		gotoxy(105,i);
		printf("\xB2");
	}

	
	gotoxy(49,5);
	color(2);
	std::cout <<  "::HOW TO USE::" ;
		
	gotoxy(13,7);
	color(15);
	printf("\xB2 [NOTE] Use arrow keys to navigate the program.");
	gotoxy(13,8);
	printf("\xB2 [NOTE] Maximize the window to avoid glitches.");
	gotoxy(13,9);
	printf("\xB2 [NOTE] Student's Age must be 6 to 60 yrs old only.");
	gotoxy(13,10);
	printf("\xB2 [NOTE] Student's ID Number must have 5 length only.");
	gotoxy(13,11);
	printf("\xB2 [NOTE] Contact Number, 9-11 digit only.");
	

	gotoxy(43,13);
	color(3);
	std::cout <<  "::Functions In this Program::" ;
		
	gotoxy(13,15);
	color(15);
	printf("\xB2 Enroll a Student \t\t \xB2 Unenroll a Student \t\t \xB2 Search a Student");
	gotoxy(13,17);
	printf("\xB2 Show Who's Enrolled \t\t \xB2 More Functions");
	gotoxy(13,18);
	printf("%c%cAccording to Gender \t\t %c%cCheck if Empty",200,205,200,205);
	gotoxy(13,19);
	printf("%c%cAlphabetical Order \t\t %c%cEdit a Student Record",200,205,200,205);
	gotoxy(13,20);
	printf("%c%cAccording to ID Number \t \t %c%cCheck number of Student",200,205,200,205);
	gotoxy(13,21);
	printf("\t\t\t\t\t %c%cRead a Text File",200,205,200,205);


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

void Helper::pause() {
	gotoxy(10,25);
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


int Helper::menu(int type) {
	std::string Menu1[6] = {"Enroll a Student", "Unenroll a Student", "Search a Student", 
							"Show Who's Enrolled", "More Functions", "Exit" };

	std::string Menu2[4] = {"According to Gender", "Alphabetical Order", "According to ID Number", "Exit"};

	std::string Menu3[5] = {"Check if Empty", "Edit Student Information", "Check Number of Student Registered", "Read a Text File", "Exit"};

	std::string Menu4[9] = {"Last Name", "First Name", "Middle Name", "Gender", "Age", "Contact Number", "Address", "All", "Cancel"};

    std::string yesNo[2] = {"NO", "YES"};

    std::string gender[2] = {"MALE", "FEMALE"};

	std::string types[4] = {"MAIN MENU", "SUB MENU", "CONTINUE?", "GENDER"};

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
			arrS = 4;
			break;
		case 3:
			menuType = Menu3;
			typeI = 1;
			arrS = 5;
			break;
		case 4:
			menuType = Menu4;
			typeI = 1;
			arrS = 9;
			break;
        case 5:
            menuType = yesNo;
            typeI = 2;
            arrS = 2;
            break;
        case 6:
            menuType = gender;
            typeI = 3;
            arrS = 2;
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
		gotoxy(18,3);
		std::cout << types[typeI];


		for (int i = 0; i < arrS; ++i) {
			if (i == pointer) {
				gotoxy(3,5 + i*2);
				color(11);
				printf("\xDB\xDB\xDB\xDB\xB2 %d.", i + 1);
				std::cout << menuType[i];
			}
			else {
				gotoxy(3,5 + i*2);
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

void Helper::box() {
	gotoxy(1,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2           \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

	// gotoxy(13,3);
	for (int i = 3; i <=30; i++) {
		gotoxy(1,i);
		printf("\xB2");
	}
	for (int i = 3; i <=40; i++) {
		gotoxy(46,i);
		printf("\xB2");
	}

	gotoxy(50,1);
	std::cout << "STUDENT ENROLLMENT SYSTEM | By Pastelero | CMSC-123";
	gotoxy(1,30);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");


	gotoxy(47,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 DISPLAY 2 \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(47,6);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(47,40);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	for (int i = 3; i <=40; i++) {
		gotoxy(162,i);
		printf("\xB2");
	}

}

