#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <string>

#include "../src/algorithm.h"

using namespace std;
using namespace std::chrono;

// Create matrices
void creating_matrix(int **&a, int **&b, int **&c, int m, int n, int p)
{
    a = new int *[m];
    b = new int *[n];
    c = new int *[m];

    for (int i = 0; i < m; i++)
    {
        a[i] = new int[n];
        c[i] = new int[p];
    }

    for (int i = 0; i < n; i++)
    {
        b[i] = new int[p];
    }
}

int main()
{
    int m, n, p;
    int block;
    int choice;

    int **a;
    int **b;
    int **c;

    cout << "Select the method:\n";
    cout << "1. GEMM\n";
    cout << "2. Blocking\n";
    cout << "Enter choice: ";

    cin >> choice;

    // Ask blocking factor only for Blocking
    if (choice == 2)
    {
        cout << "Enter Blocking factor: ";
        cin >> block;
    }

    // Test files
    string files[] =
        {
            "test (1).txt",
            "test (2).txt",
            "test (3).txt",
            "test (4).txt",
            "test (5).txt"};

    // Run all test files
    for (int i = 0; i < 5; i++)
    {
        string filename = "tests/" + files[i];

        ifstream input(filename);

        if (!input)
        {
            cout << "Cannot open file: " << filename << endl;
            continue;
        }

        // Read dimensions
        input >> m >> n >> p;

        // Create matrices
        creating_matrix(a, b, c, m, n, p);

        // Read matrix A
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                input >> a[i][j];
            }
        }

        // Read matrix B
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < p; j++)
            {
                input >> b[i][j];
            }
        }

        input.close();

        // Run algorithm
        if (choice == 1)
        {
            GEMM(c, a, b, m, n, p);
        }
        else if (choice == 2)
        {
            blocking_matrix(c, a, b, m, n, p, block);
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }

        // Display information
        cout << "File: " << files[i] << endl;
        cout << "Matrix size: "
             << m << "x" << n
             << " * "
             << n << "x" << p
             << endl;

        // Delete matrix A
        for (int i = 0; i < m; i++)
        {
            delete[] a[i];
        }

        delete[] a;

        // Delete matrix B
        for (int i = 0; i < n; i++)
        {
            delete[] b[i];
        }

        delete[] b;

        // Delete matrix C
        for (int i = 0; i < m; i++)
        {
            delete[] c[i];
        }

        delete[] c;
    }

    return 0;
}