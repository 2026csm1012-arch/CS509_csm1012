#include "algorithms.h"
#include <algorithm>
#include <vector>

using namespace std;

// ============================================================
// HELPER: SORT VERTICES BY DEGREE
// ============================================================
struct VertexDegree
{
    int id;
    int degree;
};

// Sorts largest degree first (Welsh-Powell rule). Tie-breaker by ID.
bool compareDegree(const VertexDegree &a, const VertexDegree &b)
{
    if (a.degree != b.degree)
    {
        return a.degree > b.degree;
    }
    return a.id < b.id;
}

// ============================================================
// GREEDY VERTEX COLORING ALGORITHM
// ============================================================
ColoringResult greedyColoring(const CSRGraph &graph)
{
    ColoringResult result;

    // Grab the private variables using the getter functions
    int V = graph.getVertices();
    const vector<int> &offset = graph.getOffset();
    const vector<int> &intermediaries = graph.getIntermediaries();

    // Start with all vertices uncolored (-1)
    result.color.assign(V, -1);

    // 1. Calculate the degree (number of edges) for every vertex
    vector<VertexDegree> vertices(V);
    for (int u = 0; u < V; u++)
    {
        vertices[u].id = u;
        vertices[u].degree = offset[u + 1] - offset[u];
    }

    // 2. Sort vertices by degree (highest to lowest)
    sort(vertices.begin(), vertices.end(), compareDegree);

    // 3. Array to keep track of colors used by neighbors
    // used_color[c] = u means color 'c' is currently used by a neighbor of vertex 'u'
    vector<int> used_color(V + 1, -1);
    int max_colors_used = 0;

    // 4. Color each vertex one by one
    for (int i = 0; i < V; i++)
    {
        int u = vertices[i].id;

        // Mark the colors used by all neighbors of u
        for (int p = offset[u]; p < offset[u + 1]; p++)
        {
            int neighbor = intermediaries[p];
            int neighbor_color = result.color[neighbor];

            if (neighbor_color != -1)
            {
                used_color[neighbor_color] = u;
            }
        }

        // Find the first available color (0, 1, 2...)
        int chosen_color = 0;
        while (used_color[chosen_color] == u)
        {
            chosen_color++;
        }

        // Assign the color and track the highest color number used
        result.color[u] = chosen_color;

        if (chosen_color + 1 > max_colors_used)
        {
            max_colors_used = chosen_color + 1;
        }
    }

    result.colorsUsed = max_colors_used;
    result.valid = true;

    // 5. Verify the coloring is correct (no neighbors share a color)
    for (int u = 0; u < V; u++)
    {
        for (int p = offset[u]; p < offset[u + 1]; p++)
        {
            int neighbor = intermediaries[p];
            if (result.color[u] == result.color[neighbor])
            {
                result.valid = false;
            }
        }
    }

    return result;
}