#include "algorithms.h"
#include <cmath>
#include <numeric>

PageRankResult pageRank(const CSRGraph& graph, double damping,
                        double tolerance, int maxIterations) {
    PageRankResult r;
    const int n = graph.V;
    r.rank.assign(n, 1.0 / n);
    r.iterations = 0;
    r.converged = false;

    std::vector<double> next(n, 0.0);
    std::vector<int> outdegree(n);
    for (int u = 0; u < n; ++u)
        outdegree[u] = graph.row_ptr[u + 1] - graph.row_ptr[u];

    for (int iter = 1; iter <= maxIterations; ++iter) {
        std::fill(next.begin(), next.end(), (1.0 - damping) / n);

        double danglingMass = 0.0;
        for (int u = 0; u < n; ++u) {
            if (outdegree[u] == 0) {
                danglingMass += r.rank[u];
            } else {
                double share = damping * r.rank[u] / outdegree[u];
                for (int p = graph.row_ptr[u]; p < graph.row_ptr[u + 1]; ++p)
                    next[graph.col_idx[p]] += share;
            }
        }

        double danglingShare = damping * danglingMass / n;
        for (double& x : next) x += danglingShare;

        double change = 0.0;
        for (int i = 0; i < n; ++i) change += std::fabs(next[i] - r.rank[i]);
        r.rank.swap(next);
        r.iterations = iter;
        if (change <= tolerance) {
            r.converged = true;
            break;
        }
    }
    return r;
}
