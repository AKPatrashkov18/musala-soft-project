#include "Structures.h"
#include <string>
#include <vector>

using namespace std;


string STUDENT::toString()
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

string TEACHER::toString()
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

string TEAM::toString()
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