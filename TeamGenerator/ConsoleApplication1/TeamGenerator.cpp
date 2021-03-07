#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>  
#include <sstream>
#include <ctime> 
#include <conio.h>
#include "PresentationLayer.h"
#include "DataLayer.h"
#include "Structures.h"

using namespace std;

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

