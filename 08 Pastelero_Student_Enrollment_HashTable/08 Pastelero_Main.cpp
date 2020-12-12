#include "08 Pastelero_HashTable.h" //Helper.h is already included in HashTable.h

int main()  {
    Student stud;
    Helper helper;
    int choice, val;

    do { 
        gotoxy(11, 8);
        std::cout << "                                                      ";
        gotoxy(9, 8);
        std::cout << "Input the Hash Table's Size: ";
        val = helper.returnIntNumInput();
    } while (val < 1);
    
    gotoxy(9, 8);
    std::cout << "                                               "; //clears hash size prompt
    
    HashTable hTable(val);

    helper.welcome();

	//Exits when choosing 6th option.
	while(1) {
        choice = helper.menu(1);
        switch (choice)
        {
            case 0:
                val = helper.studentID();
                if (hTable.searchStud(val, false)) {\
                    gotoxy(48, 8);
                    std::cout << "[STUDENT ID ALREADY TAKEN]\n";
                    helper.pause();
                    choice = helper.menu(5); 
                    if (!choice){
                        break;
                    }
                }

                stud.inputInfos(val, 8); //inserting the student's information hTable.
                hTable.enrollStud(val, stud); //inserting it to the hashtable with its ID as the hash key
                hTable.fileWrite(stud); //writing it to the file name StudentsNewList.txt
                break;
            case 1:
                val = helper.studentID();
                choice = helper.menu(5); 
                if (!choice){
                    break;
                }
                helper.infoHeader();
                hTable.unenrollStud(val);
                break;
            case 2:
                val = helper.studentID();
                helper.infoHeader();
                if(!hTable.searchStud(val, true)) {
                    gotoxy(48, 8);
                    std::cout << "[STUDENT DOES NOT EXIST]\n";
                }
                break;
            case 3:
                choice = helper.menu(2);
                switch (choice)
                {
                    case 0:
                        choice = helper.menu(6);
                        helper.infoHeader();
                        if (choice == 0)
                            hTable.printType(1);
                        else if (choice == 1)
                            hTable.printType(2);
                        break;
                    case 1:
                        helper.infoHeader();
                        hTable.printType(3);
                        break;
                    case 2:
                        helper.infoHeader();
                        hTable.printType(4);
                        break;
                    case 3:
                        break;
                }
                break;
            case 4:
                choice = helper.menu(3);
                switch (choice)
                {
                    case 0:
                        if (hTable.isEmpty()) {
                            gotoxy(48, 7);
                            std::cout << "[EMPTY]\n"; 
                        } else {
                            gotoxy(48, 7);
                            std::cout << "[NOT EMPTY]\n";
                        }
                        break;
                    case 1:
                        choice = helper.menu(4);
                        if (choice == 8) {
                            break;
                        }
                        val = helper.studentID();
                        hTable.editInfos(val, choice + 1); //plus 1 because it is in helper zero index base
                        break;
                    case 2:
                        gotoxy(48, 7);
                        std::cout << "Number of Students: " << hTable.numStudents() << std::endl;
                        break;
                    case 3:
                        gotoxy(48, 7);
                        std::cout << "Enter File Name: ";
                        hTable.fileRead(helper.returnStringWordInput());
                        break;
                    case 4:
                        break;
                }
                break;
            case 5:
                return 0;
            default:
                break;
        }
        helper.pause();
    }
}
