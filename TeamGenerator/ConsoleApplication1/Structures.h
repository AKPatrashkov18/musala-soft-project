#pragma once

#include <string>
#include <vector>

struct STUDENT
{
    std::string firstName;
    std::string lastName;
    int grade = 0;
    std::string role;
    std::string email;
    std::string teamStatus;
    size_t id = 0;

    std::string toString();
};

struct TEACHER
{
    std::string firstName;
    std::string lastName;
    std::vector<std::string> teachingTeams;
    size_t id = 0;
    std::string toString();
};

struct TEAM
{
    std::string name;
    std::string discription;
    std::string date;
    std::vector<std::string> students;
    std::string teacher;
    size_t id = 0;
    std::string toString();
};

struct SCHOOL
{
    std::string name;
    std::vector<std::string> studentsName;
    std::vector<std::string> teachersName;
};