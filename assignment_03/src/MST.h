#ifndef MST_H
#define MST_H

#include "../../assignment_02/src/CSR.h"
#include <vector>

struct MSTEdge
{
    int u;
    int v;
    int weight;
};

struct MSTResult
{
    std::vector<MSTEdge> edges;
    long long total_weight;
    bool connected;
};

class MSTAlgorithms
{
public:
    static MSTResult kruskal(const CSRGraph &graph);
    static MSTResult prim(const CSRGraph &graph);
};

#endif
