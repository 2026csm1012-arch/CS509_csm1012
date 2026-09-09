#include "MST.h"
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

// ============================================================
// HELPER CLASS: DISJOINT SET (For Kruskal's Algorithm)
// ============================================================
class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank_value;

public:
    // Constructor: Set up the sets so every node is its own parent initially
    DisjointSet(int n)
    {
        parent.resize(n);
        rank_value.assign(n, 0);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // Find the root parent of a node (with path compression)
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Merge two sets together. Returns true if they were merged, false if already together.
    bool unite(int a, int b)
    {
        int root_a = find(a);
        int root_b = find(b);

        // They are already in the same set (would create a cycle)
        if (root_a == root_b)
        {
            return false;
        }

        // Attach the smaller tree under the larger tree
        if (rank_value[root_a] < rank_value[root_b])
        {
            parent[root_a] = root_b;
        }
        else if (rank_value[root_a] > rank_value[root_b])
        {
            parent[root_b] = root_a;
        }
        else
        {
            parent[root_b] = root_a;
            rank_value[root_a]++;
        }

        return true;
    }
};

// ============================================================
// HELPER FUNCTION: SORT EDGES
// ============================================================
// Used by Kruskal's to sort edges from smallest weight to largest
bool compareEdges(const MSTEdge &a, const MSTEdge &b)
{
    if (a.weight != b.weight)
    {
        return a.weight < b.weight;
    }
    if (a.u != b.u)
    {
        return a.u < b.u;
    }
    return a.v < b.v;
}

// ============================================================
// KRUSKAL'S ALGORITHM
// ============================================================
MSTResult MSTAlgorithms::kruskal(const CSRGraph &graph)
{
    int V = graph.getVertices();
    const vector<int> &offset = graph.getOffset();
    const vector<int> &targets = graph.getIntermediaries();
    const vector<int> &weights = graph.getWeights();

    vector<MSTEdge> edges;

    // 1. Extract all edges from the CSR graph
    for (int u = 0; u < V; u++)
    {
        for (int e = offset[u]; e < offset[u + 1]; e++)
        {
            int v = targets[e];
            int w = weights[e];

            // The graph is undirected, so every edge appears twice (u->v and v->u).
            // We only keep one copy by checking (u < v).
            if (u < v)
            {
                MSTEdge new_edge;
                new_edge.u = u;
                new_edge.v = v;
                new_edge.weight = w;

                edges.push_back(new_edge);
            }
        }
    }

    // 2. Sort the edges by weight (smallest first)
    sort(edges.begin(), edges.end(), compareEdges);

    // 3. Build the Minimum Spanning Tree
    DisjointSet dsu(V);

    MSTResult result;
    result.total_weight = 0;
    result.connected = false;

    for (int i = 0; i < (int)edges.size(); i++)
    {
        MSTEdge current_edge = edges[i];

        // If uniting the nodes doesn't create a cycle, add the edge to our MST
        if (dsu.unite(current_edge.u, current_edge.v) == true)
        {
            result.edges.push_back(current_edge);
            result.total_weight += current_edge.weight;

            // A spanning tree always has exactly (Vertices - 1) edges. Stop early.
            if ((int)result.edges.size() == V - 1)
            {
                break;
            }
        }
    }

    // 4. Check if the graph was fully connected
    if (V <= 1 || (int)result.edges.size() == V - 1)
    {
        result.connected = true;
    }

    return result;
}

// ============================================================
// PRIM'S ALGORITHM
// ============================================================
MSTResult MSTAlgorithms::prim(const CSRGraph &graph)
{
    int V = graph.getVertices();
    const vector<int> &offset = graph.getOffset();
    const vector<int> &targets = graph.getIntermediaries();
    const vector<int> &weights = graph.getWeights();

    MSTResult result;
    result.total_weight = 0;
    result.connected = false;

    if (V == 0)
    {
        return result;
    }

    // Arrays to track the best known weights and parents
    vector<int> key(V, GRAPH_INF);
    vector<int> parent(V, -1);
    vector<bool> in_tree(V, false);

    // Min-heap Priority Queue to always pick the smallest edge.
    // It stores pairs of (weight, vertex).
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Start at vertex 0
    key[0] = 0;
    pq.push(make_pair(0, 0));

    while (!pq.empty())
    {
        // Extract the node with the smallest weight
        int current_key = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // If we already added this node to the MST, skip it
        if (in_tree[u] == true)
        {
            continue;
        }

        // Ignore stale entries in the priority queue
        if (current_key != key[u])
        {
            continue;
        }

        // Mark the node as part of the tree
        in_tree[u] = true;

        // If this is not the starting node, record the edge
        if (parent[u] != -1)
        {
            MSTEdge edge;
            edge.u = parent[u];
            edge.v = u;
            edge.weight = key[u];

            result.edges.push_back(edge);
            result.total_weight += key[u];
        }

        // Check all neighbors of the current node
        for (int e = offset[u]; e < offset[u + 1]; e++)
        {
            int v = targets[e];
            int w = weights[e];

            // If neighbor is not in tree yet, and we found a cheaper way to reach it
            if (in_tree[v] == false && w < key[v])
            {
                key[v] = w;
                parent[v] = u;
                pq.push(make_pair(w, v));
            }
        }
    }

    // Check if we successfully connected all nodes
    if ((int)result.edges.size() == V - 1)
    {
        result.connected = true;
    }

    return result;
}