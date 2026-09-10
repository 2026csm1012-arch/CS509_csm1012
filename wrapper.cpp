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
    cout << "3. Assignment 3\n";
    cout << "4. Assignment 4\n\n";

    cout << "Enter assignment number: ";
    if (!(cin >> choice)) {
        cout << "\nInvalid input.\n";
        return 1;
    }

    switch (choice)
    {
    case 1:
        cout << "\nBuilding Assignment 1...\n";
        if (system("make -C assignment_01") != 0)
            return 1;

        cout << "\nStarting Assignment 1...\n\n";
        return system("cd /d assignment_01 && assignment_01.exe");

    case 2:
        cout << "\nBuilding Assignment 2...\n";
        if (system("make -C assignment_02") != 0)
            return 1;

        cout << "\nStarting Assignment 2...\n\n";
        return system("cd /d assignment_02 && assignment_02.exe");

    case 3:
        cout << "\nBuilding Assignment 3...\n";
        if (system("make -C assignment_03") != 0)
            return 1;

        cout << "\nStarting Assignment 3...\n\n";
        return system("cd /d assignment_03 && assignment_03.exe");

    case 4:
        cout << "\nBuilding Assignment 4...\n";
        if (system("make -C assignment_04") != 0)
            return 1;

        cout << "\nStarting Assignment 4...\n\n";
        return system("cd /d assignment_04 && assignment_04.exe");

    default:
        cout << "\nInvalid assignment number.\n";
        return 1;
    }
}