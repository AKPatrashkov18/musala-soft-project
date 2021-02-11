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
    int id;
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
        students[i].id = i;
        studentsCount++;
    }
}

void printStudents(const vector<STUDENT>& students, const int& studentsCount)
{
    for (int i = 0; i < studentsCount; i++)
    {
        cout << "First name: ";
        cout << students[i].firstName << endl;
        cout << "Last name: ";
        cout << students[i].LastName << endl;
        cout << "Grade: ";
        cout << students[i].grade<< endl;
        cout << "Role: ";
        cout << students[i].role << endl;
        cout << "Email: ";
        cout << students[i].email << endl;
    }
}

int findIndex(const vector<STUDENT>& students, const int& studentsCount, int wantedId)
{
    int index;
    for (int i = 0; i < studentsCount; i++)
    {
        if (students[i].id == wantedId)
        {
            return i;
        }
    }
}
string makeStudentReport(const vector<STUDENT>& students, const int& studentsCount, int wantedId)
{
    string report;
    int index = findIndex(students, studentsCount, wantedId);
    report += "First name: " + students[index].firstName + "\n";
    report += "Last name: " + students[index].LastName + "\n";
    report += "Grade: " + to_string(students[index].grade) + "\n";
    report += "Role: " + students[index].role + "\n";
    report += "Email: " + students[index].email + "\n";
    report += "Id: " + to_string(students[index].id) + "\n";

    return report;
}

void createStudentsReport(const vector<STUDENT>& students, const int& studentsCount)
{
    ofstream studentReport("studentsRepost.txt",ios::in, ios::trunc);
    if (studentReport.is_open())
    {
        cout << "Choose from whitch to whitch id you want to create report: ";
        int startindId, edindID;
        cin >> startindId >> edindID;
        for (int i = startindId; i <= edindID; i++)
        {
            studentReport << makeStudentReport(students, studentsCount, i);
        }
    }
    else {
        cout << "error";
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
