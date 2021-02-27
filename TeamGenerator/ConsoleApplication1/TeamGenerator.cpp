#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>  
#include <sstream>

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

    std::string toString()
    {
        return firstName + ',' + lastName + ',' + to_string(grade) + ',' + role + ',' + email + ',' + teamStatus + ',' + to_string(id);
    }
};

struct TEACHER
{
    string firstName;
    string lastName;
    vector<string> teachingTeams;
    int id = 0;
    std::string toString()
    {
        string teacherSaveFile;
        teacherSaveFile += firstName + ',' + lastName + ',' + to_string(teachingTeams.size());
        for (int i = 0; i < teachingTeams.size(); i++)
        {
            teacherSaveFile += ',' + teachingTeams[i];
        }
        teacherSaveFile += ',' + to_string(id);
        return teacherSaveFile;
    }
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
    std::string toString()
    {
        string teacherSaveFile;
        teacherSaveFile += name + ',' + discription;
        for (int i = 0; i < 4; i++)
        {
            teacherSaveFile += ',' + students[i];
        }
        teacherSaveFile += status + ',' + teacher + ',' + to_string(id);
        return teacherSaveFile;
    }
};

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
    if (roleId.size() == 0)
    {
        cerr << "Error" << endl;
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
        report += "First name: ";
        report += students[i].firstName;
        report += '\n';
        report += "Last name: ";
        report += students[i].lastName;
        report += '\n';
        report += "Grade: "; 
        report += to_string(students[i].grade); 
        report += '\n';
        report += "Role: "; 
        report += students[i].role; 
        report += '\n';
        report += "Email: ";
        report += students[i].email;
        report += '\n';
        report += "Id: "; 
        report += to_string(students[i].id);
        report += '\n';
    }

    return report;
}

string makeTeachersReport(const vector<TEACHER>& teachers)
{
    string report;
    for (int i = 0; i < teachers.size(); i++)
    {
        report += "First name: ";
        report += teachers[i].firstName;
        report += '\n';
        report += "Last name: ";
        report += teachers[i].lastName;
        report += '\n';
        report += "Teaching teams: ";
        report += "\n";
        for (int j = 0; j < teachers[i].teachingTeams.size(); j++)
        {
            report += teachers[i].teachingTeams[j];
            report += '\n';
        }
        report += "Id: ";
        report += to_string(teachers[i].id);
        report += '\n';
    }

    return report;
}

string makeTeamsReport(const vector<TEAM>& teams)
{
    string report;
    for (int i = 0; i < teams.size(); i++)
    {
        report += "First name: "; 
        report += teams[i].name;
        report += '\n';
        report += "Description: ";
        report += teams[i].discription;
        report += '\n';
        report += "Students: ";
        report += '\n';
        for (int j = 0; j < 4; j++)
        {
            report += teams[i].students[j];
            report += '\n';
        }
        report += "Teacher: ";
        report += teams[i].teacher;
        report += '\n';
        report += "Id: ";
        report += to_string(teams[i].id);
        report += '\n';
    }

    return report;
}

void printMenu(const vector<STUDENT>& students, const vector<TEACHER>& teachers, const vector<TEAM>& teams)
{
    cout << "1. Print students" << endl;
    cout << "2. Print teams" << endl;
    cout << "3. Print teachers" << endl;
    int option;
    cin >> option;
    switch (option)
    {
        case 1:
            cout << makeStudentsReport(students);
            break;
        case 2:
            cout << makeTeamsReport(teams);
            break;
        case 3:
            cout << makeTeachersReport(teachers);
            break;
        default:
            break;
    }
}

void reportsMenu(const vector<STUDENT>& students, const vector<TEACHER>& teachers, const vector<TEAM>& teams)
{
    ofstream reports;
    cout << "1. Create students reports" << endl;
    cout << "2. Create teachers report" << endl;
    cout << "3. Create teams report" << endl;
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
        reports.open("Reports\\studentsReport.txt", ios::in | ios::trunc);
        if (reports.is_open())
        {
            reports << makeStudentsReport(students);
            reports.close();
        }
        else {
            cerr << "Error";
        }
        break;
    case 2:
        reports.open("Reports\\teachersReport.txt", ios::in | ios::trunc);
        if (reports.is_open())
        {
            reports << makeTeachersReport(teachers);
            reports.close();
        }
        else {
            cerr << "Error";
        }
        break;
    case 3:
        reports.open("Reports\\teamsReport.txt", ios::in | ios::trunc);
        if (reports.is_open())
        {
            reports << makeTeamsReport(teams);
            reports.close();
        }
        else {
            cerr << "Error";
        }
        break;
    default:
        break;
    }
}

void saveFiles(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    ofstream studentsSaveFile;
    ofstream teachersSaveFile;
    ofstream teamsSaveFile;

    studentsSaveFile.open("Save files\\studentsSaveFile.txt", ios::in | ios::trunc);
    if (studentsSaveFile.is_open())
    {
        for (int i = 0; i < students.size(); i++)
        {
            studentsSaveFile << students[i].toString() << endl;
        }
        studentsSaveFile.close();
    }
    else
    {
        cerr << "Error";
    }

    teachersSaveFile.open("Save files\\teachersSaveFile.txt", ios::in | ios::trunc);
    if (teachersSaveFile.is_open())
    {
        for (int i = 0; i < teachers.size(); i++)
        {
            teachersSaveFile << teachers[i].toString() << endl;
        }
        teachersSaveFile.close();
    }
    else
    {
        cerr << "Error";
    }

    teamsSaveFile.open("Save files\\teamsSaveFile.txt", ios::in | ios::trunc);
    if (teamsSaveFile.is_open())
    {
        for (int i = 0; i < teams.size(); i++)
        {
            teamsSaveFile << teams[i].toString() << endl;
        }
        teamsSaveFile.close();
    }
    else
    {
        cerr << "Error";
    }
}

int stringConvertor(string& text)
{
    stringstream convertor(text);
    int number;
    convertor >> number;
    return number;
}

void openSave(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    ifstream studentsSaveFile;
    ifstream teachersSaveFile;
    ifstream teamsSaveFile;
    string container;

    studentsSaveFile.open("Save files\\studentsSaveFile.txt", ios::out);
    if (studentsSaveFile.is_open())
    {
        while (!studentsSaveFile.eof())
        {
            students.push_back(STUDENT());
            getline(studentsSaveFile, container, ',');
            students[students.size() - 1].firstName = container;
            getline(studentsSaveFile, container, ',');
            students[students.size() - 1].lastName = container;
            getline(studentsSaveFile, container, ',');
            students[students.size() - 1].grade = stringConvertor(container);
            getline(studentsSaveFile, container, ',');
            students[students.size() - 1].role = container;
            getline(studentsSaveFile, container, ',');
            students[students.size() - 1].email = container;
            getline(studentsSaveFile, container, ',');
            students[students.size() - 1].teamStatus = container;
            getline(studentsSaveFile, container, '\n');
            students[students.size() - 1].id = stringConvertor(container);
        }
        students.erase(students.end() - 1);
    }
    else
    {
        cerr << "Error";
    }

    teachersSaveFile.open("Save files\\teachersSaveFile.txt", ios::out);
    if (teachersSaveFile.is_open())
    {
        while (!teachersSaveFile.eof())
        {
            teachers.push_back(TEACHER());
            getline(teachersSaveFile, container, ',');
            teachers[teachers.size() - 1].lastName = container;
            getline(teachersSaveFile, container, ',');
            teachers[teachers.size() - 1].lastName = container;
            for (int i = 0; i < stringConvertor(container); i++)
            {
                getline(teachersSaveFile, container, ',');
                teachers[teachers.size() - 1].teachingTeams.push_back(container);
            }
            getline(teachersSaveFile, container, '\n');
            teachers[teachers.size() - 1].id = stringConvertor(container);
        }
        teachers.erase(teachers.end() - 1);
    }
    else
    {
        cerr << "Error";
    }
}

bool mainMenu(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    cout << "1. Add students" << endl;
    cout << "2. Add teacher" << endl;
    cout << "3. Generate teams" << endl;
    cout << "4. Print teams, students or teachers" << endl;
    cout << "5. Create teams, students or teachers reposrts" << endl;
    cout << "6. Edit student, teacher or a team" << endl;
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
            printMenu(students, teachers, teams);
            return true;
            break;
        case 5:
            reportsMenu(students, teachers, teams);
            return true;
            break;
        case 6:
            return true;
            break;
        case 7:
            saveFiles(students, teachers, teams);
            return true;
            break;
        case 8:
            openSave(students, teachers, teams);
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

