#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <string>

#include "../src/algorithm.h"

using namespace std;
using namespace std::chrono;

void creating_matrix(int **&a, int **&b, int **&c, int m, int n, int p)
{
    int **one = new int *[m];
    for (int i = 0; i < m; i++)
    {
        one[i] = new int[n];
    }
    int **sec = new int *[n];
    for (int i = 0; i < n; i++)
    {
        sec[i] = new int[p];
    }
    int **result = new int *[m];
    for (int i = 0; i < m; i++)
    {
        result[i] = new int[p];
    }
    a = one;
    b = sec;
    c = result;
}

int main()
{
    int m, n, p, block;
    int **a, **b, **c;
    string rc;

    cout << " select the method you want to proceed with: " << endl;
    cout << " 1. GEMM " << endl;
    cout << " 2. Blocking " << endl;
    int choice;
    cin >> choice;

    if (choice == 2)
    {
        cout << " Enter Blocking factor: " << endl;
        cin >> block;
    }

    for (string filename : {"test (1).txt", "test (2).txt", "test (3).txt", "test (4).txt", "test (5).txt"})
    {

        ifstream dimen("tests/" + filename);

        // ADDED: Safety check to prevent segmentation faults
        if (!dimen.is_open())
        {
            cerr << "Error: Could not open file " << filename << ". Check your file paths." << endl;
            continue;
        }

        dimen >> m >> n >> p;
        creating_matrix(a, b, c, m, n, p);

        // formating and setting values in matrix
        //  one
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dimen >> a[i][j];
            }
        }
        // sec
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < p; j++)
            {
                dimen >> b[i][j];
            }
        }
        dimen.close();

        switch (choice)
        {
        case 1:
            GEMM(c, a, b, m, n, p);
            break;
        case 2:
            blocking_matrix(c, a, b, m, n, p, block);
            break;

        default:
            cout << "invalid output" << endl;
            break;
        }

        // freeup memory
        for (int i = 0; i < m; i++)
            delete[] a[i];
        delete[] a;

        for (int i = 0; i < n; i++)
            delete[] b[i];
        delete[] b;

        for (int i = 0; i < m; i++)
            delete[] c[i];
        delete[] c;

        cout << "Matrix dimensions for file " << filename << ": " << m << "x" << n << ", " << n << "x" << p << endl;
    }

    // ifstream dimen("../tests/input"+ to_string(i) + ".txt");
    // getline(dimen, rc);
    // stringstream str(rc);
    // str >> m >> n >> p;

    // creating_matrix(a, b, c, m, n, p);

    // inisitalising one

    return 0;
}