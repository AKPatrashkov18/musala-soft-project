#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Structures.h"
#include "DataLayer.h"

using namespace std;

void insertTestData(vector<STUDENT>& students, vector<TEACHER>& teachers)
{
	students.push_back(STUDENT());
	students[0].firstName = "Stanislav";
	students[0].lastName = "Todorov";
	students[0].grade = 10;
	students[0].role = "FrontEnd";
	students[0].email = "SAT@";
	students[0].teamStatus = "Not occupied";
	students[0].id = 0;

	students.push_back(STUDENT());
	students[1].firstName = "Aleksandar";
	students[1].lastName = "Patrashkov";
	students[1].grade = 10;
	students[1].role = "Scrum";
	students[1].email = "AKP@";
	students[1].teamStatus = "Not occupied";
	students[1].id = 1;

	students.push_back(STUDENT());
	students[2].firstName = "Martin";
	students[2].lastName = "Bakalov";
	students[2].grade = 10;
	students[2].role = "QA";
	students[2].email = "MB@";
	students[2].id = 2;
	students[2].teamStatus = "Not occupied";

	students.push_back(STUDENT());
	students[3].firstName = "Kaloyan";
	students[3].lastName = "Dinev";
	students[3].grade = 10;
	students[3].role = "BackEnd";
	students[3].email = "kdd@";
	students[3].teamStatus = "Not occupied";
	students[3].id = 3;

	
	teachers.push_back(TEACHER());
	teachers[0].firstName = "Petar";
	teachers[0].lastName = "Georgiev";
	teachers[0].id = 0;

	teachers.push_back(TEACHER());
	teachers[1].firstName = "Petar2";
	teachers[1].lastName = "Georgiev2";
	teachers[1].id = 1;
}

void testFindNotOccupiedStudents(vector<STUDENT>& students, vector<TEACHER>& teachers)
{
	insertTestData(students, teachers);
	int notOccupiedCount = findNotOccupiedStudents(students);

	if (notOccupiedCount == 4)
	{
		cout << "Pass!" << endl;
	}
	else
	{
		cout << "Fail!" << endl;
	}
	students.clear();
	teachers.clear();
}

void testIsDataSavesCorrectly(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
	insertTestData(students, teachers);
	saveFiles(students, teachers, teams);
	ifstream testFile;
	string container;

	testFile.open("Save files\\studentsSaveFile.txt", ios::out);
	if (testFile.is_open())
	{
		getline(testFile, container);
		if (container == students[0].toString())
		{
			cout << "Pass!" << endl;
		}
		else
		{
			cout << "Fail" << endl;
		}
		testFile.close();
	}
	else
	{
		cout << "Fail!" << endl;
	}
	students.clear();
	teachers.clear();
}

void testIsStringConvertedCorrectly()
{
	string number = "1083294";

	if (stringConvertor(number) == 1083294)
	{
		cout << "Pass!" << endl;
	}
	else
	{
		cout << "Fail!" << endl;
	}
}

void testFindIndex(vector<STUDENT>& students, vector<TEACHER>& teachers)
{
	insertTestData(students, teachers);

	if (findStudentIndex(students, 1) == 1)
	{
		cout << "Pass!" << endl;
	}
	else
	{
		cout << "Fail!" << endl;
	}

	students.clear();
	teachers.clear();
}

void testIfTeamsAreArchivedCorrectly(vector<STUDENT>& students, vector<TEACHER>& teachers, vector<TEAM>& teams)
{
	insertTestData(students, teachers);
	generateTeam(students, teachers, teams);
	archiveTeam(students, teachers, teams, true, 0);

	if (teams.size() == 0 and teachers[0].teachingTeams.size() == 0)
	{
		cout << "Pass!" << endl;
	}
	else
	{
		cout << "Fail!" << endl;
	}
}