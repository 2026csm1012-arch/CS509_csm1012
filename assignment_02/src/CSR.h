#ifndef CSR_H
#define CSR_H

#include <string>
#include <vector>
#include <limits>

using namespace std;

constexpr int GRAPH_INF = numeric_limits<int>::max() / 2;

class CSRGraph
{
private:
    int V;
    int E;
    bool is_weighted;
    int source_vertex;

    vector<int> offset;
    vector<int> intermediaries;
    vector<int> weights;

public:
    explicit CSRGraph(bool weighted = false);

    // Bellman-Ford / edge-list input
    bool loadFromFile(const string &filepath);

    // Floyd-Warshall / adjacency-matrix input
    bool loadMatrixFromFile(const string &filepath);

    void printCSR() const;

    int getVertices() const { return V; }
    int getEdges() const { return E; }
    int getSource() const { return source_vertex; }
    bool isWeighted() const { return is_weighted; }

    const vector<int> &getOffset() const { return offset; }
    const vector<int> &getIntermediaries() const { return intermediaries; }
    const vector<int> &getWeights() const { return weights; }
};

#endif