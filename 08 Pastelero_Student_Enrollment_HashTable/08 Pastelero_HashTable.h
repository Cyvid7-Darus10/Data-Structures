#include "08 Pastelero_Helper.h" //iostream and string library is already included in Helper.h
#include "08 Pastelero_LinkedList.h" //Doubly LinkedList from requirement 1
#include <vector> //vector is used for sort printing

//for file reading and writing
#include <fstream>
#include <sstream>

/*
I am overloading the begin() and end() functions so that 
I can use range-based for loop on a dynamic array.
What I am doing here is wrapping the range in std::pair 
and overload the begin() and end(), with this way, I can use
for loop like this:
for (auto i : std::make_pair(array, array + size)) 
instead of:
for (auto i : aray)

I will use auto&& because it will bind to anything, it has the 
ability to modify and discard values of the sequence within the loop.
*/

namespace std {
    template <typename T> 
    T* begin(std::pair<T*, T*> const& p) { 
        return p.first; 
    }
    template <typename T> 
    T* end(std::pair<T*, T*> const& p) { 
        return p.second; 
    }
}

class Student
{
    friend class HashTable; //made Hashtable as class's friend in order to access private attributes
                            //Needed for reading and writing text files
    public:
        Student() {};
        void inputInfos(int, int); //used for data input and data editing
        void printInfos();
        std::string wMyFamName(); //what's my Family Name, used for sorting
        std::string wMyGender(); //what's my Gender, used for segregating

    private:
        std::string details[8]; //all data of students
};

struct Pair 
{
    int first; //ID Number
    Student second; //Other details of the student
};

class HashTable
{
    public:
        //constructor
        HashTable(int size) 
        {
            hGroups = size;
            table = new LinkedList<Pair>[size];
        };

        //destructor
        ~HashTable() { delete table; }; 

        bool isEmpty();
        int numStudents();
        int hashFunc(int); //used for indexing
        void enrollStud(int, Student); //Insertion of student
        bool searchStud(int, bool); //Check if student is available
        void unenrollStud(int); //removes student
        void printType(int); //wrapper for printing functions
        void editInfos(int, int); //specific editing for student's detail
        void fileRead(std::string); //reads a text file with students' records
        void fileWrite(Student); //write a new file called StudentsNewList.txt, infos are formatted and can be reused
                                //make sure to change file name if you want to reuse the prgram to avoid duplication
        
    private:
        int hGroups;
        LinkedList<Pair>* table;
        void printSort(int); //Alphabetical or Based on ID Number
        void printGender(std::string);
};

//----------------------------Comparators for List Sorting------------------------------------
bool compareAlpha(Pair &, Pair &); //compares alphabets
bool compareNum(Pair &, Pair &); //compares numbers


//---------------------------- Student Functions -----------------------------------------------
void Student::inputInfos(int idNum, int wToInput) {
    Helper helper;
    std::string datas[8] = {"ID NUMBER: ", "LAST NAME: ", "FIRST NAME: ", "MIDDLE NAME: ",
                        "GENDER: ", "AGE: ", "CONTACT NUMBER: ", "ADDRESS: ",};

    details[0] = std::to_string(idNum); //id number is stored
    int x = wToInput, row = 8; //if x == 8, input all, else, input only the match of x
    for (int i = 1; i < 8; i++) {
        if (i == x || x == 8) {
            do {
                gotoxy(49, row);
                std::cout << "                                                           "; //used to clear invalid inputs

                gotoxy(48, row);
                std::cout << datas[i]; //prints the data needed
                if (i == 5 || i == 6) { //Age and Contact Number
                    details[i] = helper.returnStringNumInput();
                } else  {
                    details[i] = helper.returnStringWordInput();
                }

            } while (!(helper.inputCheck(i, details[i])));
            row++;
            helper.reformatInfo(details[i]);
        }
    }
}

void Student::printInfos() {
    //more organized way of printing datas
    std::cout.width(7); std::cout << std::left << details[0];
    std::cout.width(18); std::cout << std::left << details[1];
    std::cout.width(18); std::cout << std::left << details[2];
    std::cout.width(18); std::cout << std::left << details[3];
    std::cout.width(8); std::cout << std::left << details[4];
    std::cout.width(5); std::cout << std::left << details[5];
    std::cout.width(15); std::cout << std::left << details[6];
    std::cout.width(15); std::cout << std::left << details[7];;
}

std::string Student::wMyFamName() {
    return details[1];
} 

std::string Student::wMyGender() {
    return details[4];
}

//------------------------------------HASH TABLE FUNCTIONS---------------------------------

void HashTable::fileRead(std::string fileName) {
    Student stud;
    Helper helper;
    std::ifstream inFile(fileName);

    if (inFile.is_open()) {
        std::string line;
        while( std::getline(inFile, line) ) {
            std::stringstream ss(line);
            //copies string separated by comma
            std::getline(ss, stud.details[0], ','); 
            std::getline(ss, stud.details[1], ','); 
            std::getline(ss, stud.details[2], ','); 
            std::getline(ss, stud.details[3], ','); 
            std::getline(ss, stud.details[4], ','); 
            std::getline(ss, stud.details[5], ','); 
            std::getline(ss, stud.details[6], ','); 
            std::getline(ss, stud.details[7], ','); 

            //reformats the informations' capitalization and the number's format
            helper.reformatInfo(stud.details[0]);
            helper.reformatInfo(stud.details[1]);
            helper.reformatInfo(stud.details[2]);
            helper.reformatInfo(stud.details[3]);
            helper.reformatInfo(stud.details[4]);
            helper.reformatInfo(stud.details[5]);
            helper.reformatInfo(stud.details[6]);
            helper.reformatInfo(stud.details[7]);
            enrollStud(stoi(stud.details[0]), stud);
            fileWrite(stud); //wrties it to file called StudentsNewList.txt
        }
        gotoxy(10, 29);
        std::cout << "[SUCCESS AT READING FILE]";
    } else {
        gotoxy(10, 29);
        std::cout << "[UNSUCCESSFUL AT READING FILE]"; //file cannot be found, must be at the same folder
    }
}

void HashTable::fileWrite(Student stud) {
    std::ofstream f("StudentsNewList.txt", f.out | f.app); //.out - file is opened for writng
                                                        //.app - appends existing contents
    f << stud.details[0] << "," << stud.details[1] << "," << stud.details[2] << "," << stud.details[3] << ","
    << stud.details[4] << ","<< stud.details[5] << "," << stud.details[6] << "," << stud.details[7] << "\n";
}

bool HashTable::isEmpty() {
    int sum = 0;
    for (auto&& t: std::make_pair(table, table + hGroups)) { //gets all linkedlist sizes
        sum += t.size();
    }
    if (!sum) { //not zero is 1, thus return true
        return true;
    }
    return false; //not zero
}

int HashTable::numStudents() {
    int sum = 0;
    for (auto&& t: std::make_pair(table, table + hGroups)) { //gets all linkedlist size and that's the number of students
        sum += t.size();
    }
    return sum;
}

int HashTable::hashFunc(int key) {
    return key % hGroups; 
}

void HashTable::enrollStud(int key, Student stud) {
    int hValue = hashFunc(key);
    Pair student; //creates a pair
    student.first = key; //initinialize
    student.second = stud;

    LinkedList<Pair>& rec = table[hValue]; //address is used to edit the content

    if (rec.findNode(key)) {
        rec.deleteAtPos(rec.findNodePos(key)); //deletes the old record if there is similar
        rec.insertEnd(student); //insert it at back
    } else {
        rec.insertEnd(student);
    }
}

void HashTable::unenrollStud(int key) {
    int hValue = hashFunc(key); 
    LinkedList<Pair>& rec = table[hValue];

    if (rec.findNode(key)) {
        searchStud(key, true); //prints the unenrolled student's information
        rec.deleteAtPos(rec.findNodePos(key)); //deletes the record
        gotoxy(13, 27);
        std::cout << "[STUDENT IS REMOVED]\n";
    } else {
        gotoxy(13, 27);
        std::cout << "[STUDENT NOT FOUND]\n";
    }
}

//I can use the linkedlist search node but I won't be able to print the content
//I can but I still need to change the linkedlist header file
bool HashTable::searchStud(int idNum, bool print) {
    int hValue = hashFunc(idNum); 
    LinkedList<Pair> rec = table[hValue];
    Node<Pair> *copy; //used for traversing

    copy = rec.head; //copies the linked list header
    while (copy) {
        if (copy->data.first == idNum) {
            if (print) { //checker if it needs to print it or not
                gotoxy(15,26);
                std::cout << "[STUDENT RECORD]\n";
                gotoxy(48,10);
                copy->data.second.printInfos();
            }
            return true;
        }
        copy = copy->next;
    }

    return false;
}

//wrapper for the printing functions
void HashTable::printType(int numType) {
    switch (numType) {
        case 1:
            printGender("Male");
            break;
        case 2:
            printGender("Female");
            break;
        case 3:
            printSort(1); //alphabetical
            break;
        case 4:
            printSort(2); //numerical
            break;
        default:
            break;
    }
}

void HashTable::printGender(std::string gender) {
    std::vector<Pair> holder; //vector is used so we can use sort function
    Node<Pair> *copy;

    for (auto&& studentList: std::make_pair(table, table + hGroups)) {
        copy = studentList.head;
        while (copy) {
            if (copy->data.second.wMyGender().compare(gender) == 0) { //checher student gender one by one
                holder.push_back(copy->data);
            }
            copy = copy->next;
        }
    }

    sort(holder.begin(), holder.end(), compareNum); //Numerical

    int row = 8;
    for (auto& it : holder) { //prints the datas
        gotoxy(48,row++);
        it.second.printInfos();
    }
    return;
}

void HashTable::printSort(int typeOfSort) {
    std::vector<Pair> holder;
    Node<Pair> *copy;
    
    //copies all the data
    for (auto&& studentList: std::make_pair(table, table + hGroups)) {
        copy = studentList.head;
        while (copy) {
            holder.push_back(copy->data);
            copy = copy->next;
        }
    }
    
    //checks what type of sorting
    switch (typeOfSort) {
        case 1:
            sort(holder.begin(), holder.end(), compareAlpha); //Alphabetical
            break;
        case 2:
            sort(holder.begin(), holder.end(), compareNum); //Numerical
            break;
    }

    int row = 8;
    for (auto& it : holder) {
        gotoxy(48,row++);
        it.second.printInfos();
    }
}

void HashTable::editInfos(int idNum, int toEdit) {
    bool keyExist = false;
    int hValue = hashFunc(idNum); 
    LinkedList<Pair>& rec = table[hValue];
    Node<Pair> *copy = rec.head; //used for traversing

    //looks for match
    while (copy) {
        if (copy->data.first == idNum) {
            copy->data.second.inputInfos(idNum, toEdit);
            keyExist = true;
        }
        copy = copy->next;
    }

    if (!keyExist) {
        gotoxy(48,9);
        std::cout << "[STUDENT DOES NOT EXIST]\n";
    }
}

//-------------------------------COMPARATORS-----------------------------------
bool compareAlpha(Pair &x, Pair &y) {
    if (x.second.wMyFamName().compare(y.second.wMyFamName()) < 0) {
        return true;
    }
    return false;
}

bool compareNum(Pair &x, Pair &y) {
    if (x.first < y.first) {
        return true;
    }
    return false;
}
