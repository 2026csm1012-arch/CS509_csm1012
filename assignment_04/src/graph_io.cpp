#include "graph_io.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

using namespace std;

static Graph readAdjacency(const string& filename) {
    ifstream fin(filename);
    if (!fin)
        throw runtime_error("Error: Unable to open input file: " + filename);

    Graph g;
    if (!(fin >> g.V >> g.E) || g.V <= 0 || g.E < 0)
        throw runtime_error("Error: invalid V/E in " + filename);

    g.adj.assign(g.V, {});

    // Exactly V adjacency-list records are expected.
    for (int i = 0; i < g.V; ++i) {
        int u, degree;
        if (!(fin >> u >> degree) || u < 0 || u >= g.V || degree < 0)
            throw runtime_error("Error: invalid adjacency-list header in " + filename);

        if (!g.adj[u].empty())
            throw runtime_error("Error: duplicate adjacency-list record for vertex " +
                                to_string(u));

        g.adj[u].resize(degree);
        for (int j = 0; j < degree; ++j) {
            if (!(fin >> g.adj[u][j]) || g.adj[u][j] < 0 || g.adj[u][j] >= g.V)
                throw runtime_error("Error: out-of-range vertex id in " + filename);
        }
    }

    return g;
}

Graph readUnweightedGraph(const string& filename, bool undirected) {
    Graph g = readAdjacency(filename);
    if (undirected)
        validateVertexColoringGraph(g);
    return g;
}

void validateVertexColoringGraph(const Graph& g) {
    long long entries = 0;
    vector<unordered_set<int>> seen(g.V);

    for (int u = 0; u < g.V; ++u) {
        seen[u].reserve(g.adj[u].size() * 2 + 1);
        for (int v : g.adj[u]) {
            if (u == v)
                throw runtime_error("Error: self-loop found at vertex " + to_string(u));
            if (!seen[u].insert(v).second)
                throw runtime_error("Error: parallel edge found");
            ++entries;
        }
    }

    if (entries != 2LL * g.E)
        throw runtime_error("Error: adjacency entries do not equal 2E for undirected graph");

    for (int u = 0; u < g.V; ++u) {
        for (int v : g.adj[u]) {
            if (seen[v].find(u) == seen[v].end())
                throw runtime_error("Error: undirected edge is not present at both endpoints");
        }
    }
}

PageRankInput readPageRankGraph(const string& filename) {
    PageRankInput input;
    input.graph = readAdjacency(filename);

    ifstream fin(filename);
    if (!fin)
        throw runtime_error("Error: Unable to reopen input file: " + filename);

    int V, E;
    fin >> V >> E;
    for (int i = 0; i < V; ++i) {
        int u, degree;
        fin >> u >> degree;
        for (int j = 0; j < degree; ++j) {
            int v;
            fin >> v;
        }
    }

    string label;
    if (!(fin >> label >> input.damping) || label != "DAMPING")
        throw runtime_error("Error: expected DAMPING in " + filename);
    if (!(fin >> label >> input.tolerance) || label != "TOLERANCE")
        throw runtime_error("Error: expected TOLERANCE in " + filename);
    if (!(fin >> label >> input.maxIterations) || label != "MAX_ITERATIONS")
        throw runtime_error("Error: expected MAX_ITERATIONS in " + filename);

    if (!(input.damping > 0.0 && input.damping < 1.0))
        throw runtime_error("Error: damping must satisfy 0 < d < 1");
    if (!(input.tolerance > 0.0) || input.maxIterations <= 0)
        throw runtime_error("Error: tolerance and MAX_ITERATIONS must be positive");

    return input;
}

CSRGraph convertToCSR(const Graph& graph) {
    return convertToCSR(graph.adj);
}
