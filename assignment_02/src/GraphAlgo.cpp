#include "GraphAlgo.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>

using namespace std;

ShortestPathResult GraphAlgorithms::bellmanFord(const CSRGraph &graph, int source)
{
    int V = graph.getVertices();
    const auto &offset = graph.getOffset();
    const auto &targets = graph.getIntermediaries();
    const auto &weights = graph.getWeights();
    bool weighted = graph.isWeighted();

    vector<int> dist(V, GRAPH_INF);
    dist[source] = 0;

    for (int iter = 1; iter < V; ++iter)
    {
        bool updated = false;
        for (int u = 0; u < V; ++u)
        {
            if (dist[u] == GRAPH_INF)
                continue;

            for (int e = offset[u]; e < offset[u + 1]; ++e)
            {
                int v = targets[e];
                int w = weighted ? weights[e] : 1;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
        }
        if (!updated)
            break;
    }

    bool neg_cycle = false;
    for (int u = 0; u < V; ++u)
    {
        if (dist[u] == GRAPH_INF)
            continue;

        for (int e = offset[u]; e < offset[u + 1]; ++e)
        {
            int v = targets[e];
            int w = weighted ? weights[e] : 1;

            if (dist[u] + w < dist[v])
            {
                neg_cycle = true;
                break;
            }
        }
        if (neg_cycle)
            break;
    }

    return {neg_cycle, dist};
}

AllPairsResult GraphAlgorithms::floydWarshall(const CSRGraph &graph)
{
    int V = graph.getVertices();
    const auto &offset = graph.getOffset();
    const auto &targets = graph.getIntermediaries();
    const auto &weights = graph.getWeights();
    bool weighted = graph.isWeighted();

    vector<vector<int>> dist(V, vector<int>(V, GRAPH_INF));

    for (int i = 0; i < V; ++i)
    {
        dist[i][i] = 0;
    }

    for (int u = 0; u < V; ++u)
    {
        for (int e = offset[u]; e < offset[u + 1]; ++e)
        {
            int v = targets[e];
            int w = weighted ? weights[e] : 1;
            dist[u][v] = min(dist[u][v], w);
        }
    }

    for (int k = 0; k < V; ++k)
    {
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                if (dist[i][k] < GRAPH_INF && dist[k][j] < GRAPH_INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    bool neg_cycle = false;
    for (int i = 0; i < V; ++i)
    {
        if (dist[i][i] < 0)
        {
            neg_cycle = true;
            break;
        }
    }

    // Printing the 2D dist vector as a matrix
    // for (int i = 0; i < V; ++i) {
    //     for (int j = 0; j < V; ++j) {
    //         if (dist[i][j] >= GRAPH_INF) {
    //             std::cout << "INF";
    //         } else {
    //             std::cout << dist[i][j];
    //         }

    //         // Add space separator between elements, but skip at the end of the line
    //         if (j < V - 1) {
    //             std::cout << " ";
    //         }
    //     }
    //     std::cout << "\n";
    // }

    return {neg_cycle, dist};
}