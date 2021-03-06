#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Structures.h"
#include "DataLayer.h"

using namespace std;

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
    cout << "|-----------------------------------------------------|" << endl;
    cout << "|              1. Create students reports             |" << endl;
    cout << "|              2. Create teachers report              |" << endl;
    cout << "|              3. Create teams report                 |" << endl;
    cout << "|              4. Create school report                |" << endl;
    cout << "|              0. Exit                                |" << endl;
    cout << "|-----------------------------------------------------|" << endl;
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
            cout << "Congratulations! Your students report has been saved! " << endl;
        }
        else {
            cerr << "Error! Can't open studentsReport text file! " << endl;
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
            cout << "Congratulations! Your teachers report has been saved! " << endl;
        }
        else {
            cerr << "Error! Can't open teachersReport text file! " << endl;
        }
        break;
    case 3:
        reports.open("Reports\\teamsReport.txt", ios::in | ios::trunc);
        if (reports.is_open())
        {
            for (int i = 0; i < teams.size(); i++)
            {
                reports << makeTeamsReport(teams, i);
            }
            reports.close();
            cout << "Congratulations! Your teams report has been saved! " << endl;
        }
        else {
            cerr << "Error! Can't open teamsReport text file! " << endl;
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
            cerr << "Error! Can't open schoolReport text file! " << endl;
        }
        break;
    case 0:
        return;
        break;
    default:
        break;
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
    cout << "|------------------------------------------------------------------|" << endl;
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