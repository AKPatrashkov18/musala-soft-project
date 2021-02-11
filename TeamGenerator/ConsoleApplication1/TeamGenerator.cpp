#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT
{
    string firstName;
    string LastName;
    int grade;
    string role;
    string email;
    string teamName = "Not occupied";
};

struct TEACHERS
{
    string firstName;
    string LastTeam;
    vector<string> teachingTeams;
};

struct TEAM
{
    string name;
    string discription;
    int day, mounth, year;
    string students[4];
    string studentsStatus[4];
};

void addStudent(vector<STUDENT>& students, int& studentsCount)
{
    cout << "How many students do you want to enter: ";
    int quantity;
    cin >> quantity;
    quantity += studentsCount;
    for (int i = studentsCount; i < quantity; i++)
    {
        students.push_back(STUDENT());
        cin >> students[i].firstName;
        cin >> students[i].LastName;
        cin >> students[i].grade;
        cin >> students[i].role;
        cin >> students[i].email;
        studentsCount++;
    }
}

void printStudents(const vector<STUDENT>& students, int& studentsCount)
{
    for (int i = 0; i < studentsCount; i++)
    {
        cout << students[i].firstName << endl;
        cout << students[i].LastName << endl;
        cout << students[i].grade << endl;
        cout << students[i].role << endl;
        cout << students[i].email << endl;
    }
}

void deleteStudents(vector<STUDENT>& students, int& studentsCount)
{
    int deleteIndex;
    cin >> deleteIndex;
    students.erase(students.begin() + deleteIndex);
    studentsCount--;
}

void editStudent(vector<STUDENT>& students)
{
    cout << "choose index: ";
    int index;
    cin >> index;
    cout << endl;
    cout << "1. name" << endl;
    cout << "2. lastname" << endl;
    cout << "3. grade" << endl;
    cout << "4. role" << endl;
    cout << "5. email" << endl;
    int option;
    cin >> option;
    switch (option)
    {
        case 1:
            cin>>students[index].firstName;
            break;
        case 2:
            cin >> students[index].LastName;
            break;
        case 3:
            cin >> students[index].grade;
            break;
        case 4:
            cin >> students[index].role;
            break;
        case 5:
            cin >> students[index].email;
            break;
        default:
            break;
    }
}

bool mainMenu(vector<STUDENT>& students, int& studentsCount)
{
    cout << "1. Add students or teachers"<<endl;
    cout << "2. Generate team"<<endl;
    cout << "3. Edit teams, students or teachers"<<endl;
    cout << "4. Print teams, students or teachers" << endl;
    cout << "9. Exit"<<endl;
    int option;
    cin >> option;
    switch (option)
    {
        case 1:
            addStudent(students, studentsCount);
            return true;
            break;
        case 2:
            return true;
            break;
        case 3:
            editStudent(students);
            return true;
            break;
        case 4:
            return true;
            break;
        case 9:
            return false;
            break;
        default:
            return mainMenu(students, studentsCount);

    }
}

int main()
{
    vector<STUDENT> students;
    bool exit=false;
    int studentsCount = 0;
    do {
        exit = mainMenu(students, studentsCount);
    } while (exit);
    deleteStudents(students, studentsCount);
    printStudents(students, studentsCount);
    return 0;
}
