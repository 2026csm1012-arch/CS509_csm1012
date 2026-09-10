#ifndef ASSIGNMENT_04_GRAPH_IO_H
#define ASSIGNMENT_04_GRAPH_IO_H

#include <string>
#include <vector>
#include "CSR.h"

using namespace std;

// ============================================================
// DATA STRUCTURES
// ============================================================

// A basic structure to hold a graph before it gets converted to CSR
struct Graph
{
    int V = 0;             // Number of Vertices (nodes)
    int E = 0;             // Number of Edges (connections)
    bool weighted = false; // Does the graph have edge weights?

    // Adjacency List: A list of neighbors for every single node
    vector<vector<int>> adj;
};

// Holds the graph and the specific math settings needed for PageRank
struct PageRankInput
{
    Graph graph;             // The graph data
    double damping = 0.85;   // The probability of following a link (default is 85%)
    double tolerance = 1e-4; // Stop running if scores change by less than this tiny amount
    int maxIterations = 100; // The maximum number of loops allowed so it doesn't run forever
};

// ============================================================
// FILE READING & HELPERS
// ============================================================

// Reads a basic unweighted graph from a text file (used for Vertex Coloring)
Graph readUnweightedGraph(const string &filename, bool undirected);

// Checks if the graph is valid for Vertex Coloring (e.g., making sure it has no self-loops)
void validateVertexColoringGraph(const Graph &graph);

// Reads a graph and its special settings from a text file (used for PageRank)
PageRankInput readPageRankGraph(const string &filename);

// Converts our basic Graph object into the much faster CSRGraph format
CSRGraph convertToCSR(const Graph &graph);

#endif