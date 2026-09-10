#ifndef CSR_H
#define CSR_H

#include <string>
#include <vector>

using namespace std;

class CSRGraph
{
private:
    // Basic Graph Information
    int V;             // Number of Vertices (nodes)
    int E;             // Number of Edges (connections)
    bool is_weighted;  // Does the graph have edge weights?
    int source_vertex; // Starting node (if applicable)

    // CSR Arrays (Assignment 2 style)
    vector<int> offset;
    vector<int> intermediaries;
    vector<int> weights;

public:
    // Constructor
    CSRGraph(bool weighted = false);

    // File Loaders
    bool loadFromFile(const string &filepath);
    bool loadMatrixFromFile(const string &filepath);

    // Printer
    void printCSR() const;

    // Getters (Safely read the private variables)
    int getVertices() const { return V; }
    int getEdges() const { return E; }
    int getSource() const { return source_vertex; }
    bool isWeighted() const { return is_weighted; }

    const vector<int> &getOffset() const { return offset; }
    const vector<int> &getIntermediaries() const { return intermediaries; }
    const vector<int> &getWeights() const { return weights; }

    // ============================================================
    // ASSIGNMENT 4 CONVERTER PERMISSION
    // ============================================================
    // The "friend" keyword lets this specific external function access
    // the private variables above so it can build the graph in memory.
    friend CSRGraph convertToCSR(const vector<vector<int>> &adj);
};

// Function declaration for Assignment 4
CSRGraph convertToCSR(const vector<vector<int>> &adj);

#endif