#include "algorithms.h"
#include <vector>

using namespace std;

// ============================================================
// PAGERANK ALGORITHM
// ============================================================
PageRankResult pageRank(const CSRGraph& graph, double damping, double tolerance, int maxIterations) {
    PageRankResult result;
    
    // Grab the private variables using the getter functions
    int V = graph.getVertices();
    const vector<int>& offset = graph.getOffset();
    const vector<int>& intermediaries = graph.getIntermediaries();
    
    // Start everyone with an equal PageRank score (1.0 / Vertices)
    result.rank.assign(V, 1.0 / V);
    result.iterations = 0;
    result.converged = false;

    vector<double> next_rank(V, 0.0);
    vector<int> out_degree(V, 0);
    
    // 1. Calculate how many outgoing edges each vertex has
    for (int u = 0; u < V; u++) {
        out_degree[u] = offset[u + 1] - offset[u];
    }

    // 2. Run the main PageRank loop
    for (int iter = 1; iter <= maxIterations; iter++) {
        
        // Base score everyone gets just for existing (teleportation)
        double base_score = (1.0 - damping) / V;
        for (int i = 0; i < V; i++) {
            next_rank[i] = base_score;
        }

        double dangling_mass = 0.0;
        
        // Distribute PageRank scores to neighbors
        for (int u = 0; u < V; u++) {
            
            // If a node has no outgoing edges, its score gets pooled
            if (out_degree[u] == 0) {
                dangling_mass += result.rank[u];
            } 
            else {
                // Otherwise, share the score equally among all neighbors
                double share = damping * result.rank[u] / out_degree[u];
                
                for (int p = offset[u]; p < offset[u + 1]; p++) {
                    int neighbor = intermediaries[p];
                    next_rank[neighbor] += share;
                }
            }
        }

        // Distribute the pooled score from dead-end nodes equally to everyone
        double dangling_share = damping * dangling_mass / V;
        for (int i = 0; i < V; i++) {
            next_rank[i] += dangling_share;
        }

        // 3. Check how much the scores changed to see if we can stop early
        double total_change = 0.0;
        for (int i = 0; i < V; i++) {
            double change = next_rank[i] - result.rank[i];
            
            // Make it positive (absolute value)
            if (change < 0) {
                change = -change; 
            }
            total_change += change;
        }

        // 4. Update the actual ranks for the next round
        for (int i = 0; i < V; i++) {
            result.rank[i] = next_rank[i];
        }
        
        result.iterations = iter;
        
        // If the scores barely changed, we are done!
        if (total_change <= tolerance) {
            result.converged = true;
            break;
        }
    }
    
    return result;
}