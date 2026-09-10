#ifndef ASSIGNMENT_04_ALGORITHMS_H
#define ASSIGNMENT_04_ALGORITHMS_H

#include <vector>
#include "CSR.h"

using namespace std;

// ============================================================
// RESULT STRUCTURES
// ============================================================

// Holds the final results for the Vertex Coloring algorithm
struct ColoringResult
{
    vector<int> color;  // The color assigned to each vertex (e.g., 0, 1, 2...)
    int colorsUsed = 0; // Total number of different colors needed
    bool valid = false; // True if the coloring is correct (no connected nodes share the same color)
};

// Holds the final results for the PageRank algorithm
struct PageRankResult
{
    vector<double> rank;    // The final PageRank score for each vertex
    int iterations = 0;     // How many loops it took to finish
    bool converged = false; // True if the scores stabilized successfully before hitting the max limit
};

// ============================================================
// ALGORITHM DEFINITIONS
// ============================================================

// 1. Greedy Vertex Coloring (Welsh-Powell)
ColoringResult greedyColoring(const CSRGraph &graph);

// 2. PageRank Algorithm
PageRankResult pageRank(const CSRGraph &graph, double damping, double tolerance, int maxIterations);

#endif