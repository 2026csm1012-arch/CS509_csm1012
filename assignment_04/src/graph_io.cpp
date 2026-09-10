#include "graph_io.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

using namespace std;

// ============================================================
// HELPER: READ BASIC ADJACENCY LIST FROM FILE
// ============================================================
static Graph readAdjacency(const string& filename) {
    // 1. Open the file
    ifstream fin(filename);
    if (!fin)
        throw runtime_error("Error: Unable to open input file: " + filename);

    Graph g;
    // 2. Read the total number of Vertices (V) and Edges (E)
    if (!(fin >> g.V >> g.E) || g.V <= 0 || g.E < 0)
        throw runtime_error("Error: invalid V/E in " + filename);

    // Initialize the adjacency list vector with empty slots for all vertices
    g.adj.assign(g.V, {});

    // 3. Read exact adjacency list entries for each vertex
    for (int i = 0; i < g.V; ++i) {
        int u, degree;
        if (!(fin >> u >> degree) || u < 0 || u >= g.V || degree < 0)
            throw runtime_error("Error: invalid adjacency-list header in " + filename);

        // Make sure we don't accidentally read duplicate records for the same node
        if (!g.adj[u].empty())
            throw runtime_error("Error: duplicate adjacency-list record for vertex " +
                                to_string(u));

        // Resize the sub-vector to hold all neighbors for this node
        g.adj[u].resize(degree);
        for (int j = 0; j < degree; ++j) {
            if (!(fin >> g.adj[u][j]) || g.adj[u][j] < 0 || g.adj[u][j] >= g.V)
                throw runtime_error("Error: out-of-range vertex id in " + filename);
        }
    }

    return g;
}

// ============================================================
// READ UNWEIGHTED GRAPH (Used for Vertex Coloring)
// ============================================================
Graph readUnweightedGraph(const string& filename, bool undirected) {
    Graph g = readAdjacency(filename);
    // If the graph is undirected, validate its structure for vertex coloring rules
    if (undirected)
        validateVertexColoringGraph(g);
    return g;
}

// ============================================================
// VALIDATE GRAPH INTEGRITY FOR VERTEX COLORING
// ============================================================
void validateVertexColoringGraph(const Graph& g) {
    long long entries = 0;
    vector<unordered_set<int>> seen(g.V);

    for (int u = 0; u < g.V; ++u) {
        seen[u].reserve(g.adj[u].size() * 2 + 1);
        for (int v : g.adj[u]) {
            // Check for self-loops (a node connecting to itself)
            if (u == v)
                throw runtime_error("Error: self-loop found at vertex " + to_string(u));
            // Check for duplicate parallel edges
            if (!seen[u].insert(v).second)
                throw runtime_error("Error: parallel edge found");
            ++entries;
        }
    }

    // Ensure edge entries match 2E for undirected graphs
    if (entries != 2LL * g.E)
        throw runtime_error("Error: adjacency entries do not equal 2E for undirected graph");

    // Ensure edges are symmetric (if u connects to v, v must connect to u)
    for (int u = 0; u < g.V; ++u) {
        for (int v : g.adj[u]) {
            if (seen[v].find(u) == seen[v].end())
                throw runtime_error("Error: undirected edge is not present at both endpoints");
        }
    }
}

// ============================================================
// READ PAGERANK GRAPH & MATH PARAMETERS
// ============================================================
PageRankInput readPageRankGraph(const string& filename) {
    PageRankInput input;
    // Read the standard graph layout first
    input.graph = readAdjacency(filename);

    // Reopen the file to read additional configuration parameters at the bottom
    ifstream fin(filename);
    if (!fin)
        throw runtime_error("Error: Unable to reopen input file: " + filename);

    int V, E;
    fin >> V >> E;
    // Skip through the adjacency list lines we already parsed
    for (int i = 0; i < V; ++i) {
        int u, degree;
        fin >> u >> degree;
        for (int j = 0; j < degree; ++j) {
            int v;
            fin >> v;
        }
    }

    string label;
    // Read and validate Damping factor, Tolerance, and Max Iterations
    if (!(fin >> label >> input.damping) || label != "DAMPING")
        throw runtime_error("Error: expected DAMPING in " + filename);
    if (!(fin >> label >> input.tolerance) || label != "TOLERANCE")
        throw runtime_error("Error: expected TOLERANCE in " + filename);
    if (!(fin >> label >> input.maxIterations) || label != "MAX_ITERATIONS")
        throw runtime_error("Error: expected MAX_ITERATIONS in " + filename);

    // Validate parameter value constraints
    if (!(input.damping > 0.0 && input.damping < 1.0))
        throw runtime_error("Error: damping must satisfy 0 < d < 1");
    if (!(input.tolerance > 0.0) || input.maxIterations <= 0)
        throw runtime_error("Error: tolerance and MAX_ITERATIONS must be positive");

    return input;
}

// ============================================================
// CONVERT TO CSR FORMAT
// ============================================================
CSRGraph convertToCSR(const Graph& graph) {
    // Calls the shared conversion function defined in CSR.cpp
    return convertToCSR(graph.adj);
}