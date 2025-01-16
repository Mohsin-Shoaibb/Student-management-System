#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cctype>
#include<Windows.h>
#include<conio.h>
#include<thread>
using namespace std;
const int maxrecords = 100;

/*----------------------------------------------------GUI FUNCTIONS AND ARRAYS--------------------------------*/
int SCREEN_WIDTH = 50;
int SCREEN_HEIGHT = 65;

int first_time = 1;
int selected = 0;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle
COORD position = { 0, 0 };

void gotoxy(int x, int y);
void drawBorder();
void PrintFast();
void MenuBar(const string& label, bool isSelected);
                    /*------------------------------------------------------------------------------------*/

/*----------------------------------------------------ADMIN FUNCTIONS DECLARATION and ARRAYS--------------------------------*/
void admin();
void adminlogin();
void addteacher();
void deleteteacher(string teacherID);
void loadteacherdata();
void saveteacherdata();
bool CheckID(string id);

string TEACHERNAME[maxrecords];
string TEACHERID[maxrecords];
string TEACHERSUBJECT[maxrecords];

string adminpass = "1234";
bool adminlogintime = 0;

string Subjects[] = { "Applied Physics", "Programming Fundamentals", "Functional English", "Calculus and Analytical Geometry", "Islamic Studies" };
/*------------------------------------------------------------------------------------*/

/*----------------------------------------TEACHER FUNCTIONS AND ARRAYS-----------------------------------------*/

void teachermenu();
void teacherlogin();
void addStudent();
void deletestudent(string search);
void PassedStudents();
void FailedStudents();
void CalculateAvgCGPA();
void CalculateCGPA();
void calculateCGPA_for_1_s(string student);
void AssignMarks(string ID);
void ListStudentsa();
void ListStudentsd();
void saveStudentData();
void LoadStudentData();

bool TeacherLoginTime = 0;
/*------------------------------------------------------------------------------------*/

/*----------------------------------------STUDENT FUNCTIONS AND ARRAYS-----------------------------------------*/

void StudentMenu();
string StudentLogin();
void ViewGrades(string ID);
char StudentGrades(float marks);
void ViewCGPA(string ID);

string STUDENTNAME[maxrecords];
string STUDENTID[maxrecords];
string STUDENTCLASS[maxrecords];
float STUDENTGRADES[maxrecords][9];
float CGPA[maxrecords];
float STUDENTCGPA[maxrecords];

bool StudentLoginTime = 0;
string StudentLoginID;
/*------------------------------------------------------------------------------------*/

/*---------------------------------------------------THESE ARE GUI FUNCTIONS-----------------------------------------------------------------------------*/
void gotoxy(int x, int y)   {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder() {

    // for coloring
    cout << "\033[1;314;42m";

    for (int i = 0; i <= SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "||";
        gotoxy(SCREEN_WIDTH * 2, i); cout << "||";
    }

    for (int i = 0; i < SCREEN_WIDTH * 2 + 2; i++) {
        gotoxy(i, 0); cout << "-";
        gotoxy(i, SCREEN_HEIGHT); cout << "-";
    }

    // to reset formatting
    cout << "\033[0m";

    PrintFast();
}

void PrintFast() {

    // for coloring
    cout << "\033[1;91;107m";

    gotoxy(2, 1);
    cout << "    _______   _______   _______   _______       ______    ___ ___   _______   _______   _______   ";
    gotoxy(2, 2);
    cout << "   |   _   | |   _   | |   _   | |       |     |   _  \\  |   Y   | |   _   | |   _   | |   _   |  ";
    gotoxy(2, 3);
    cout << "   |.  1___| |.  1   | |   1___| |.|   | |     |.  |   | |.  |   | |.  1___| |.  1___| |   1___|  ";
    gotoxy(2, 4);
    cout << "   |.  __)   |.  _   | |____   | `-|.  |-'     |.  |   | |.  |   | |.  |___  |.  __)_  |____   |  ";
    gotoxy(2, 5);
    cout << "   |:  |     |:  |   | |:  1   |   |:  |       |:  |   | |:  1   | |:  1   | |:  1   | |:  1   |  ";
    gotoxy(2, 6);
    cout << "   |::.|     |::.|:. | |::.. . |   |::.|       |::.|   | |::.. . | |::.. . | |::.. . | |::.. . |  ";
    gotoxy(2, 7);
    cout << "   `---'     `--- ---' `-------'   `---'       `--- ---' `-------' `-------' `-------' `-------'  ";
    gotoxy(2, 8);
    cout << "                                                                                                  ";
    gotoxy(33, 10);
    cout << "  WELCOME TO FAST NUCES!  ";

    // for reset formatting
    cout << "\033[0m";

}

void MenuBar(const string &label, bool isSelected) {
    if (isSelected) {
        cout << "\033[1;30;107m"; // Highlight: white background, black text
    }
    else {
        cout << "\033[1;37m"; // Normal: white text
    }
    cout << " [  " << label << "  ] " << endl << endl;
    cout << "\033[0m"; // Reset formatting
}
/*------------------------------------------------------------------------------------*/

/*--------------------------------------------------- ( _ < MAIN > _ )-----------------------------------------------------------------------------*/

int main()  {

    // if you are loggin first time, then control the size of the console according to your screen
    if (first_time) {
        cout << "Enter: ";
        _getch();
        first_time = 0;
    }

    loadteacherdata();
    LoadStudentData();

    system("cls"); // Clear screen
    drawBorder();
    
    gotoxy(41, 12);
    cout << "\033[1;91;107m" << "  MAIN MENU  " << "\033[0m";

    do {
        const string menus[] = { "ADMIN", "TEACHER", "STUDENT", "EXIT" };
        char input;

        while (true) {
            gotoxy(6, 15);
            cout << "  Please Select:  " << "\033[0m";

            // for menus
            for (int i = 0; i < 4; i++) {
                cout << "\033[?25l";
                gotoxy(10, 17 + (i * 2));
                MenuBar(menus[i], i == selected);
            }
            gotoxy(65, 18);
            cout << "\033[1;30;107m" << "  Use W/S to navigate  ";
            gotoxy(65, 20);
            cout << "  Press '0' to enter  " << "\033[0m";

            input = _getch();

            if (input == 'w' || input == 'W') {
                selected = (selected - 1 + 4) % 4; // Move up
            }
            else if (input == 's' || input == 'S') {
                selected = (selected + 1) % 4; // Move down
            }
            else if (input == '0') { // '0' key
                gotoxy(38, 26);
                cout << "You selected: " << menus[selected];
                break;
            }
        }
        
        switch (selected+1)
        {
        case 1:
            admin();
            break;
        case 2:
            teachermenu();
            break;
        case 3:
            StudentMenu();
            break;
        default:
            break;
        }

    } while (selected != 3);

    saveteacherdata();
    saveStudentData();
    gotoxy(32, 30);
    cout << "DATA HAS BEEN SAVED IN DATABASE!";
    this_thread::sleep_for(std::chrono::milliseconds(30000)); // Delay
    exit(0);
}
/*------------------------------------------------------------------------------------*/

/*---------------------------------------------------THESE ARE ADMIN FUNCTIONS-----------------------------------------------------------------------------*/
void adminlogin() {
    string search;
    system("cls");
    drawBorder();
    gotoxy(36, 12);
    cout << "\033[1;91;107m" << "  ADMIN LOGIN PAGE  " << "\033[0m";

    gotoxy(10, 16);
    cout << "Enter Admin Password: ";
    cout << "\033[?25h";
    cin >> search;

    if (search == adminpass) {
         gotoxy(37, 20);
         cout << "\033[1;91;107m" << "  WELCOME ADMIN  " << "\033[0m";
         this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
         return;
    }
    else {
        gotoxy(32, 20);
        cout << "\033[91m" << "  LOGIN FAILED! RETURNING BACK! " << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        main();
    }
}

void admin()    {
    if (!adminlogintime) {
        adminlogin();
        adminlogintime = 1;
    }

    system("cls");
    drawBorder();

    gotoxy(40, 12);
    cout << "\033[1;91;107m" << "  ADMIN MENU  " << "\033[0m";

    do {
        const string menus[] = { "ADD TEACHER", "DELETE TEACHER", "BACK TO MAIN MENU" };
        char input;

        while (true) {
            gotoxy(6, 15);
            cout << "  Please Select:  " << "\033[0m";

            // for menus
            for (int i = 0; i < 3; i++) {
                cout << "\033[?25l";
                gotoxy(10, 17 + (i * 2));
                MenuBar(menus[i], i == selected);
            }
            gotoxy(65, 18);
            cout << "\033[1;30;107m" << "  Use W/S to navigate  ";
            gotoxy(65, 20);
            cout << "  Press '0' to enter  " << "\033[0m";

            input = _getch();

            if (input == 'w' || input == 'W') {
                selected = (selected - 1 + 3) % 3; // Move up
            }
            else if (input == 's' || input == 'S') {
                selected = (selected + 1) % 3; // Move down
            }
            else if (input == '0') { // '0' key
                gotoxy(34, 24);
                cout << "You selected: " << menus[selected];
                break;
            }
        }

        switch (selected+1) {
        case 1:
            addteacher();
            break;
        case 2: {
            string teacherID;
            cin.ignore();
            gotoxy(10, 28);
            cout << "ENTER ID OF TEACHER TO DELETE: ";
            cout << "\033[?25h";
            getline(cin, teacherID);
            deleteteacher(teacherID);
        }
        break;

        case 3:
            adminlogintime = 0;
            gotoxy(40, 28);
            cout << "\033[91;107m" << "  GOING BACK!  " << "\033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
            main();
        default:
            cout << "Enter a valid choice\n\n";
            break;
        }
    } while (selected != 2);
}

bool CheckID(string id) {
    int length = id.length();
    if (length != 4) {
        return 0;
    }
    else {
        if (isdigit(id[0]) && isdigit(id[1]) && isdigit(id[2]) && isdigit(id[3])) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

void addteacher()   {
    string TeacherName;
    string TeacherID;
    string TeacherSubject;

    cin.ignore();

    gotoxy(10, 26);
    cout << "Enter The Teacher's ID: ";
    cout << "\033[?25h";
    getline(cin, TeacherID);

    if (!CheckID(TeacherID)) {
        gotoxy(38, 30);
        cout << "\033[91m" << "Invalid ID! Try again" << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        admin();
    }

    bool idcheck = false;

    // to check if the same teacher's ID exists or not
    for (int i = 0; i < maxrecords; i++)    {
        if (TEACHERID[i] == TeacherID)  {
            idcheck = true;
            break;
        }
    }

    if (idcheck)    {
        gotoxy(35, 30);
        cout << "\033[91m" << "Teacher of This ID Already Exists! Going Back!" << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        admin();
    }

    gotoxy(10, 28);
    cout << "Enter the Teacher's Name: ";
    getline(cin, TeacherName);

    gotoxy(60, 27);
    cout << "\033[1;91;107m" << "  Subjects can be:  " << "\033[0m";
    for (int k = 0; k < 5; k++) {
        gotoxy(65, 29 + (k*2));
        cout << Subjects[k];
    }

    gotoxy(10, 30);
    cout << "Enter the Teacher's Subjcct: ";
    getline(cin, TeacherSubject);

    int cord = 30;

    bool subject_choose = 0;
    while (subject_choose == 0) {
        for (int k = 0; k < 5; k++) {
            if (TeacherSubject == Subjects[k])  subject_choose = 1;
        }

        if (subject_choose == 0) {
            gotoxy(10, cord += 2);
            cout << "\033[91m" << "Invalid Input! Choose from given Subjects!" << "\033[0m";
            gotoxy(10, cord += 2);
            cout << "Enter the Teacher's Subjcct: ";
            getline(cin, TeacherSubject);
        }
    }

    for (int i = 0; i < maxrecords; i++)    {

        if (TEACHERID[i] == "" || TEACHERID[i] == "DELETED")    {
            TEACHERID[i] = TeacherID;
            TEACHERNAME[i] = TeacherName;
            TEACHERSUBJECT[i] = TeacherSubject;

            gotoxy(36, cord += 5);
            cout << "\033[91;107m" << "TEACHER ADDED SUCCESSFULLY!" << "\033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
            saveteacherdata();
            admin();
        }
    }

}

void deleteteacher(string ID)   {
    int count = 0;
    for (int i = 0; i < maxrecords; i++)    {
        if (TEACHERID[i] == ID) {
            count++;
            TEACHERID[i] = "DELETED";
            TEACHERNAME[i] = "DELETED";
            TEACHERSUBJECT[i] = "DELETED";
            gotoxy(30, 31);
            cout << "\033[91;107m" << "TEACHER ID " << ID << " RECORD REMOVED SUCCESSFULLY!" << "\033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
            saveteacherdata();
            admin();
        }
    }

    if (count == 0) {
        gotoxy(31, 31);
        cout << "\033[91m" << "NO Teacher with this ID EXISTS IN RECORDS!" << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        admin();
    }
}

/*---------------------FILE HANDLING---------------------*/
void saveteacherdata()
{
    ofstream teacherfile;
    teacherfile.open("D:\\semester 1\\Student Management system\\teacher.csv", ios::trunc);

    for (int i = 0;i < maxrecords && TEACHERID[i] != ""; i++)
    {
        if (!(TEACHERID[i] == "DELETED")) {
            teacherfile << TEACHERID[i] << "," << TEACHERNAME[i] << "," << TEACHERSUBJECT[i] << endl;
        }
    }

    teacherfile.close();
}

void loadteacherdata()
{
    string line;
    ifstream teachers("D:\\semester 1\\Student Management system\\teacher.csv");

    if (teachers.is_open())
    {
        int i = 0;
        while (getline(teachers, line))
        {
            stringstream t_data(line);
            getline(t_data, TEACHERID[i], ',');
            getline(t_data, TEACHERNAME[i], ',');
            getline(t_data, TEACHERSUBJECT[i], ',');

            i++;
            if (i >= maxrecords)    break;
        }
        teachers.close();
    }
    else
    {
        cout << "\n\t\t ERROR: Unable to fetch data from file!\n";
    }
}
/*------------------------------------------------------------------------------------*/

/*---------------------------------------------------THESE ARE TEACHER FUNCTIONS-----------------------------------------------------------------------------*/
void teacherlogin() {
    string search;
    system("cls");
    drawBorder();
    gotoxy(35, 12);
    cout << "\033[1;91;107m" << "  TEACHER LOGIN PAGE  " << "\033[0m";

    gotoxy(10, 16);
    cout << "Enter Teacher ID: ";
    cout << "\033[?25h";
    cin >> search;
    bool teacher_login = 0;

    for (int i = 0; i < maxrecords && TEACHERID[i] != ""; i++) {
        if (TEACHERID[i] == search) {
            teacher_login = 1;
            gotoxy(35, 20);
            cout << "\033[1;91;107m" << "  WELCOME " << TEACHERNAME[i] << "  " << "\033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
            return;
        }
    }

    if (teacher_login == 0) {
        gotoxy(30, 20);
        cout << "\033[91m" << "  LOGIN FAILED! RETURNING BACK! " << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        main();
    }
}

void teachermenu()  {
    if (TeacherLoginTime == 0) {
        teacherlogin();
        TeacherLoginTime = 1;
    }

    system("cls");
    drawBorder();

    gotoxy(39, 12);
    cout << "\033[1;91;107m" << "  TEACHER MENU  " << "\033[0m";

    do {
        const string menus[] = { "ADD STUDENT", "DELETE STUDENT", "CALCULATE CGPA", "CALCULATE AVERAGE CGPA", "ASSIGN MARKS", "LIST PASSED STUDENTS", "LIST FAILED STUDENTS", "LIST OF STUDENTS", "BACK TO MAIN MENU" };
        char input;

        while (true) {
            gotoxy(6, 15);
            cout << "  Please Select:  " << "\033[0m";

            // for menus
            for (int i = 0; i < 9; i++) {
                cout << "\033[?25l";
                gotoxy(10, 17 + (i * 2));
                MenuBar(menus[i], i == selected);
            }
            gotoxy(65, 18);
            cout << "\033[1;30;107m" << "  Use W/S to navigate  ";
            gotoxy(65, 20);
            cout << "  Press '0' to enter  " << "\033[0m";

            input = _getch();

            if (input == 'w' || input == 'W') {
                selected = (selected - 1 + 9) % 9; // Move up
            }
            else if (input == 's' || input == 'S') {
                selected = (selected + 1) % 9; // Move down
            }
            else if (input == '0') { // '0' key
                gotoxy(32, 36);
                cout << "You selected: " << menus[selected];
                break;
            }
        }

        switch (selected+1) {
        case 1:
            addStudent();
            break;
        case 2:
        {
            string studentid;
            cin.ignore();
            gotoxy(10, 39);
            cout << "Enter The Student ID to DELETE The Record: ";
            cout << "\033[?25h";
            getline(cin, studentid);
            deletestudent(studentid);
        }
        case 3: {
            string s_ID;
            cin.ignore();
            gotoxy(10, 39);
            cout << "Enter The Student ID to Calculate CGPA: ";
            cout << "\033[?25h";
            getline(cin, s_ID);
            calculateCGPA_for_1_s(s_ID);
            break;
        }
        case 4:
            CalculateAvgCGPA();
            break;
        case 5: {
            string studentid;
            cin.ignore();
            gotoxy(10, 39);
            cout << "Enter The Student ID to Assign the Marks: ";
            cout << "\033[?25h";
            getline(cin, studentid);
            AssignMarks(studentid);
            break;
        }
        case 6:
            PassedStudents();
        case 7:
            FailedStudents();
        case 8: {
            int option;
            gotoxy(10, 39);
            cout << "1. ASCENDING ORDER";
            gotoxy(10, 40);
            cout << "2. DESCENDING ORDER";
            gotoxy(10, 42);
            cout << "Enter: ";
            cout << "\033[?25h";
            cin >> option;
            if (option == 1) {
                ListStudentsa();
            }
            else if (option == 2) {
                ListStudentsd();
            }
            else {
                gotoxy(10, 44);
                cout << "\033[91m" << "Invalid Input! Try Again!" << "\033[0m";
                this_thread::sleep_for(std::chrono::milliseconds(2000)); // Delay
                teachermenu();
            }
        }
        case 9:
            TeacherLoginTime = 0;
            main();
        default:
            cout << "\n\t\tEnter A Valid Choice From Given: \n\n";
        }

    } while (selected != 8);
}

void addStudent()   {
    string ID, Name, Class;

    for (int i = 0; i < maxrecords; i++)    {

        if (STUDENTID[i] == "" || STUDENTID[i] == "DELETED")    {

            gotoxy(10, 39);
            cout << "Enter Roll Number for Student: ";
            cout << "\033[?25h";
            cin >> ID;

            int cord = 39;

            while (!CheckID(ID)) {
                gotoxy(10, cord += 2);
                cout << "\033[91m" << "Enter A valid 4-Digit Roll Number: " << "\033[0m";
                this_thread::sleep_for(std::chrono::milliseconds(2000)); // Delay
                cin >> ID;
            }

            // to check if the student id already exists or not
            bool checkid = false;

            for (int j = 0; j < maxrecords; j++)    {
                if (STUDENTID[j] == ID) {
                    checkid = true;
                    break;
                }
            }
            if (checkid)    {
                gotoxy(27, cord += 5);
                cout << "\033[91m" << "A Student With This Roll Already Exists. GOING BACK!" << "\033[0m";
                this_thread::sleep_for(std::chrono::milliseconds(2000)); // Delay
                teachermenu();
            }
            //--------------------

            cin.ignore();
            gotoxy(10, cord += 2);
            cout << "Enter Student Name: ";
            getline(cin, Name);

            gotoxy(10, cord += 2);
            cout << "Enter Student Class ( EX: BSCS-1A): ";
            getline(cin, Class);

            STUDENTID[i] = ID;
            STUDENTNAME[i] = Name;
            STUDENTCLASS[i] = Class;

            for (int j = 0; j < 9; j++) {
                STUDENTGRADES[i][j] = 0;
            }

            char choice;
            int j;

            gotoxy(10, cord += 2);
            cout << "Do You Want to Enter marks for Quizes? (Y/N): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << endl;
                for (j = 0; j < 3; j++) {
                    gotoxy(10, cord += 1);
                    cout << "Enter marks for Quiz " << j + 1 << " (out of 100): ";
                    cin >> STUDENTGRADES[i][j];

                    // if marks are greater than 100
                    while (STUDENTGRADES[i][j] > 100) {
                        gotoxy(10, cord += 2);
                        cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                        cin >> STUDENTGRADES[i][j];
                    }
                }
            }

            gotoxy(10, cord += 2);
            cout << "Do You Want to Enter marks for Assignments? (Y/N): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << endl;
                for (j = 3; j < 6; j++) {
                    gotoxy(10, cord += 1);
                    cout << "Enter marks for Assignment " << j - 2 << " (out of 100): ";
                    cin >> STUDENTGRADES[i][j];

                    // if marks are greater than 100
                    while (STUDENTGRADES[i][j] > 100) {
                        gotoxy(10, cord += 2);
                        cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                        cin >> STUDENTGRADES[i][j];
                    }
                }
            }

            gotoxy(10, cord += 2);
            cout << "Do You Want to Enter marks for Exams? (Y/N): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {

                gotoxy(10, cord += 1);
                cout << "Enter Marks for Sessional 1 (out of 100): ";
                cin >> STUDENTGRADES[i][6];

                // if marks are greater than 100
                while (STUDENTGRADES[i][6] > 100) {
                    gotoxy(10, cord += 2);
                    cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                    cin >> STUDENTGRADES[i][6];
                }
                gotoxy(10, cord += 1);
                cout << "Enter Marks for Sessional 2 (out of 100): ";
                cin >> STUDENTGRADES[i][7];

                // if marks are greater than 100
                while (STUDENTGRADES[i][7] > 100) {
                    gotoxy(10, cord += 2);
                    cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                    cin >> STUDENTGRADES[i][7];
                }

                gotoxy(10, cord += 1);
                cout << "Enter Marks for Final Exams (out of 100): ";
                cin >> STUDENTGRADES[i][8];

                // if marks are greater than 100
                while (STUDENTGRADES[i][8] > 100) {
                    gotoxy(10, cord += 2);
                    cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                    cin >> STUDENTGRADES[i][8];
                }
            }

            gotoxy(35, cord += 3);
            cout << "\033[91;107m" << "  STUDENT ADDED SUCCESSFULLY!  " << "\033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
            saveStudentData();
            teachermenu();

        }
    }
}

void deletestudent(string search)   {
    int count = 0;

    for (int i = 0; i < maxrecords; i++)    {

        if (STUDENTID[i] == search) {

            count++;
            STUDENTID[i] = "DELETED";
            STUDENTNAME[i] = "DELETED";
            STUDENTCLASS[i] = "DELETED";

            for (int j = 0; j < 9; j++) {
                STUDENTGRADES[i][j] = 0;
            }
            CGPA[i] = 0;
            gotoxy(31, 43);
            cout << "\033[91;107m" << "  STUDENT RECORD REMOVED SUCCESSFULLY!  " << "\033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
            saveStudentData();
            teachermenu();
        }
    }
    if (count == 0) {
        gotoxy(28, 42);
        cout << "\033[91m" << "No Student With ID " << search << " Exists in Records!!" << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        teachermenu();
    }
}

void PassedStudents() {

    system("cls");
    drawBorder();

    gotoxy(31, 12);
    cout << "\033[1;91;107m" << "   LIST OF PASSED STUDENTS    " << "\033[0m";

    CalculateCGPA();
    int count = 0;

    // to count no of passed students
    for (int i = 0; i < maxrecords; i++) {
        if (STUDENTID[i] == "") break;
        else if (STUDENTID[i] != "DELETED" && CGPA[i] >= 2) {
            count++;
        }
    }

    if (count != 0) {
        // for white background
        for (int k = 0; k < count + 4; k++) {
            for (int s = 0; s < 72; s++) {
                gotoxy(13 + s, 15 + k);
                cout << "\033[107m" << " " << "\033[0m";
            }
        }

        // for black borders
        for (int k = 0; k < count + 2; k++) {
            for (int s = 0; s < 67; s++) {
                gotoxy(15 + s, 16 + k);
                if (k == 0 || s == 1 || s == 65 || k == count + 1 || s == 0 || s == 66) {
                    cout << "\033[40m" << " " << "\033[0m";
                }
            }
        }

        gotoxy(33, 16);
        cout << "\033[97;40m" << "Name" << "\033[0m";
        gotoxy(59, 16);
        cout << "\033[97;40m" << "CGPA" << "\033[0m";

        int p = 0;
        for (int i = 0; i < maxrecords; i++) {
            if (STUDENTID[i] == "") break;
            else if (STUDENTID[i] != "DELETED" && CGPA[i] >= 2) {
                gotoxy(28, 17 + p);
                cout << "\033[30;107m" << STUDENTNAME[i] << "\033[0m";
                gotoxy(56, 17 + p);
                cout << "\033[30;107m" << CGPA[i] << "\033[0m";
                p++;
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(7000)); // Delay
    }

    else {
        gotoxy(34, 15);
        cout << "There are no Students Passed!";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        teachermenu();
    }

    teachermenu();
}

void FailedStudents() {
    system("cls");

    drawBorder();

    gotoxy(31, 12);
    cout << "\033[1;91;107m" << "   LIST OF FAILED STUDENTS    " << "\033[0m";

    CalculateCGPA();
    int count = 0;

    // to count no of passed students
    for (int i = 0; i < maxrecords; i++) {
        if (STUDENTID[i] == "") break;
        else if (STUDENTID[i] != "DELETED" && CGPA[i] < 2) {
            count++;
        }
    }

    if (count != 0) {
        // for white background
        for (int k = 0; k < count + 4; k++) {
            for (int s = 0; s < 72; s++) {
                gotoxy(13 + s, 15 + k);
                cout << "\033[107m" << " " << "\033[0m";
            }
        }

        // for black borders
        for (int k = 0; k < count + 2; k++) {
            for (int s = 0; s < 67; s++) {
                gotoxy(15 + s, 16 + k);
                if (k == 0 || s == 1 || s == 65 || k == count + 1 || s == 0 || s == 66) {
                    cout << "\033[40m" << " " << "\033[0m";
                }
            }
        }

        gotoxy(33, 16);
        cout << "\033[97;40m" << "Name" << "\033[0m";
        gotoxy(59, 16);
        cout << "\033[97;40m" << "CGPA" << "\033[0m";

        int p = 0;
        for (int i = 0; i < maxrecords; i++) {
            if (STUDENTID[i] == "") break;
            else if (STUDENTID[i] != "DELETED" && CGPA[i] < 2) {
                gotoxy(28, 17 + p);
                cout << "\033[30;107m" << STUDENTNAME[i] << "\033[0m";
                gotoxy(56, 17 + p);
                cout << "\033[30;107m" << CGPA[i] << "\033[0m";
                p++;
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(7000)); // Delay
    }

    else {
        gotoxy(34, 15);
        cout << "There are no Students Passed!";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        teachermenu();
    }

    teachermenu();
}

void ListStudentsa() {
    CalculateCGPA();
    string sortedName[maxrecords];
    float sortedCGPA[maxrecords];

    int j = 0;
    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++, j++) {
        if (STUDENTID[i] == "DELETED") {
            j--;
            continue;
        }
        sortedName[j] = STUDENTNAME[i];
        sortedCGPA[j] = CGPA[i];
    }

    for (int i = 0; i < j; i++) {
        bool swapped = 0;
        for (int k = 0; k < j - 1; k++) {
            if (sortedCGPA[k] > sortedCGPA[k + 1]) {
                swap(sortedCGPA[k], sortedCGPA[k + 1]);
                swap(sortedName[k], sortedName[k + 1]);
                swapped = 1;
            }
        }
        if (!swapped)   break;
    }

    system("cls");

    drawBorder();

    gotoxy(30, 12);
    cout << "\033[1;91;107m" << "  LIST OF STUDENTS (ASCENDING) " << "\033[0m";

    CalculateCGPA();
    int count = 0;

    // to count no of passed students
    for (int i = 0; i < maxrecords; i++) {
        if (STUDENTID[i] == "") break;
        else if (STUDENTID[i] != "DELETED") {
            count++;
        }
    }

    if (count != 0) {
        // for white background
        for (int k = 0; k < count + 4; k++) {
            for (int s = 0; s < 72; s++) {
                gotoxy(13 + s, 15 + k);
                cout << "\033[107m" << " " << "\033[0m";
            }
        }

        // for black borders
        for (int k = 0; k < count + 2; k++) {
            for (int s = 0; s < 67; s++) {
                gotoxy(15 + s, 16 + k);
                if (k == 0 || s == 1 || s == 65 || k == count + 1 || s == 0 || s == 66) {
                    cout << "\033[40m" << " " << "\033[0m";
                }
            }
        }

        gotoxy(33, 16);
        cout << "\033[97;40m" << "Name" << "\033[0m";
        gotoxy(59, 16);
        cout << "\033[97;40m" << "CGPA" << "\033[0m";

        int p = 0;
        for (int i = 0; i < maxrecords; i++) {
            if (STUDENTID[i] == "") break;
            else if (STUDENTID[i] != "DELETED") {
                gotoxy(28, 17 + p);
                cout << "\033[30;107m" << sortedName[i] << "\033[0m";
                gotoxy(56, 17 + p);
                cout << "\033[30;107m" << sortedCGPA[i] << "\033[0m";
                p++;
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(7000)); // Delay
        teachermenu();
    }
}

void ListStudentsd() {
    CalculateCGPA();
    string sortedName[maxrecords];
    float sortedCGPA[maxrecords];

    int j = 0;
    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++, j++) {
        if (STUDENTID[i] == "DELETED") {
            j--;
            continue;
        }
        sortedName[j] = STUDENTNAME[i];
        sortedCGPA[j] = CGPA[i];
    }

    for (int i = 0; i < j; i++) {
        bool swapped = 0;
        for (int k = 0; k < j - 1; k++) {
            if (sortedCGPA[k] < sortedCGPA[k + 1]) {
                swap(sortedCGPA[k], sortedCGPA[k + 1]);
                swap(sortedName[k], sortedName[k + 1]);
                swapped = 1;
            }
        }
        if (!swapped)   break;
    }

    system("cls");

    drawBorder();

    gotoxy(30, 12);
    cout << "\033[1;91;107m" << "  LIST OF STUDENTS (DESCENDING) " << "\033[0m";

    CalculateCGPA();
    int count = 0;

    // to count no of passed students
    for (int i = 0; i < maxrecords; i++) {
        if (STUDENTID[i] == "") break;
        else if (STUDENTID[i] != "DELETED") {
            count++;
        }
    }

    if (count != 0) {
        // for white background
        for (int k = 0; k < count + 4; k++) {
            for (int s = 0; s < 72; s++) {
                gotoxy(13 + s, 15 + k);
                cout << "\033[107m" << " " << "\033[0m";
            }
        }

        // for black borders
        for (int k = 0; k < count + 2; k++) {
            for (int s = 0; s < 67; s++) {
                gotoxy(15 + s, 16 + k);
                if (k == 0 || s == 1 || s == 65 || k == count + 1 || s == 0 || s == 66) {
                    cout << "\033[40m" << " " << "\033[0m";
                }
            }
        }

        gotoxy(33, 16);
        cout << "\033[97;40m" << "Name" << "\033[0m";
        gotoxy(59, 16);
        cout << "\033[97;40m" << "CGPA" << "\033[0m";

        int p = 0;
        for (int i = 0; i < maxrecords; i++) {
            if (STUDENTID[i] == "") break;
            else if (STUDENTID[i] != "DELETED") {
                gotoxy(28, 17 + p);
                cout << "\033[30;107m" << sortedName[i] << "\033[0m";
                gotoxy(56, 17 + p);
                cout << "\033[30;107m" << sortedCGPA[i] << "\033[0m";
                p++;
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(7000)); // Delay
        teachermenu();
    }
}

/*---------------------CGPA CALCULATION---------------------*/
void calculateCGPA_for_1_s(string student)  {

    CalculateCGPA();

    bool found = 0;

    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++) {

        if (STUDENTID[i] == student) {
            found = 1;

            gotoxy(30, 42);
            cout << "CGPA for Student " << STUDENTNAME[i] << ": \033[91;107m  " << CGPA[i] << "  \033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(5000)); // Delay
            teachermenu();
        }
    }

    if (found == 0) {
        gotoxy(28, 44);
        cout << "\033[91m" << "No Student With ID " << student << " Exists in Records!!" << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        teachermenu();
    }
}

void CalculateAvgCGPA() {

    CalculateCGPA();

    float avgCGPA = 0;
    int i;
    for (i = 0; i < maxrecords && STUDENTID[i] != ""; i++) {
        if (STUDENTID[i] != "DELETED") {
            avgCGPA += CGPA[i];
        }
    }

    avgCGPA /= i;
    gotoxy(29, 40);
    cout << "Average CGPA of all students: " << "\033[91;107m  " << avgCGPA << "  \033[0m";
    this_thread::sleep_for(std::chrono::milliseconds(5000)); // Delay
    teachermenu();
}

void AssignMarks(string ID) {
    bool found = 0;

    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++) {
        if (STUDENTID[i] == ID) {
            found = 1;

            char choice;
            int j;
            int cord = 40;

            gotoxy(10, cord += 2);
            cout << "Do You Want to Enter marks for Quizes? (Y/N): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << endl;
                for (j = 0; j < 3; j++) {
                    gotoxy(10, cord += 1);
                    cout << "Enter marks for Quiz " << j + 1 << " (out of 100): ";
                    cin >> STUDENTGRADES[i][j];

                    // if marks are greater than 100
                    while (STUDENTGRADES[i][j] > 100) {
                        gotoxy(10, cord += 2);
                        cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                        cin >> STUDENTGRADES[i][j];
                    }
                }
            }

            gotoxy(10, cord += 2);
            cout << "Do You Want to Enter marks for Assignments? (Y/N): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << endl;
                for (j = 3; j < 6; j++) {
                    gotoxy(10, cord += 1);
                    cout << "Enter marks for Assignment " << j - 2 << " (out of 100): ";
                    cin >> STUDENTGRADES[i][j];

                    // if marks are greater than 100
                    while (STUDENTGRADES[i][j] > 100) {
                        gotoxy(10, cord += 2);
                        cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                        cin >> STUDENTGRADES[i][j];
                    }
                }
            }

            gotoxy(10, cord += 2);
            cout << "Do You Want to Enter marks for Exams? (Y/N): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {

                gotoxy(10, cord += 1);
                cout << "Enter Marks for Sessional 1 (out of 100): ";
                cin >> STUDENTGRADES[i][6];

                // if marks are greater than 100
                while (STUDENTGRADES[i][6] > 100) {
                    gotoxy(10, cord += 2);
                    cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                    cin >> STUDENTGRADES[i][6];
                }
                gotoxy(10, cord += 1);
                cout << "Enter Marks for Sessional 2 (out of 100): ";
                cin >> STUDENTGRADES[i][7];

                // if marks are greater than 100
                while (STUDENTGRADES[i][7] > 100) {
                    gotoxy(10, cord += 2);
                    cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                    cin >> STUDENTGRADES[i][7];
                }

                gotoxy(10, cord += 1);
                cout << "Enter Marks for Final Exams (out of 100): ";
                cin >> STUDENTGRADES[i][8];

                // if marks are greater than 100
                while (STUDENTGRADES[i][8] > 100) {
                    gotoxy(10, cord += 2);
                    cout << "\033[91m" << "Invalid Input! Enter again: " << "\033[0m";
                    cin >> STUDENTGRADES[i][8];
                }
            }
            gotoxy(33, cord += 3);
            cout << "\033[91;107m" << "  MARKS UPDATED SUCCESSFULLY  " << "\033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
            saveStudentData();
            teachermenu();
        }
    }

    if (found == 0) {
        gotoxy(28, 42);
        cout << "\033[91m" << "No Student With ID " << ID << " Exists in Records!" << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        teachermenu();
    }

}

void CalculateCGPA() {
    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++) {
        float marks = 0;
        float TotalGrades = 0;

        // for Quized
        for (int j = 0; j < 3; j++) {
            marks += STUDENTGRADES[i][j];
        }
        TotalGrades += (marks / 300.0) * 10.0;

        // for Assignments
        marks = 0;
        for (int j = 3; j < 6; j++) {
            marks += STUDENTGRADES[i][j];
        }
        TotalGrades += (marks / 300.0) * 10.0;

        // for Seasionals
        marks = STUDENTGRADES[i][6] + STUDENTGRADES[i][7];
        TotalGrades += (marks / 200.0) * 30.0;

        // for Final Exams
        marks = STUDENTGRADES[i][8];
        TotalGrades += marks / 2.0;

        // Calculating CGPA
        CGPA[i] = (TotalGrades / 100.0) * 4.0;
    }
    return;
}
/*------------------------------------------------------------------------------------*/

/*---------------------------------------------------THESE ARE STUDENT FUNCTIONS-----------------------------------------------------------------------------*/

void StudentMenu() {
    if (!StudentLoginTime) {
        StudentLoginID = StudentLogin();
        StudentLoginTime = 1;
    }

    system("cls");

    drawBorder();

    gotoxy(39, 12);
    cout << "\033[1;91;107m" << "  STUDENT MENU  " << "\033[0m";

    do {
        const string menus[] = { "VIEW GRADES", "VIEW CGPA", "RETURN TO MAIN MENU" };
        char input;

        while (true) {
            gotoxy(6, 15);
            cout << "  Please Select:  " << "\033[0m";

            for (int i = 0; i < 3; i++) {
                cout << "\033[?25l";
                gotoxy(10, 17 + (i * 2));
                MenuBar(menus[i], i == selected);
            }
            gotoxy(65, 18);
            cout << "\033[1;30;107m" << "  Use W/S to navigate  ";
            gotoxy(65, 20);
            cout << "  Press '0' to enter  " << "\033[0m";

            input = _getch();

            if (input == 'w' || input == 'W') {
                selected = (selected - 1 + 3) % 3; // Move up
            }
            else if (input == 's' || input == 'S') {
                selected = (selected + 1) % 3; // Move down
            }
            else if (input == '0') { // '0' key
                gotoxy(34, 25);
                cout << "You selected: " << menus[selected];
                break;
            }
        }

        switch (selected + 1) {
        case 1:
            ViewGrades(StudentLoginID);
            break;
        case 2:
            ViewCGPA(StudentLoginID);
            break;
        case 3:
            StudentLoginTime = 0;
            main();
        default:
            cout << "\n\t\tEnter A Valid Choice From Given: \n\n";
        }
    } while (selected != 2);
}

string StudentLogin() {
    string search;
    system("cls");
    drawBorder();
    gotoxy(35, 12);
    cout << "\033[1;91;107m" << "  STUDENT LOGIN PAGE  " << "\033[0m";

    gotoxy(10, 16);
    cout << "Enter Student ID: ";
    cout << "\033[?25h";
    cin >> search;
    bool teacher_login = 0;

    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++) {
        if (STUDENTID[i] == search) {
            teacher_login = 1;
            gotoxy(35, 20);
            cout << "\033[1;91;107m" << "  WELCOME " << STUDENTNAME[i] << "  " << "\033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
            return search;
        }
    }

    if (teacher_login == 0) {
        gotoxy(30, 20);
        cout << "\033[91m" << "  LOGIN FAILED! RETURNING BACK! " << "\033[0m";
        this_thread::sleep_for(std::chrono::milliseconds(3000)); // Delay
        main();
    }
}

void ViewGrades(string ID) {
    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++) {
        if (STUDENTID[i] == ID) {
            for (int j = 0; j < 3; j++) {
                gotoxy(10, 27 + (j * 2));
                cout << "Marks for Quiz " << j + 1 << ": " << StudentGrades(STUDENTGRADES[i][j]);
            }

            for (int j = 3; j < 6; j++) {
                gotoxy(10, 34 + ((j - 3) * 2));
                cout << "Marks for Assignment " << j - 2 << ": " << StudentGrades(STUDENTGRADES[i][j]);
            }

            gotoxy(10, 41);
            cout << "Marks for Seasional 1: " << StudentGrades(STUDENTGRADES[i][6]);
            gotoxy(10, 43);
            cout << "Marks for Seasional 2: " << StudentGrades(STUDENTGRADES[i][7]);

            gotoxy(10, 46);
            cout << "Marks for Final Exam: " << StudentGrades(STUDENTGRADES[i][8]);
            this_thread::sleep_for(std::chrono::milliseconds(5000)); // Delay
            StudentMenu();
        }
    }
}

void ViewCGPA(string ID) {
    CalculateCGPA();

    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++) {

        if (STUDENTID[i] == ID) {
            gotoxy(35, 29);
            cout << "Your CGPA: \033[91;107m  " << CGPA[i] << "  \033[0m";
            this_thread::sleep_for(std::chrono::milliseconds(5000)); // Delay
            StudentMenu();
        }
    }
}

char StudentGrades(float marks) {
    if (marks >= 90) {
        return 'A';
    }
    else if (marks >= 80) {
        return 'B';
    }
    else if (marks >= 70) {
        return 'C';
    }
    else if (marks >= 60) {
        return 'D';
    }
    else if (marks >= 50) {
        return 'E';
    }
    else {
        return 'F';
    }
}

/*---------------------FILE HANDLING---------------------*/
void saveStudentData()
{
    ofstream studentFile;
    studentFile.open("D:\\semester 1\\Student Management system\\students.csv", ios::trunc);

    for (int i = 0; i < maxrecords && STUDENTID[i] != ""; i++)
    {
        if (STUDENTID[i] != "DELETED") {
            studentFile << STUDENTID[i] << "," << STUDENTNAME[i] << "," << STUDENTCLASS[i];

            for (int j = 0; j < 9; j++)
            {
                studentFile << "," << STUDENTGRADES[i][j];
            }
            studentFile << endl;
        }
    }

    studentFile.close();
}

void LoadStudentData()  {
    string line;
    ifstream studentFile("D:\\semester 1\\Student Management system\\students.csv");

    if (studentFile.is_open())
    {
        int i = 0;
        while (getline(studentFile, line))
        {
            stringstream s_data(line);

            getline(s_data, STUDENTID[i], ',');
            getline(s_data, STUDENTNAME[i], ',');
            getline(s_data, STUDENTCLASS[i], ',');

            for (int j = 0; j < 9; j++)
            {
                string temp;
                getline(s_data, temp, ',');
                if (temp == "0") {
                    STUDENTGRADES[i][j] = 0;
                }
                else STUDENTGRADES[i][j] = stof(temp);
            }

            i++;
            if (i >= maxrecords)    break;
        }
        studentFile.close();
    }
    else
    {
        cout << "\n\t\tERROR: Unable to fetch data from file!\n";
    }
}
/*------------------------------------------------------------------------------------*/