#ifndef ASSIGNMENT_04_ALGORITHMS_H
#define ASSIGNMENT_04_ALGORITHMS_H

#include <vector>
#include "CSR.h"

struct ColoringResult {
    std::vector<int> color;
    int colorsUsed = 0;
    bool valid = false;
};

struct PageRankResult {
    std::vector<double> rank;
    int iterations = 0;
    bool converged = false;
};

ColoringResult greedyColoring(const CSRGraph& graph);
PageRankResult pageRank(const CSRGraph& graph, double damping,
                        double tolerance, int maxIterations);

#endif
