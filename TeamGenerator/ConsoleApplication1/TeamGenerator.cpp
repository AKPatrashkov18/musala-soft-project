#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>  

using namespace std;

struct STUDENT
{
    string firstName;
    string LastName;
    int grade;
    string role;
    string email;
    string teamStatus = "Not occupied";
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
    string date;
    string students[4];
    string studentsStatus[4];
};

vector<int> findRole(const vector<STUDENT>& students, const int& studentsCount, const string wantedRole)
{
    vector<int> roleId;
    for (int i = 0; i < studentsCount; i++)
    {
        if (students[i].role == wantedRole)
        {
            roleId.push_back(students[i].id);
        }
    }
    return roleId;
}

int suffleIndex(const vector<STUDENT>& students, const int& studentsCount, const string wantedRole)
{
    vector<int> roleId;
    roleId = findRole(students, studentsCount, wantedRole);
    int shuffle;
    for (int i = 0; i < roleId.size(); i++)
    {
        shuffle = rand() % roleId.size();
        swap(roleId[0], roleId[shuffle]);
    }
    for (int i = 0; i < roleId.size(); i++)
    {
        if (students[i].teamStatus == "Not occupied")
        {
            return roleId[i];
        }
    }
    cout << "sorry but no " << wantedRole << " left";
}

void generateTeam(const vector<STUDENT>& students, const int& studentsCount, vector<TEAM>& teams)
{
    int studentIndex = suffleIndex(students, studentsCount, "Back End");
    teams[0].students[0] = students[studentIndex].firstName + " " + students[studentIndex].LastName;
    int studentIndex = suffleIndex(students, studentsCount, "Front End");
    teams[1].students[1] = students[studentIndex].firstName + " " + students[studentIndex].LastName;
    int studentIndex = suffleIndex(students, studentsCount, "QA");
    teams[2].students[2] = students[studentIndex].firstName + " " + students[studentIndex].LastName;
    int studentIndex = suffleIndex(students, studentsCount, "scrup");
    teams[3].students[3] = students[studentIndex].firstName + " " + students[studentIndex].LastName;
}

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

string makeStudentReport(const vector<STUDENT>& students, const int& studentsCount, int wantedId)
{
    string report;
    report += "First name: " + students[wantedId].firstName + "\n";
    report += "Last name: " + students[wantedId].LastName + "\n";
    report += "Grade: " + to_string(students[wantedId].grade) + "\n";
    report += "Role: " + students[wantedId].role + "\n";
    report += "Email: " + students[wantedId].email + "\n";
    report += "Id: " + to_string(students[wantedId].id) + "\n";

    return report;
}

void createStudentsReport(const vector<STUDENT>& students, const int& studentsCount)
{
    ofstream studentReport("studentsRepost.txt",ios::in, ios::trunc);
    if (studentReport.is_open())
    {
        for (int i = 0; i < studentsCount; i++)
        {
            studentReport << makeStudentReport(students, studentsCount, i);
            studentReport << "\n";
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
    srand(time(NULL));
    vector<STUDENT> students;
    bool exit=false;
    int studentsCount = 0;
    do {
        exit = mainMenu(students, studentsCount);
    } while (exit);
    printStudents(students, studentsCount);
    createStudentsReport(students, studentsCount);
    return 0;
}
