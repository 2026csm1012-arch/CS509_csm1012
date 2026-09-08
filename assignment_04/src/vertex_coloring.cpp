#include "algorithms.h"
#include <algorithm>
#include <numeric>

ColoringResult greedyColoring(const CSRGraph& graph) {
    ColoringResult r;
    r.color.assign(graph.V, -1);

    std::vector<int> degree(graph.V);
    for (int u = 0; u < graph.V; ++u)
        degree[u] = graph.row_ptr[u + 1] - graph.row_ptr[u];

    std::vector<int> order(graph.V);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        if (degree[a] != degree[b]) return degree[a] > degree[b];
        return a < b;
    });

    std::vector<int> used(graph.V + 1, -1);
    int stamp = 0;
    int colors = 0;

    for (int u : order) {
        ++stamp;
        for (int p = graph.row_ptr[u]; p < graph.row_ptr[u + 1]; ++p) {
            int v = graph.col_idx[p];
            if (r.color[v] >= 0) used[r.color[v]] = stamp;
        }
        int c = 0;
        while (used[c] == stamp) ++c;
        r.color[u] = c;
        colors = std::max(colors, c + 1);
    }

    r.colorsUsed = colors;
    r.valid = true;
    for (int u = 0; u < graph.V; ++u)
        for (int p = graph.row_ptr[u]; p < graph.row_ptr[u + 1]; ++p)
            if (r.color[u] == r.color[graph.col_idx[p]]) r.valid = false;
    return r;
}
