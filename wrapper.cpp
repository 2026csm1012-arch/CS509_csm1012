#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
    int choice;

    cout << "\n";
    cout << "====================================\n";
    cout << "        PGSL Assignment Wrapper\n";
    cout << "====================================\n\n";

    cout << "1. Assignment 1\n";
    cout << "2. Assignment 2\n";
    cout << "3. Assignment 3\n\n";

    cout << "Enter assignment number: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\nBuilding Assignment 1...\n";

        if (system("make -C assignment_01") != 0)
            return 1;

        cout << "\nStarting Assignment 1...\n\n";

        return system("cd /d assignment_01 && build\\assignment_01.exe");

    case 2:
        cout << "\nBuilding Assignment 2...\n";

        if (system("make -C assignment_02") != 0)
            return 1;

        cout << "\nStarting Assignment 2...\n\n";

        return system(
            "cd /d assignment_02 && build\\assignment_02.exe");

    case 3:
        cout << "\nBuilding Assignment 3...\n";

        if (system("make -C assignment_03") != 0)
            return 1;

        cout << "\nStarting Assignment 3...\n\n";

        return system(
            "cd /d assignment_03 && build\\assignment_03.exe");
    default:
        cout << "\nInvalid assignment number.\n";
        return 1;
    }
}