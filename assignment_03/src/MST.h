#ifndef MST_H
#define MST_H

#include "../../assignment_02/src/CSR.h"
#include <vector>

using namespace std;

// ============================================================
// RESULT STRUCTURES
// ============================================================

// Represents a single connection (edge) in the Minimum Spanning Tree
struct MSTEdge
{
    int u;      // Starting node
    int v;      // Ending node
    int weight; // Cost of the connection
};

// Holds the final result after running an MST algorithm
struct MSTResult
{
    vector<MSTEdge> edges;  // List of all edges chosen for the MST
    long long total_weight; // Total cost of all chosen edges combined
    bool connected;         // True if all nodes could be connected, False otherwise
};

// ============================================================
// ALGORITHM DEFINITIONS
// ============================================================

class MSTAlgorithms
{
public:
    // 1. Kruskal's Minimum Spanning Tree Algorithm
    static MSTResult kruskal(const CSRGraph &graph);

    // 2. Prim's Minimum Spanning Tree Algorithm
    static MSTResult prim(const CSRGraph &graph);
};

#endif