#pragma once
#include <string>
#include <vector>
#include "Structures.h"

std::string checkRole();

std::string checkEmail();

int inputValidation();

void addStudent(std::vector<STUDENT>& students, SCHOOL& school);

void addTeachers(std::vector<TEACHER>& teachers, SCHOOL& school);

int findRole(std::vector<STUDENT>& students, const std::string wantedRole, const std::string teamName);

int findNotOccupiedStudents(std::vector<STUDENT>& students);

void generateTeam(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

void saveFiles(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

int stringConvertor(std::string& text);

void openSave(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams, SCHOOL& school);

bool checkId(const std::vector<TEAM>& teams, const int wantedId);

int findTeamIndex(const std::vector<TEAM>& teams, const int wantedId);

int findStudentIndex(const std::vector<STUDENT>& students, const int wantedId);

int findTeacherIndex(const std::vector<TEACHER>& teachers, const int wantedId);

void archiveTeam(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams, bool removedPersonOrEditedPerson = false, int indexOfremovedPersonOrEditedPerson = 0);

void deleteStudent(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

void deleteTeacher(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

void editStudent(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

void editTeacher(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);