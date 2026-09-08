#ifndef ASSIGNMENT_04_CSR_H
#define ASSIGNMENT_04_CSR_H

#include <vector>

struct CSRGraph {
    int V = 0;
    int E = 0;
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
};

CSRGraph convertToCSR(const std::vector<std::vector<int>>& adj);

#endif
