#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Normal Matrix Multiplication
void GEMM(int **result, int **one, int **sec, int m, int n, int p)
{
    auto start = high_resolution_clock::now();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            result[i][j] = 0;

            for (int k = 0; k < n; k++)
            {
                result[i][j] += one[i][k] * sec[k][j];
            }
        }
    }

    auto end = high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(end - start);

    cout << "GEMM Time: "
         << duration.count()
         << " us" << endl;
}

// Matrix Multiplication using Blocking
void blocking_matrix(int **result, int **one, int **sec,
                     int m, int n, int p, int B)
{
    auto start = high_resolution_clock::now();

    // Set result matrix to 0
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            result[i][j] = 0;
        }
    }

    // Blocking
    for (int ii = 0; ii < m; ii += B)
    {
        for (int jj = 0; jj < p; jj += B)
        {
            for (int kk = 0; kk < n; kk += B)
            {
                for (int i = ii; i < min(ii + B, m); i++)
                {
                    for (int j = jj; j < min(jj + B, p); j++)
                    {
                        for (int k = kk; k < min(kk + B, n); k++)
                        {
                            result[i][j] +=
                                one[i][k] * sec[k][j];
                        }
                    }
                }
            }
        }
    }

    auto end = high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(end - start);

    cout << "Blocking Time: "
         << duration.count()
         << " us" << endl;
}