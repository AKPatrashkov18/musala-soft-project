#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT
{
    string firstName;
    string LastName;
    int grade;
    string role;
    string email;
    string teamName = "Not occupied";
};

struct TEACHERS
{
    string firstName;
    string LastTeam;
    vector<string> teachingTeams;
};

struct TEAM
{
    string name;
    string discription;
    int day, mounth, year;
    string students[4];
    string studentsStatus[4];
};


bool mainMenu()
{
    cout << "1. Add students or teachers"<<endl;
    cout << "2. Generate team"<<endl;
    cout << "3. Edit teams, students or teachers"<<endl;
    cout << "4. Print teams, students or teachers" << endl;
    cout << "9. Exit"<<endl;
    int option;
    cin >> option;
    switch (option)
    {
        case 1:
            return true;
            break;
        case 2:
            return true;
            break;
        case 3:
            return true;
            break;
        case 4:
            return true;
            break;
        case 9:
            return false;
            break;
        default:
            return mainMenu();

    }

}

int main()
{
    //vector<STUDENT> students;
    bool exit=false;
    do {
        exit = mainMenu();
    } while (exit);
    return 0;
}
