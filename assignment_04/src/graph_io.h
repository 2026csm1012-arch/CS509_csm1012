#ifndef ASSIGNMENT_04_GRAPH_IO_H
#define ASSIGNMENT_04_GRAPH_IO_H

#include <string>
#include <vector>
#include "CSR.h"

struct Graph {
    int V = 0;
    int E = 0;
    bool weighted = false;
    std::vector<std::vector<int>> adj;
};

Graph readUnweightedGraph(const std::string& filename, bool undirected);
void validateVertexColoringGraph(const Graph& graph);

struct PageRankInput {
    Graph graph;
    double damping = 0.85;
    double tolerance = 1e-4;
    int maxIterations = 100;
};

PageRankInput readPageRankGraph(const std::string& filename);

CSRGraph convertToCSR(const Graph& graph);

#endif
