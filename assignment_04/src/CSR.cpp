#include "CSR.h"
#include <stdexcept>

CSRGraph convertToCSR(const std::vector<std::vector<int>>& adj) {
    CSRGraph csr;
    csr.V = static_cast<int>(adj.size());
    csr.row_ptr.resize(csr.V + 1, 0);

    for (int u = 0; u < csr.V; ++u) {
        csr.row_ptr[u + 1] =
            csr.row_ptr[u] + static_cast<int>(adj[u].size());
    }

    csr.E = csr.row_ptr[csr.V];
    csr.col_idx.reserve(csr.E);

    for (const auto& neighbours : adj) {
        csr.col_idx.insert(csr.col_idx.end(),
                           neighbours.begin(), neighbours.end());
    }

    return csr;
}
