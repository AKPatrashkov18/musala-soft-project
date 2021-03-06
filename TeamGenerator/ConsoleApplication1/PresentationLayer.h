#pragma once

#include <string>
#include <vector>
#include "Structures.h"

std::string makeStudentsReport(const std::vector<STUDENT>& students, int wantedIndex);

std::string makeTeachersReport(const std::vector<TEACHER>& teachers, int wantedIndex);

std::string makeTeamsReport(const std::vector<TEAM>& teams, int wantedIndex);

std::string makeSchoolReport(const SCHOOL& school);

void printMenu(const std::vector<STUDENT>& students, const std::vector<TEACHER>& teachers, const std::vector<TEAM>& teams, const SCHOOL& school);

void reportsMenu(const std::vector<STUDENT>& students, const std::vector<TEACHER>& teachers, const std::vector<TEAM>& teams, const SCHOOL& school);

void tutorial();

void editMenu(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

bool mainMenu(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams, SCHOOL& school);