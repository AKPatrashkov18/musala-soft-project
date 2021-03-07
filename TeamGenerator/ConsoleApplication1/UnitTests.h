#pragma once

#include <string>
#include <vector>
#include "Structures.h"

void insertTestData(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers);

void testFindNotOccupiedStudents(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers);

void testIsDataSavesCorrectly(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);

void testIsStringConvertedCorrectly();

void testFindIndex(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers);

void testIfTeamsAreArchivedCorrectly(std::vector<STUDENT>& students, std::vector<TEACHER>& teachers, std::vector<TEAM>& teams);
