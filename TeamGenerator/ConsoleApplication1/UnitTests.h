#pragma once

#include <string>
#include <vector>
#include "Structures.h"

void insertTestData(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers);

void testFindNotOccupiedStudents(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers);

void testIsDataSaves(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

void testIsStringConverted();

void testFindIndex(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers);

void testIfTeamsAreArchived(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

void testAreStudentsDeleted(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

void testAreTeachersDeleted(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);
