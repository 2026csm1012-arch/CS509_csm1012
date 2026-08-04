#include <iostream>
#include <chrono>
#include <algorithm> // Added for std::min
#include <ctime>     // Added for clock_t and clock()

using namespace std;

void GEMM(int **result, int **one, int **sec, int m, int n, int p)
{

    clock_t start, end;
    start = clock();

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

    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time taken: " << duration * 1000 << " ms" << endl;
}

void blocking_matrix(int **result, int **one, int **sec, int m, int n, int p, int B)
{

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++)
            result[i][j] = 0;

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
                            result[i][j] += one[i][k] * sec[k][j];
                        }
                    }
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();

auto duration =
chrono::duration_cast<chrono::microseconds>(end-start);

cout << duration.count() << " us";


}