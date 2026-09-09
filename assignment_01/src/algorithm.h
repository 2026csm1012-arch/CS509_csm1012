#ifndef ALGORITHM_H
#define ALGORITHM_H

void GEMM(int **result, int **one, int **sec, int m, int n, int p);

void blocking_matrix(int **result, int **one, int **sec, int m, int n, int p, int B);

#endif