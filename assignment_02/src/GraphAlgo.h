#ifndef GRAPH_ALGO_H
#define GRAPH_ALGO_H

#include "CSR.h"
#include <vector>
using namespace std;

struct ShortestPathResult
{
    bool has_negative_cycle;
    vector<int> distances;
};

struct AllPairsResult
{
    bool has_negative_cycle;
    vector<vector<int>> distances;
};

class GraphAlgorithms
{
    public:
        static ShortestPathResult bellmanFord(const CSRGraph &graph, int source);
        static AllPairsResult floydWarshall(const CSRGraph &graph);
};

#endif