#include "GraphAlgo.h"
#include <iostream>
#include <vector>

using namespace std; 

// ====================================s========================
// BELLMAN-FORD ALGORITHM
// ============================================================
ShortestPathResult GraphAlgorithms::bellmanFord(const CSRGraph &graph, int source)
{
    int V = graph.getVertices();
    const vector<int> &offset = graph.getOffset();
    const vector<int> &targets = graph.getIntermediaries();
    const vector<int> &weights = graph.getWeights();
    bool weighted = graph.isWeighted();

    // Initialize all distances to infinity
    vector<int> dist(V, GRAPH_INF);
    dist[source] = 0;

    // Step 1: Relax all edges (V - 1) times
    for (int iter = 1; iter < V; iter++)
    {
        bool updated = false;

        for (int u = 0; u < V; u++)
        {
            // Skip this node if we haven't reached it yet
            if (dist[u] == GRAPH_INF)
            {
                continue;
            }

            // Check all edges leaving node 'u'
            for (int e = offset[u]; e < offset[u + 1]; e++)
            {
                int v = targets[e];

                int w;
                if (weighted == true)
                {
                    w = weights[e];
                }
                else
                {
                    w = 1;
                }

                // If we found a shorter path, update it
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
        }

        // If no distances were updated in this pass, we can stop early
        if (updated == false)
        {
            break;
        }
    }

    // Step 2: Check for negative weight cycles
    bool neg_cycle = false;
    for (int u = 0; u < V; u++)
    {
        if (dist[u] == GRAPH_INF)
            continue;

        for (int e = offset[u]; e < offset[u + 1]; e++)
        {
            int v = targets[e];
            int w;
            if (weighted == true)
            {
                w = weights[e];
            }
            else
            {
                w = 1;
            }

            if (dist[u] + w < dist[v])
            {
                neg_cycle = true;
                break;
            }
        }
        if (neg_cycle == true)
            break;
    }

    // Return the final result
    ShortestPathResult result;
    result.has_negative_cycle = neg_cycle;
    result.distances = dist;

    return result;
}

// ============================================================
// FLOYD-WARSHALL ALGORITHM (STANDARD)
// ============================================================
AllPairsResult GraphAlgorithms::floydWarshall(const CSRGraph &graph)
{
    int V = graph.getVertices();
    const vector<int> &offset = graph.getOffset();
    const vector<int> &targets = graph.getIntermediaries();
    const vector<int> &weights = graph.getWeights();
    bool weighted = graph.isWeighted();

    // Create a 2D matrix (V x V) filled with infinity
    vector<vector<int>> dist(V, vector<int>(V, GRAPH_INF));

    // The distance from any node to itself is 0
    for (int i = 0; i < V; i++)
    {
        dist[i][i] = 0;
    }

    // Step 1: Load direct edges from the CSR graph into the matrix
    for (int u = 0; u < V; u++)
    {
        for (int e = offset[u]; e < offset[u + 1]; e++)
        {
            int v = targets[e];
            int w;
            if (weighted == true)
            {
                w = weights[e];
            }
            else
            {
                w = 1;
            }

            // Set distance if it is smaller than what is already there
            if (w < dist[u][v])
            {
                dist[u][v] = w;
            }
        }
    }

    // Step 2: Floyd-Warshall Algorithm main loop
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {

                // Only process if paths actually exist
                if (dist[i][k] != GRAPH_INF && dist[k][j] != GRAPH_INF)
                {

                    int new_distance = dist[i][k] + dist[k][j];

                    if (new_distance < dist[i][j])
                    {
                        dist[i][j] = new_distance;
                    }
                }
            }
        }
    }

    // Step 3: Check for negative cycles (negative number on the diagonal)
    bool neg_cycle = false;
    for (int i = 0; i < V; i++)
    {
        if (dist[i][i] < 0)
        {
            neg_cycle = true;
            break;
        }
    }

    AllPairsResult result;
    result.has_negative_cycle = neg_cycle;
    result.distances = dist;

    return result;
}

// ============================================================
// FLOYD-WARSHALL ALGORITHM (BLOCKED CACHE-FRIENDLY)
// ============================================================
AllPairsResult GraphAlgorithms::block_floydWarshall(const CSRGraph &graph, int B)
{
    int V = graph.getVertices();
    const vector<int> &offset = graph.getOffset();
    const vector<int> &targets = graph.getIntermediaries();
    const vector<int> &weights = graph.getWeights();
    bool weighted = graph.isWeighted();

    // Create a 2D matrix (V x V) filled with infinity
    vector<vector<int>> dist(V, vector<int>(V, GRAPH_INF));

    // Distance to itself is 0
    for (int i = 0; i < V; i++)
    {
        dist[i][i] = 0;
    }

    // Step 1: Load direct edges
    for (int u = 0; u < V; u++)
    {
        for (int e = offset[u]; e < offset[u + 1]; e++)
        {
            int v = targets[e];
            int w;
            if (weighted == true)
            {
                w = weights[e];
            }
            else
            {
                w = 1;
            } 

            if (w < dist[u][v])
            {
                dist[u][v] = w;
            }
        }
    }

    // Step 2: Process the matrix in blocks of size 'B'
    for (int k = 0; k < V; ++k)
    {
        for (int ii = 0; ii < V; ii += B)
        {
            for (int jj = 0; jj < V; jj += B)
            {
                for (int i = ii; i < min(ii + B, V); i++)
                {
                    for (int j = jj; j < min(jj + B, V); j++)
                    {
                        if (dist[i][k] < GRAPH_INF && dist[k][j] < GRAPH_INF)
                        {
                            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }
        }
    }

    // Step 3: Check for negative cycles
    bool neg_cycle = false;
    for (int i = 0; i < V; i++)
    {
        if (dist[i][i] < 0)
        {
            neg_cycle = true;
            break;
        }
    }

    AllPairsResult result;
    result.has_negative_cycle = neg_cycle;
    result.distances = dist;

    return result;
}