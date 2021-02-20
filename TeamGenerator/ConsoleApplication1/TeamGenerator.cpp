#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>  

using namespace std;

struct STUDENT
{
    string firstName;
    string lastName;
    int grade;
    string role;
    string email;
    string teamStatus;
    int id = 0;
};

struct TEACHER
{
    string firstName;
    string lastName;
    vector<string> teachingTeams;
    int id = 0;
};

struct TEAM
{
    string name;
    string discription;
    string date;
    string students[4];
    string status;
    string teacher;
    int id = 0;
};

/*void printTeams(const vector<TEAM>& teams)
{
    for (int i = 0; i < teams.size(); i++)
    {
        cout << "Name: " << teams[i].name << endl;
        cout << "Task: " << teams[i].discription << endl;
        cout << "Students: " << endl;
        for (int j = 0; j < 4; j++)
        {
            cout << teams[i].students[j] << endl;
        }
    }
}

void printTeams(const vector<TEAM>& teams)
{
    ofstream teamsReport("teamsRepost.txt", ios::in, ios::trunc);
    ifstream teamsName("teamNames.txt", ios::out);
    ifstream teamDescription("teamTasks.txt", ios::out);
    int teamNameIndex;
    int teamDescriptionIndex;
    for (int i = 0; i < teams.size(); i++)
    {
        teamNameIndex = rand() % 30;
        teamDescriptionIndex = rand() % 30;

        teamsReport << "TEAM - ";

        string container;
        for (int i = 0; i < teamNameIndex; i++)
        {
            getline(teamsName, container);
        }
        getline(teamsName, container);
        teamsReport << container + '\n';

        teamsReport << "TASK - ";

        for (int i = 0; i < teamDescriptionIndex; i++)
        {
            getline(teamDescription, container);
        }
        getline(teamDescription, container);

        teamsReport << container + '\n';

        teamsReport << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa: " + '\n';

        for (int j = 0; j < 4; j++)
        {
            teamsReport << teams[i].students[j] + '\n';
        }
    }
    
    teamsReport.close();
    teamsName.close();
    teamDescription.close();
}

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
    cout << "Sorry but no " << wantedRole << " left";
}

void generateTeam(const vector<STUDENT>& students, const int& studentsCount, vector<TEAM>& teams, int& teamCount)
{
    ifstream teamsName("teamNames.txt", ios::out);
    ifstream teamDescription("teamTasks.txt", ios::out);
    int studentIndex;
    teams.push_back(TEAM());
    studentIndex = suffleIndex(students, studentsCount, "BackEnd");
    teams[teamCount].students[0] = students[studentIndex].firstName + " " + students[studentIndex].LastName;
    studentIndex = suffleIndex(students, studentsCount, "FrontEnd");
    teams[teamCount].students[1] = students[studentIndex].firstName + " " + students[studentIndex].LastName;
    studentIndex = suffleIndex(students, studentsCount, "QA");
    teams[teamCount].students[2] = students[studentIndex].firstName + " " + students[studentIndex].LastName;
    studentIndex = suffleIndex(students, studentsCount, "Scrum");
    teams[teamCount].students[3] = students[studentIndex].firstName + " " + students[studentIndex].LastName;

    int teamNameIndex = rand() % 30;
    int teamDescriptionIndex = rand() % 30;

    string container;
    for (int i = 0; i < teamNameIndex; i++)
    {
        getline(teamsName, container);
    }
    getline(teamsName, container);
    teams[teamCount].name = container;

    for (int i = 0; i < teamDescriptionIndex; i++)
    {
        getline(teamDescription, container);
    }
    getline(teamDescription, container);

    teams[teamCount].discription = container;

    teamCount++;
    printTeams(teams);
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
}*/

void addStudent(vector<STUDENT>& students)
{
    cout << "How many students do you want to enter: ";
    int quantity;
    cin >> quantity;
    quantity += students.size();
    for (int i = students.size(); i < quantity; i++)
    {
        students.push_back(STUDENT());
        cin >> students[i].firstName;
        cin >> students[i].lastName;
        cin >> students[i].grade;
        cin >> students[i].role;
        cin >> students[i].email;
        students[i].id = i;
        students[i].teamStatus = "Not occupied";
    }
}

void addTeachers(vector<TEACHER>& teachers)
{
    cout << "How many teachers do you want to enter: ";
    int quantity;
    cin >> quantity;
    quantity += teachers.size();
    for (int i = teachers.size(); i < quantity; i++)
    {
        teachers.push_back(TEACHER());
        cin >> teachers[i].firstName;
        cin >> teachers[i].lastName;
        teachers[i].id = i;
    }
}

int findRole(vector<STUDENT>& students, const string wantedRole)
{
    vector<int> roleId;
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].role == wantedRole and students[i].teamStatus == "Not occupied")
        {
            roleId.push_back(students[i].id);
        }
    }
    for (int i = 0; i < roleId.size(); i++)
    {
        cout << roleId[i] << " ";
    }
    cout << endl;
    if (roleId.size() == 0)
    {
        cerr << "Error" << endl;//not enough students
    }
    else
    {
        int shuffle;
        for (int i = 0; i < roleId.size(); i++)
        {
            shuffle = rand() % roleId.size();
            swap(roleId[0], roleId[shuffle]);
        }
        students[roleId[0]].teamStatus = "Occupied";
        return roleId[0];
    }
}

void generateTeam(vector<STUDENT>& students, vector<TEAM>& teams, vector<TEACHER>& teachers)
{
    ifstream teamsName("Data Files\\teamNames.txt");
    ifstream teamDescription("Data Files\\teamTasks.txt");
    int studentIndex;
    for (int i = 0; i < students.size() / 4; i++)
    {
        teams.push_back(TEAM());
        studentIndex = findRole(students, "BackEnd");
        teams[teams.size() - 1].students[0] = students[studentIndex].firstName + " " + students[studentIndex].lastName;
        studentIndex = findRole(students, "FrontEnd");
        teams[teams.size() - 1].students[1] = students[studentIndex].firstName + " " + students[studentIndex].lastName;
        studentIndex = findRole(students, "QA");
        teams[teams.size() - 1].students[2] = students[studentIndex].firstName + " " + students[studentIndex].lastName;
        studentIndex = findRole(students, "Scrum");
        teams[teams.size() - 1].students[3] = students[studentIndex].firstName + " " + students[studentIndex].lastName;

        int teamNameIndex = rand() % 30;
        int teamDescriptionIndex = rand() % 30;

        string container;
        for (int i = 0; i < teamNameIndex; i++)
        {
            getline(teamsName, container);
        }
        getline(teamsName, container);
        teams[teams.size() - 1].name = container;

        for (int i = 0; i < teamDescriptionIndex; i++)
        {
            getline(teamDescription, container);
        }
        getline(teamDescription, container);

        teams[teams.size() - 1].discription = container;

        int randomIndex = rand() % teachers.size();
        teams[teams.size() - 1].teacher = teachers[randomIndex].firstName + " " + teachers[randomIndex].lastName;
        teams[teams.size() - 1].id = teams.size() - 1;
        teachers[randomIndex].teachingTeams.push_back(teams[teams.size() - 1].name);
    }
}

string makeStudentsReport(const vector<STUDENT>& students)
{
    string report;
    for (int i = 0; i < students.size(); i++)
    {
        report += "First name: " + students[i].firstName + '\n';
        report += "Last name: " + students[i].lastName + '\n';
        report += "Grade: " + to_string(students[i].grade) + '\n';
        report += "Role: " + students[i].role + '\n';
        report += "Email: " + students[i].email + '\n';
        report += "Id: " + to_string(students[i].id) + '\n';
    }

    return report;
}

string makeTeachersReport(const vector<TEACHER>& teachers)
{
    string report;
    for (int i = 0; i < teachers.size(); i++)
    {
        report += "First name: " + teachers[i].firstName + '\n';
        report += "Last name: " + teachers[i].lastName + '\n';
        report += "Teacing teams:" + '\n';
        for (int j = 0; j < teachers[i].teachingTeams.size(); j++)
        {
            report += teachers[i].teachingTeams[j] + '\n';
        }
        report += "Id: " + to_string(teachers[i].id) + '\n';
    }

    return report;
}

string makeTeamsReport(const vector<TEAM>& teams)
{
    string report;
    for (int i = 0; i < teams.size(); i++)
    {
        report += "First name: " + teams[i].name + '\n';
        report += "Description: " + teams[i].discription + '\n';
        report += "Students: " + '\n';
        for (int j = 0; j < 4; j++)
        {
            report += teams[i].students[j] + '\n';
        }
        report += "Teacher: " + teams[i].teacher + '\n';
        report += "Id: " + to_string(teams[i].id) + '\n';
    }

    return report;
}


bool mainMenu(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    cout << "1. Add students" << endl;
    cout << "2. Add teacher" << endl;
    cout << "3. Generate teams" << endl;
    cout << "4. Edit teams, students or teachers" << endl;
    cout << "5. Print teams, students or teachers" << endl;
    cout << "6. Create teams, students or teachers" << endl;
    cout << "7. Save" << endl;
    cout << "8. Open last save" << endl;
    cout << "9. Exit" << endl;
    int option;
    cin >> option;
    switch (option)
    {
        case 1:
            addStudent(students);
            return true;
            break;
        case 2:
            addTeachers(teachers);
            return true;
            break;
        case 3:
            generateTeam(students, teams, teachers);
            return true;
            break;
        case 4:
            return true;
            break;
        case 5:
            return true;
            break;
        case 6:
            return true;
            break;
        case 7:
            return true;
            break;
        case 8:
            return true;
            break;
        case 9:
            return false;
            break;
        default:
            return mainMenu(students, teachers, teams);

    }
}

int main()
{
    srand(time(NULL));
    vector<STUDENT> students;
    vector<TEACHER> teachers;
    vector<TEAM> teams;
    bool exit=false;
    do {
        exit = mainMenu(students, teachers, teams);
    } while (exit);
}

