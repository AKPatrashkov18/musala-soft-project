#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>  
#include <sstream>
#include <ctime> 
#include <conio.h>
#include "Structures.h"
#include "PresentationLayer.h"

using namespace std;

// checks if the role is valid
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

// checks if the email is valid
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

// checks if the input is correct
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
        cout << "Student " << i << " data." << endl;
        cout << "Enter first Name: ";
        cin >> students[i].firstName;
        cout << "Enter last Name: ";
        cin >> students[i].lastName;
        cout << "Enter grade: ";
        students[i].grade = inputValidation();
        cout << "Enter role: ";
        students[i].role = checkRole();
        cout << "Your email must have @ symbol!" << endl;
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

// selects a random student with a certain role
int findRole(vector<STUDENT>& students, const string wantedRole, const string teamName)
{
    vector<int> roleId;
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].role == wantedRole and students[i].teamStatus == "Not occupied")
        {
            // finds what are the student Ids that compile a certain role
            roleId.push_back(students[i].id);
        }
    }
    // checks if there are no suitable students
    if (roleId.size() == 0)
    {
        return -1;
    }
    int shuffle;
    // shuffles the students
    for (int i = 0; i < roleId.size(); i++)
    {
        shuffle = rand() % roleId.size();
        swap(roleId[0], roleId[shuffle]);
    }
    students[roleId[0]].teamStatus = teamName;
    return roleId[0];
}

// finds how many students don't have a team
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
            int teamNameIndex = rand() % 28 + 1;
            int teamTaskIndex = rand() % 28 + 1;
            // skips the lines in teamnames file
            for (int i = 0; i < teamNameIndex; i++)
            {
                getline(teamName, container);
            }
            teams[teams.size() - 1].name = container;

            // skip lines in the teamtasks file
            for (int i = 0; i < teamTaskIndex; i++)
            {
                getline(teamTask, container);
            }
            teams[teams.size() - 1].discription = container;
            // get the current time
            time_t now = time(0);
            container = time(&now);

            teams[teams.size() - 1].date = container;

            // getting the Id of the student that is suitable for the role
            studentIndex = findRole(students, "BackEnd", teams[teams.size() - 1].name);
            // checks if there are no suitable students
            if (studentIndex == -1)
            {
                // erases the last element
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

            // choosing a random teacher
            int randomIndex = rand() % teachers.size();
            teams[teams.size() - 1].teacher = teachers[randomIndex].firstName + " " + teachers[randomIndex].lastName;
            teams[teams.size() - 1].id = teams.size() - 1;
            teachers[randomIndex].teachingTeams.push_back(teams[teams.size() - 1].name);

            // goes to the beginning of the files
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
        cerr << "Error! Can't open teamNames or teamTasks text files! " << endl;
    }
}

void saveFiles(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    ofstream studentsSaveFile;
    ofstream teachersSaveFile;
    ofstream teamsSaveFile;

    // Opens the file and delets its content
    studentsSaveFile.open("Save files\\studentsSaveFile.txt", ios::in | ios::trunc);
    // checks if the file is open
    if (studentsSaveFile.is_open())
    {
        for (int i = 0; i < students.size(); i++)
        {
            // inputs the saved data into the file
            studentsSaveFile << students[i].toString() << endl;
        }
        // closing the file
        studentsSaveFile.close();
    }
    else
    {
        cerr << "Error! Can't open studentsSaveFile text file! " << endl;
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
        cerr << " Error! Can't open teachersSaveFile text file! " << endl;
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
        cerr << "Error! Can't open teamsSaveFile text file! " << endl;
    }
    cout << "Congratulations! Your data has been saved! " << endl;
}

// converts string to an int
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
    // clears all current data
    students.clear();
    teachers.clear();
    teams.clear();
    school.studentsName.clear();
    school.teachersName.clear();

    // opens the save file
    studentsSaveFile.open("Save files\\studentsSaveFile.txt", ios::out);
    // checks if the file is open
    if (studentsSaveFile.is_open())
    {
        // extract data from the file until the file is empty
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
        // erases the last element
        students.erase(students.end() - 1);
        // closes the file
        studentsSaveFile.close();
    }
    else
    {
        cerr << "Error! Can't open studentsSaveFile text file! " << endl;
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
        cerr << "Error! Can't open teachersSaveFile text file! " << endl;
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
        cerr << "Error! Can't open teamsSaveFile text file! " << endl;
    }
    cout << "Congratulations! Your data has been opened! " << endl;
}

// checks if the wanted Id exists 
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

// finds the wanted Id
int findTeamIndex(const vector<TEAM>& teams, const int wantedId)
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

// finds the wanted Id
int findStudentIndex(const vector<STUDENT>& students, const int wantedId)
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

// finds the wanted Id
int findTeacherIndex(const vector<TEACHER>& teachers, const int wantedId)
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

void archiveTeam(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams, bool removedOrEditedPerson = false, int removedOrEditedPersonIndex = 0)
{
    // checks if the vector is empty
    if (teams.size() == 0)
    {
        cerr << "Error! There are no teams" << endl;
        return;
    }
    int index;
    if (removedOrEditedPerson)
    {
        index = removedOrEditedPersonIndex;
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
    // checks if the wanted Id exists
    if (!checkId(teams, index))
    {
        cerr << "Error! Please enter valid id! " << endl;
    }
    else {
        ofstream archaivedTeams;
        // opens the file at the end
        archaivedTeams.open("Archived files\\archaivedTeams.txt", ios::in | ios::ate);
        // checks if the file is open
        if (archaivedTeams.is_open())
        {
            archaivedTeams << makeTeamsReport(teams, findTeamIndex(teams, index));
            archaivedTeams.close();
        }
        for (int i = 0; i < teachers.size(); i++)
        {
            for (int j = 0; j < teachers[i].teachingTeams.size(); j++)
            {
                // if teachers teaching teams are equal with teamname, erase the teaching teams from the teacher
                if (teachers[i].teachingTeams[j] == teams[findTeamIndex(teams, index)].name)
                {
                    teachers[i].teachingTeams.erase(teachers[i].teachingTeams.begin() + j);
                    break;
                }
            }
        }
        for (int i = 0; i < students.size(); i++)
        {
            // if the students teamstatus is equal to the teamname, removes the student from the team
            if (students[i].teamStatus == teams[findTeamIndex(teams, index)].name)
            {
                students[i].teamStatus = "Not occupied";
            }
        }
        teams.erase(teams.begin() + findTeamIndex(teams, index));
    }
}

void deleteStudent(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    // checks if there are no students
    if (students.size() == 0)
    {
        cerr << "Error! There are no students!" << endl;
        return;
    }
    system("cls");
    for (int i = 0; i < students.size(); i++)
    {
        cout << makeStudentsReport(students, i);
    }
    cout << "Enter an index of a student you want to delete: ";
    int deleteIndex = findStudentIndex(students, inputValidation());

    for (int i = 0; i < teams.size(); i++)
    {
        // if the name of the team is equal to the teamstatus of the student, removes the team
        if (teams[i].name == students[deleteIndex].teamStatus)
        {
            archiveTeam(students, teachers, teams, true, findStudentIndex(students, i));
            break;
        }
    }
    students.erase(students.begin() + deleteIndex);
    system("cls");
}

void deleteTeacher(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    // checks if there are no teachers
    if (teachers.size() == 0)
    {
        cerr << "Error! There are no teachers!" << endl;
        return;
    }
    for (int i = 0; i < teachers.size(); i++)
    {
        cout << makeTeachersReport(teachers, i);
    }
    cout << "Enter an index of a teacher you want to delete: ";
    int deleteIndex = findTeacherIndex(teachers, inputValidation());

    // if there is one teacher, deletes all students, teachers and teams
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
                // if the teamname is equal to the teachers teaching teams name, change the teacher to the team
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

void editStudent(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
    // checks if there are no students
    if (students.size() == 0)
    {
        cerr << "Error! There are no students!" << endl;
        return;
    }
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
                // if the student name is equal to the teammate, changes the teammate name to the current student name
                if (students[findStudentIndex(students, editIndex)].firstName + " " + students[findStudentIndex(students, editIndex)].lastName == teams[i].students[j])
                {
                    teams[i].students[j] = container + " " + students[findStudentIndex(students, editIndex)].lastName;
                    students[findStudentIndex(students, editIndex)].firstName = container;
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
                // if the student name is equal to the teammate, changes the teammate name to the current student name
                if (students[findStudentIndex(students, editIndex)].firstName + " " + students[findStudentIndex(students, editIndex)].lastName == teams[i].students[j])
                {
                    teams[i].students[j] = students[findStudentIndex(students, editIndex)].firstName + " " + container;
                    students[findStudentIndex(students, editIndex)].lastName = container;
                    break;
                }
            }

        }
        break;
    case 3:
        students[findStudentIndex(students, editIndex)].grade = inputValidation();
        break;
    case 4:
        students[findStudentIndex(students, editIndex)].role = checkRole();
        break;
    case 5:
        students[findStudentIndex(students, editIndex)].email = checkEmail();
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
    // checks if there are no teachers
    if (teachers.size() == 0)
    {
        cerr << "Error! There are no teachers!" << endl;
        return;
    }
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
            // if the teacher of the team is equal to the teacher, changes the teacher of the team to current teacher's name 
            if (teams[i].teacher == teachers[findTeacherIndex(teachers, editIndex)].firstName + " " + teachers[findTeacherIndex(teachers, editIndex)].lastName)
            {
                teams[i].teacher = container + " " + teachers[findTeacherIndex(teachers, editIndex)].lastName;
            }
        }
        teachers[findTeacherIndex(teachers, editIndex)].firstName = container;
        break;
    case 2:
        cin >> container;
        for (int i = 0; i < teams.size(); i++)
        {
            // if the teacher of the team is equal to the teacher, changes the teacher of the team to current teacher's name 
            if (teams[i].teacher == teachers[findTeacherIndex(teachers, editIndex)].firstName + " " + teachers[findTeacherIndex(teachers, editIndex)].lastName)
            {
                teams[i].teacher = teachers[findTeacherIndex(teachers, editIndex)].firstName + " " + container;
            }
        }
        teachers[findTeacherIndex(teachers, editIndex)].lastName = container;
        break;
    case 0:
        return;
        break;
    default:
        editTeacher(students, teachers, teams);
        break;
    }
}