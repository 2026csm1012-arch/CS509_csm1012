#include "MST.h"

#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank_value;

public:
    explicit DisjointSet(int n)
        : parent(n), rank_value(n, 0)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank_value[a] < rank_value[b])
            swap(a, b);

        parent[b] = a;

        if (rank_value[a] == rank_value[b])
            rank_value[a]++;

        return true;
    }
};

MSTResult MSTAlgorithms::kruskal(const CSRGraph &graph)
{
    const int V = graph.getVertices();
    const auto &offset = graph.getOffset();
    const auto &targets = graph.getIntermediaries();
    const auto &weights = graph.getWeights();

    // Per assignment timing rules, edge extraction and sorting
    // are intentionally inside the Kruskal routine.
    vector<MSTEdge> edges;
    edges.reserve(static_cast<size_t>(graph.getEdges()));

    for (int u = 0; u < V; ++u)
    {
        for (int e = offset[u]; e < offset[u + 1]; ++e)
        {
            const int v = targets[e];

            // MST input is undirected, so every edge occurs twice.
            // Keep one copy.
            if (u < v)
            {
                edges.push_back({u, v, weights[e]});
            }
        }
    }

    sort(edges.begin(), edges.end(),
         [](const MSTEdge &a, const MSTEdge &b)
         {
             if (a.weight != b.weight)
                 return a.weight < b.weight;

             if (a.u != b.u)
                 return a.u < b.u;

             return a.v < b.v;
         });

    DisjointSet dsu(V);

    MSTResult result{{}, 0, false};
    result.edges.reserve(static_cast<size_t>(V > 0 ? V - 1 : 0));

    for (const MSTEdge &edge : edges)
    {
        if (dsu.unite(edge.u, edge.v))
        {
            result.edges.push_back(edge);
            result.total_weight += edge.weight;

            if (static_cast<int>(result.edges.size()) == V - 1)
                break;
        }
    }

    result.connected = (V <= 1 ||
                        static_cast<int>(result.edges.size()) == V - 1);

    return result;
}

MSTResult MSTAlgorithms::prim(const CSRGraph &graph)
{
    const int V = graph.getVertices();
    const auto &offset = graph.getOffset();
    const auto &targets = graph.getIntermediaries();
    const auto &weights = graph.getWeights();

    MSTResult result{{}, 0, false};

    if (V == 0)
        return result;

    vector<int> key(V, GRAPH_INF);
    vector<int> parent(V, -1);
    vector<bool> in_tree(V, false);

    using HeapNode = pair<int, int>;
    priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode>> pq;

    // Assignment recommends vertex 0 for reproducibility.
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        auto [current_key, u] = pq.top();
        pq.pop();

        if (in_tree[u])
            continue;

        // Ignore stale priority-queue entries.
        if (current_key != key[u])
            continue;

        in_tree[u] = true;

        if (parent[u] != -1)
        {
            result.edges.push_back({parent[u], u, key[u]});
            result.total_weight += key[u];
        }

        for (int e = offset[u]; e < offset[u + 1]; ++e)
        {
            int v = targets[e];
            int w = weights[e];

            if (!in_tree[v] && w < key[v])
            {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    result.connected = (static_cast<int>(result.edges.size()) == V - 1);

    return result;
}
