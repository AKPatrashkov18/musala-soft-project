#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>  
#include <sstream>
#include <chrono> 
#include <ctime> 
#include <conio.h>

using namespace std;

struct STUDENT
{
    string firstName;
    string lastName;
    int grade = 0;
    string role;
    string email;
    string teamStatus;
    size_t id = 0;

    std::string toString()
    {
        string studentSaveFile;
        studentSaveFile += firstName;
        studentSaveFile += ',';
        studentSaveFile += lastName;
        studentSaveFile += ',';
        studentSaveFile += to_string(grade);
        studentSaveFile += ',';
        studentSaveFile += role;
        studentSaveFile += ',';
        studentSaveFile += email;
        studentSaveFile += ',';
        studentSaveFile += teamStatus;
        studentSaveFile += ',';
        studentSaveFile += to_string(id);

        return studentSaveFile;
    }

};

struct TEACHER
{
    string firstName;
    string lastName;
    vector<string> teachingTeams;
    size_t id = 0;
    std::string toString()
    {
        string teacherSaveFile;
        teacherSaveFile += firstName; 
        teacherSaveFile += ','; 
        teacherSaveFile += lastName;
        teacherSaveFile += ',';
        teacherSaveFile += to_string(teachingTeams.size());
        for (int i = 0; i < teachingTeams.size(); i++)
        {
            teacherSaveFile += ',';
            teacherSaveFile += teachingTeams[i];
        }
        teacherSaveFile += ','; 
        teacherSaveFile += to_string(id);
        return teacherSaveFile;
    }
};

struct TEAM
{
    string name;
    string discription;
    string date;
    vector<string> students;
    string teacher;
    size_t id = 0;
    std::string toString()
    {
        string temaSaveFile;
        temaSaveFile += name;
        temaSaveFile += ',';
        temaSaveFile += discription;
        for (int i = 0; i < 4; i++)
        {
            temaSaveFile += ','; 
            temaSaveFile += students[i];
        }
        temaSaveFile += ','; 
        temaSaveFile += teacher; 
        temaSaveFile += ','; 
        temaSaveFile += to_string(id);
        return temaSaveFile;
    }
};

struct SCHOOL 
{
    string name;
    vector<string> studentsName;
    vector<string> teachersName;
};

string checkRole()
{
    string role;
    cin >> role;
    if (role != "BackEnd" and role != "FrontEnd" and role != "QA" and role != "Scrum")
    {
        cerr << "Error! Invalid role!" << endl;
        cout << "Try again: ";
        return checkRole();
    }
    return role;
}

string checkEmail()
{
    string email;
    cin >> email;
    for (int i = 0; i < email.size(); i++)
    {
        if (email[i] == '@')
        {
            return email;
        }
    }
    cerr << "Error there isn't @ symbol" << endl;
    return checkEmail();
}

int inputValidation()
{
    int number;
    cin >> number;
    // input validation
    while (cin.fail())
    {
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input
        cout << "You can only enter numbers: ";
        cin >> number;
    }
    return number;
}

void addStudent(vector<STUDENT>& students, SCHOOL& school)
{
    system("cls");
    cout << "How many students do you want to enter: ";
    size_t quantity;
    quantity = inputValidation();
    quantity += students.size();
    for (size_t i = students.size(); i < quantity; i++)
    {
        system("cls");
        students.push_back(STUDENT());
        cout << "Student " << i <<" data."<<endl;
        cout << "Enter first Name: ";
        cin >> students[i].firstName;
        cout << "Enter last Name: ";
        cin >> students[i].lastName;
        cout << "Enter grade: ";
        students[i].grade = inputValidation();
        cout << "Enter role: ";
        students[i].role = checkRole();
        cout <<"Your email must have @ symbol!"<< endl;
        cout << "Enter email: ";
        students[i].email = checkEmail();
        students[i].id = i;
        students[i].teamStatus = "Not occupied";
        school.studentsName.push_back(students[i].firstName + " " + students[i].lastName);
    }
    system("cls");
}

void addTeachers(vector<TEACHER>& teachers, SCHOOL& school)
{
    system("cls");
    cout << "How many teachers do you want to enter: ";
    size_t quantity;
    quantity = inputValidation();
    quantity += teachers.size();
    for (size_t i = teachers.size(); i < quantity; i++)
    {
        system("cls");
        teachers.push_back(TEACHER());
        cout << "Teacher " << i << " data." << endl;
        cout << "Enter first name: ";
        cin >> teachers[i].firstName;
        cout << "Enter last name: ";
        cin >> teachers[i].lastName;
        teachers[i].id = i;
        school.teachersName.push_back(teachers[i].firstName + " " + teachers[i].lastName);
    }
    system("cls");
}

int findRole(vector<STUDENT>& students, const string wantedRole, const string teamName)
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
        return -1;
    }
    int shuffle;
    for (int i = 0; i < roleId.size(); i++)
    {
        shuffle = rand() % roleId.size();
        swap(roleId[0], roleId[shuffle]);
    }
    students[roleId[0]].teamStatus = teamName;
    return roleId[0];
}

int findNotOccupiedStudents(vector<STUDENT>& students)
{
    int notOccupiedCount = 0;
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].teamStatus == "Not occupied")
        {
            notOccupiedCount++;
        }
    }
    return notOccupiedCount;
}

void generateTeam(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    bool checkIfTeamsIsCreated = false;
    ifstream teamName;
    ifstream teamTask;
    int studentIndex;
    string container;
    teamName.open("Data files\\teamNames.txt", ios::out);
    teamTask.open("Data files\\teamTasks.txt", ios::out);
    int notOccupiedCount = findNotOccupiedStudents(students);
    if (teamName.is_open() and teamTask.is_open())
    {
        for (size_t i = 0; i < notOccupiedCount / 4; i++)
        {
            teams.push_back(TEAM());
            int teamNameIndex = rand() % 29;
            int teamTaskIndex = rand() % 29;
            for (int i = 0; i < teamNameIndex; i++)
            {
                getline(teamName, container);
            }
            teams[teams.size() - 1].name = container;

            for (int i = 0; i < teamTaskIndex; i++)
            {
                getline(teamTask, container);
            }
            teams[teams.size() - 1].discription = container;

            time_t now = time(0);
            container = time(&now);

            teams[teams.size() - 1].date = container;

            studentIndex = findRole(students, "BackEnd", teams[teams.size() - 1].name);
            if (studentIndex == -1)
            {
                teams.erase(teams.end() - 1);
                cerr << "Error! Not enough students or too many students have the same role! There are " << teams.size() << "created teams. Wherethere could be " << notOccupiedCount / 4 << endl;
                return;
            }
            teams[teams.size() - 1].students.push_back(students[studentIndex].firstName + " " + students[studentIndex].lastName);
            studentIndex = findRole(students, "FrontEnd", teams[teams.size() - 1].name);
            if (studentIndex == -1)
            {
                teams.erase(teams.end() - 1);
                cerr << "Error! Not enough students or too many students have the same role! There are " << teams.size() << " created teams. Where there could be " << notOccupiedCount / 4 << endl;
                return;
            }
            teams[teams.size() - 1].students.push_back(students[studentIndex].firstName + " " + students[studentIndex].lastName);
            studentIndex = findRole(students, "QA", teams[teams.size() - 1].name);
            if (studentIndex == -1)
            {
                teams.erase(teams.end() - 1);
                cerr << "Error! Not enough students or too many students have the same role! There are " << teams.size() << " created teams. Where there could be " << notOccupiedCount / 4 << endl;
                return;
            }
            teams[teams.size() - 1].students.push_back(students[studentIndex].firstName + " " + students[studentIndex].lastName);
            studentIndex = findRole(students, "Scrum", teams[teams.size() - 1].name);
            if (studentIndex == -1)
            {
                teams.erase(teams.end() - 1);
                cerr << "Error! Not enough students or too many students have the same role! There are " << teams.size() << " created teams. Where there could be " << notOccupiedCount / 4 << endl;
                return;
            }
            teams[teams.size() - 1].students.push_back(students[studentIndex].firstName + " " + students[studentIndex].lastName);

            if (teachers.size() == 0)
            {
                cerr << "Error! Not enought teachers" << endl;
                return;
            }

            int randomIndex = rand() % teachers.size();
            teams[teams.size() - 1].teacher = teachers[randomIndex].firstName + " " + teachers[randomIndex].lastName;
            teams[teams.size() - 1].id = teams.size() - 1;
            teachers[randomIndex].teachingTeams.push_back(teams[teams.size() - 1].name);

            teamName.clear();
            teamName.seekg(0, ios::beg);

            teamTask.clear();
            teamTask.seekg(0, ios::beg);
            checkIfTeamsIsCreated = true;
        }
        if (!checkIfTeamsIsCreated)
        {
            cerr << "Error! Not enought students" << endl;
        }
    }
    else
    {
        cerr << "Error! Can't open teamNames or teamTasks text files! "<<endl;
    }
}

string makeStudentsReport(const vector<STUDENT>& students, int wantedIndex)
{
    string report;
    report += "First name: ";
    report += students[wantedIndex].firstName;
    report += '\n';
    report += "Last name: ";
    report += students[wantedIndex].lastName;
    report += '\n';
    report += "Grade: "; 
    report += to_string(students[wantedIndex].grade);
    report += '\n';
    report += "Role: "; 
    report += students[wantedIndex].role;
    report += '\n';
    report += "Email: ";
    report += students[wantedIndex].email;
    report += '\n';
    report += "Team: ";
    report += students[wantedIndex].teamStatus;
    report += '\n';
    report += "Id: "; 
    report += to_string(students[wantedIndex].id);
    report += '\n';

    return report;
}

string makeTeachersReport(const vector<TEACHER>& teachers, int wantedIndex)
{
    string report;
    report += "First name: ";
    report += teachers[wantedIndex].firstName;
    report += '\n';
    report += "Last name: ";
    report += teachers[wantedIndex].lastName;
    report += '\n';
    report += "Teaching teams: ";
    report += "\n";
    for (int j = 0; j < teachers[wantedIndex].teachingTeams.size(); j++)
    {
        report += teachers[wantedIndex].teachingTeams[j];
        report += '\n';
    }
    report += "Id: ";
    report += to_string(teachers[wantedIndex].id);
    report += '\n';
    return report;
}

string makeTeamsReport(const vector<TEAM>& teams, int wantedIndex)
{
    string report;
    report += "First name: "; 
    report += teams[wantedIndex].name;
    report += '\n';
    report += "Description: ";
    report += teams[wantedIndex].discription;
    report += '\n';
    report += "Students: ";
    report += '\n';
    for (int j = 0; j < teams[wantedIndex].students.size(); j++)
    {
        report += teams[wantedIndex].students[j];
        report += '\n';
    }
    report += "Teacher: ";
    report += teams[wantedIndex].teacher;
    report += '\n';
    report += "Id: ";
    report += to_string(teams[wantedIndex].id);
    report += '\n';

    return report;
}

string makeSchoolReport(const SCHOOL& school)
{
    string report;
    report += "School name: ";
    report += school.name;
    report += '\n';
    report += "Students: ";
    report += '\n';
    for (int i = 0; i < school.studentsName.size(); i++)
    {
        report += school.studentsName[i];
        report += '\n';
    }
    report += "Teachers: ";
    report += '\n';
    for (int i = 0; i < school.teachersName.size(); i++)
    {
        report += school.teachersName[i];
        report += '\n';
    }

    return report;
}

void printMenu(const vector<STUDENT>& students, const vector<TEACHER>& teachers, const vector<TEAM>& teams, const SCHOOL& school)
{
    system("cls");
    cout << "|-----------------------------------------------------------|" << endl;
    cout << "|                    1. Print students                      |" << endl;
    cout << "|                    2. Print teachers                      |" << endl;
    cout << "|                    3. Print teams                         |" << endl;
    cout << "|                    4. Print school                        |" << endl;
    cout << "|                    0. Exit                                |" << endl;
    cout << "|-----------------------------------------------------------|" << endl;
    cout << "Enter your option: ";
    switch (inputValidation())
    {
        system("cls");
        case 1:
            for (int i = 0; i < students.size(); i++)
            {
                cout << makeStudentsReport(students, i);
            }
            break;
        case 2:
            for (int i = 0; i < teachers.size(); i++)
            {
                cout << makeTeachersReport(teachers, i);
            }
            break;
        case 3:
            for (int i = 0; i < teams.size(); i++)
            {
                cout << makeTeamsReport(teams, i);
            }
            break;
        case 4:
            cout << makeSchoolReport(school);
            break;
        case 0:
            return;
            break;
        default:
            break;
    }
}



void reportsMenu(const vector<STUDENT>& students, const vector<TEACHER>& teachers, const vector<TEAM>& teams, const SCHOOL& school)
{
    system("cls");
    ofstream reports;
    cout << "|-----------------------------------------------------|"<<endl;
    cout << "|              1. Create students reports             |" << endl;
    cout << "|              2. Create teachers report              |" << endl;
    cout << "|              3. Create teams report                 |" << endl;
    cout << "|              4. Create school report                |" << endl;
    cout << "|              0. Exit                                |" << endl;
    cout << "|-----------------------------------------------------|"<<endl;
    cout << "Enter your option: ";
    switch (inputValidation())
    {
    case 1:
        reports.open("Reports\\studentsReport.txt", ios::in | ios::trunc);
        if (reports.is_open())
        {
            for (int i = 0; i < students.size(); i++)
            {
                reports << makeStudentsReport(students, i);
            }
            
            reports.close();
            cout << "Congratulations! Your students report has been saved! "<<endl;
        }
        else {
            cerr << "Error! Can't open studentsReport text file! "<<endl;
        }
        break;
    case 2:
        reports.open("Reports\\teachersReport.txt", ios::in | ios::trunc);
        if (reports.is_open())
        {
            for (int i = 0; i < teachers.size(); i++)
            {
                reports << makeTeachersReport(teachers, i);
            }  
            reports.close();
            cout << "Congratulations! Your teachers report has been saved! "<<endl;
        }
        else {
            cerr << "Error! Can't open teachersReport text file! "<<endl;
        }
        break;
    case 3:
        reports.open("Reports\\teamsReport.txt", ios::in | ios::trunc);
        if (reports.is_open())
        {
            for (int i = 0; i < teams.size(); i++)
            {
                reports << makeTeamsReport(teams,i);
            }
            reports.close();
            cout << "Congratulations! Your teams report has been saved! "<<endl;
        }
        else {
            cerr << "Error! Can't open teamsReport text file! "<<endl;
        }
        break;
    case 4:
        reports.open("Reports\\schoolReport.txt", ios::in | ios::trunc);
        if (reports.is_open())
        {
            reports << makeSchoolReport(school);
            reports.close();
            cout << "Congratulations! Your school report has been saved! " << endl;
        }
        else {
            cerr << "Error! Can't open schoolReport text file! "<<endl;
        }
        break;
    case 0:
        return;
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
        cerr << "Error! Can't open studentsSaveFile text file! "<<endl;
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
        cerr << " Error! Can't open teachersSaveFile text file! "<<endl;
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
        cerr << "Error! Can't open teamsSaveFile text file! "<<endl;
    }
    cout << "Congratulations! Your data has been saved! "<<endl;
}

int stringConvertor(string& text)
{
    stringstream convertor(text);
    int number;
    convertor >> number;
    return number;
}

void openSave(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams, SCHOOL& school)
{
    ifstream studentsSaveFile;
    ifstream teachersSaveFile;
    ifstream teamsSaveFile;
    string container;
    students.clear();
    teachers.clear();
    teams.clear();
    school.studentsName.clear();
    school.teachersName.clear();

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
            school.studentsName.push_back(students[students.size() - 1].firstName + " " + students[students.size() - 1].lastName);
        }
        students.erase(students.end() - 1);
        studentsSaveFile.close();
    }
    else
    {
        cerr << "Error! Can't open studentsSaveFile text file! "<<endl;
    }

    teachersSaveFile.open("Save files\\teachersSaveFile.txt", ios::out);
    if (teachersSaveFile.is_open())
    {
        while (!teachersSaveFile.eof())
        {
            teachers.push_back(TEACHER());
            getline(teachersSaveFile, container, ',');
            teachers[teachers.size() - 1].firstName = container;
            getline(teachersSaveFile, container, ',');
            teachers[teachers.size() - 1].lastName = container;
            getline(teachersSaveFile, container, ',');
            int teamsNumber = stringConvertor(container);
            for (int i = 0; i < teamsNumber; i++)
            {
                getline(teachersSaveFile, container, ',');
                teachers[teachers.size() - 1].teachingTeams.push_back(container);
            }
            getline(teachersSaveFile, container, '\n');
            teachers[teachers.size() - 1].id = stringConvertor(container);
            school.teachersName.push_back(teachers[teachers.size() - 1].firstName + " " + teachers[teachers.size() - 1].lastName);
        }
        teachers.erase(teachers.end() - 1);
        teachersSaveFile.close();
    }
    else
    {
        cerr << "Error! Can't open teachersSaveFile text file! "<<endl;
    }

    teamsSaveFile.open("Save files\\teamsSaveFile.txt", ios::out);
    if (teamsSaveFile.is_open())
    {
        while (!teamsSaveFile.eof())
        {
            teams.push_back(TEAM());
            getline(teamsSaveFile, container, ',');
            teams[teams.size() - 1].name = container;
            getline(teamsSaveFile, container, ',');
            teams[teams.size() - 1].discription = container;
            for (int i = 0; i < 4; i++)
            {
                getline(teamsSaveFile, container, ',');
                teams[teams.size() - 1].students.push_back(container);
            }
            getline(teamsSaveFile, container, ',');
            teams[teams.size() - 1].teacher = container;
            getline(teamsSaveFile, container, '\n');
            teams[teams.size() - 1].id = stringConvertor(container);
        }
        teams.erase(teams.end() - 1);
        teamsSaveFile.close();
    }
    else
    {
        cerr << "Error! Can't open teamsSaveFile text file! "<<endl;
    }
    cout << "Congratulations! Your data has been opened! "<<endl;
}

bool checkId(const vector<TEAM>& teams, const int wantedId)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (wantedId == teams[i].id)
        {
            return true;
        }
    }
    return false;
}

int findTeamId(const vector<TEAM>& teams, const int wantedId)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (wantedId == teams[i].id)
        {
            return i;
        }
    }
    return 0;
}

int findStudentId(const vector<STUDENT>& students, const int wantedId)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (wantedId == students[i].id)
        {
            return i;
        }
    }
    return 0;
}

int findTeacherId(const vector<TEACHER>& teachers, const int wantedId)
{
    for (int i = 0; i < teachers.size(); i++)
    {
        if (wantedId == teachers[i].id)
        {
            return i;
        }
    }
    return 0;
}

void archiveTeam(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams, bool removedPersonOrEditedPerson = false, int indexOfremovedPersonOrEditedPerson = 0)
{
    int index;
    if (removedPersonOrEditedPerson)
    {
        index = indexOfremovedPersonOrEditedPerson;
    }
    else
    {
        for (int i = 0; i < teams.size(); i++)
        {
            cout << makeTeamsReport(teams, i);
        }
        cout << "Choose index: ";
        index = inputValidation();
    }
    if (!checkId(teams, index))
    {
        cerr << "Error! Please enter valid id! "<<endl;
    }
    else {
        ofstream archaivedTeams;
        archaivedTeams.open("Archived files\\archaivedTeams.txt", ios::in | ios::ate);
        if (archaivedTeams.is_open())
        {
            archaivedTeams << makeTeamsReport(teams, findTeamId(teams, index));
            archaivedTeams.close();
        }
        for (int i = 0; i < teachers.size(); i++)
        {
            for (int j = 0; j < teachers[i].teachingTeams.size(); j++)
            {
                if (teachers[i].teachingTeams[j] == teams[findTeamId(teams, index)].name)
                {
                    teachers[i].teachingTeams.erase(teachers[i].teachingTeams.begin() + j);
                    break;
                }
            }
        }
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].teamStatus == teams[findTeamId(teams, index)].name)
            {
                students[i].teamStatus = "Not occupied";
            }
        }
        teams.erase(teams.begin() + findTeamId(teams, index));
    }
}

void deleteStudent(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    system("cls");
    for (int i = 0; i < students.size(); i++)
    {
        cout << makeStudentsReport(students, i);
    }
    cout << "Enter an index of a student you want to delete: ";
    int deleteIndex = findStudentId(students, inputValidation());

    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].name == students[deleteIndex].teamStatus)
        {
            archiveTeam(students, teachers, teams, true, findStudentId(students,i));
            break;
        }
    }
    students.erase(students.begin() + deleteIndex); 
    system("cls");
}

void deleteTeacher(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    for (int i = 0; i < teachers.size(); i++)
    {
        cout << makeTeachersReport(teachers, i);
    }
    cout << "Enter an index of a teacher you want to delete: ";
    int deleteIndex = findTeacherId(teachers, inputValidation());

    if (teachers.size() == 1)
    {
        students.clear();
        teachers.clear();
        teams.clear();
    }
    else
    {
        for (int i = 0; i < teams.size(); i++)
        {
            for (int j = 0; j < teachers[deleteIndex].teachingTeams.size(); j++)
            {
                if (teams[i].name == teachers[deleteIndex].teachingTeams[j])
                {
                    int randomIndex = rand() % teachers.size();
                    teams[i].teacher = teachers[randomIndex].firstName + " " + teachers[randomIndex].lastName;
                    teachers[randomIndex].teachingTeams.push_back(teams[i].name);
                }
            }
        }
        teachers.erase(teachers.begin() + deleteIndex);
    }

}

void tutorial()
{
    system("cls");
    string container;
    ifstream tutorial;
    tutorial.open("Data files\\tutorial.txt", ios::out);
    if (tutorial.is_open())
    {
        while (!tutorial.eof())
        {
            getline(tutorial, container);
            cout << container << endl;
        }
    }
    else
    {
        cerr << "Error! Can't open tutorial text file!" << endl;
    }
}

void editStudent(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    system("cls");
    for (int i = 0; i < students.size(); i++)
    {
        cout << makeStudentsReport(students, i);
    }
    cout << "Choose index: ";
    string container;
    int editIndex;
    cin >> editIndex;
    system("cls");

    cout << "|------------------------------------------------------------------|" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                         1. First name                            |" << endl;
    cout << "|                         2. Last name                             |" << endl;
    cout << "|                         3. Grade                                 |" << endl;
    cout << "|                         4. Role                                  |" << endl;
    cout << "|                         5. Email                                 |" << endl;
    cout << "|                         0. Exit                                  |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|------------------------------------------------------------------|" << endl;
    cout << "Enter your option: ";

    switch (inputValidation())
    {
    case 1:
        cin >> container;
        for (int i = 0; i < teams.size(); i++)
        {
            for (int j = 0; j < teams[i].students.size(); j++)
            {
                if (students[findStudentId(students, editIndex)].firstName + " " + students[findStudentId(students, editIndex)].lastName == teams[i].students[j])
                {
                    teams[i].students[j] = container + " " + students[findStudentId(students, editIndex)].lastName;
                    students[findStudentId(students, editIndex)].firstName = container;
                    break;
                }
            }

        }
        break;
    case 2:
        cin >> container;
        for (int i = 0; i < teams.size(); i++)
        {
            for (int j = 0; j < teams[i].students.size(); j++)
            {
                if (students[findStudentId(students, editIndex)].firstName + " " + students[findStudentId(students, editIndex)].lastName == teams[i].students[j])
                {
                    teams[i].students[j] = students[findStudentId(students, editIndex)].firstName + " " + container;
                    students[findStudentId(students, editIndex)].lastName = container;
                    break;
                }
            }

        }
        break;
    case 3:
        students[findStudentId(students, editIndex)].grade = inputValidation();
        break;
    case 4:
        students[findStudentId(students, editIndex)].role = checkRole();
        break;
    case 5:
        students[findStudentId(students, editIndex)].email = checkEmail();
        break;
    case 0:
        return;
        break;
    default:
        cerr << "Error! Invalid option! Try again." << endl;
        editStudent(students, teachers, teams);
        break;
    }

}

void editTeacher(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    system("cls");
    for (int i = 0; i < teachers.size(); i++)
    {
        cout << makeTeachersReport(teachers, i);
    }
    cout << "Choose index: ";
    string container;
    int editIndex;
    cin >> editIndex;
    system("cls");

    cout << "|------------------------------------------------------------------|" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                         1. First name                            |" << endl;
    cout << "|                         2. Last name                             |" << endl;
    cout << "|                         0. Exit                                  |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|------------------------------------------------------------------|" << endl;
    cout << "Enter your option: ";

    switch (inputValidation())
    {
    case 1:
        cin >> container;
        for (int i = 0; i < teams.size(); i++)
        {
            if (teams[i].teacher == teachers[findTeacherId(teachers, editIndex)].firstName + " " + teachers[findTeacherId(teachers, editIndex)].lastName)
            {
                teams[i].teacher = container + " " + teachers[findTeacherId(teachers, editIndex)].lastName;
            }
        }
        teachers[findTeacherId(teachers, editIndex)].firstName = container;
        break;
    case 2:
        cin >> container;
        for (int i = 0; i < teams.size(); i++)
        {
            if (teams[i].teacher == teachers[findTeacherId(teachers, editIndex)].firstName + " " + teachers[findTeacherId(teachers, editIndex)].lastName)
            {
                teams[i].teacher = teachers[findTeacherId(teachers, editIndex)].firstName + " " + container;
            }
        }
        teachers[findTeacherId(teachers, editIndex)].lastName = container;
        break;
    case 0:
        return;
        break;
    default:
        editTeacher(students, teachers, teams);
        break;
    }
}

void editMenu(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    system("cls");
    cout << "|------------------------------------------------------------------|" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                         1. Edit student                          |" << endl;
    cout << "|                         2. Edit teacher                          |" << endl;
    cout << "|                         0. Exit                                  |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|------------------------------------------------------------------|" << endl;
    cout << "Enter your option: ";
    switch (inputValidation())
    {
    case 1:
        editStudent(students, teachers, teams);
        break;
    case 2:
        editTeacher(students, teachers, teams);
        break;
    case 0:
        return;
        break;
    default:
        editMenu(students, teachers, teams);
        break;
    }
}

bool mainMenu(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams, SCHOOL& school)
{
    cout << "|------------------------------------------------------------------|"<<endl;
    cout << "|       .: WELCOME TO OUR PROGRAM! CHOOSE YOUR OPTION: :.          |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                   1. Add students                                |" << endl;
    cout << "|                   2. Add teacher                                 |" << endl;
    cout << "|                   3. Generate teams                              |" << endl;
    cout << "|                   4. Print menu                                  |" << endl;
    cout << "|                   5. Create reports menu                         |" << endl;
    cout << "|                   6. Edit menu                                   |" << endl;
    cout << "|                   7. Delete student                              |" << endl;
    cout << "|                   8. Delete teacher                              |" << endl;
    cout << "|                   9. Archive team                                |" << endl;
    cout << "|                   10. Save                                       |" << endl;
    cout << "|                   11. Open last save                             |" << endl;
    cout << "|                   12. Tutorial                                   |" << endl;
    cout << "|                   0. Exit                                        |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|------------------------------------------------------------------|" << endl;
    cout << "Enter your option: ";

    switch (inputValidation())
    {
        case 1:
            addStudent(students, school);
            return true;
            break;
        case 2:
            addTeachers(teachers, school);
            return true;
            break;
        case 3:
            generateTeam(students, teachers, teams);
            return true;
            break;
        case 4:
            printMenu(students, teachers, teams, school);
            return true;
            break;
        case 5:
            reportsMenu(students, teachers, teams, school);
            return true;
            break;
        case 6:
            editMenu(students, teachers, teams);
            return true;
            break;
        case 7:
            deleteStudent(students, teachers, teams);
            return true;
            break;
        case 8:
            deleteTeacher(students, teachers, teams);
            return true;
            break;
        case 9:
            archiveTeam(students, teachers, teams);
            return true;
        case 10:
            saveFiles(students, teachers, teams);
            return true;
        case 11:
            openSave(students, teachers, teams, school);
            return true;
        case 12:
            tutorial();
            return true;
        case 0:
            return false;
            break;
        default:
            cerr << "Error! Invalid option!" << endl; 
            return mainMenu(students, teachers, teams, school);

    }
}

int main()
{
    srand(time(NULL));
    vector<STUDENT> students;
    vector<TEACHER> teachers;
    vector<TEAM> teams;
    SCHOOL school;
    cout << "Please enter the name of your organisation: ";
    cin >> school.name;
    bool exit=false;
    do {
        exit = mainMenu(students, teachers, teams, school);
    } while (exit);
}

