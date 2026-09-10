#include "CSR.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ============================================================
// CONSTRUCTOR
// ============================================================
CSRGraph::CSRGraph(bool weighted)
{
    V = 0;
    E = 0;
    is_weighted = weighted;
    source_vertex = 0;
}

// ============================================================
// LOAD BELLMAN-FORD FILE (Supports both Adjacency List & Edge List)
// ============================================================
bool CSRGraph::loadFromFile(const string &filepath)
{
    ifstream input(filepath);

    if (input.is_open() == false)
    {
        cout << "Error: Cannot open file " << filepath << "\n";
        return false;
    }

    string line;

    // 1. Read the very first line to determine the format
    getline(input, line);

    // Clean up carriage returns if they exist
    if (!line.empty() && line.back() == '\r')
    {
        line.pop_back();
    }

    // ------------------------------------------------------------
    // FORMAT A: EDGE LIST (Starts with 'D' for Directed or 'U' for Undirected)
    // ------------------------------------------------------------
    if (line == "D" || line == "U")
    {
        bool is_directed = true;
        if (line == "U")
        {
            is_directed = false;
        }

        // Temporary 2D vectors to group edges because we don't know the total nodes yet
        vector<vector<int>> temp_neighbors;
        vector<vector<int>> temp_weights;
        int total_edges = 0;
        source_vertex = 0;

        while (getline(input, line))
        {
            if (line == "" || line == "\r")
                continue;

            if (line.find("SOURCE") != string::npos)
            {
                stringstream ss(line);
                string temp;
                ss >> temp >> source_vertex;
                break;
            }

            stringstream edgeData(line);
            int u, v;
            int w = 1;

            if (is_weighted == true)
            {
                edgeData >> u >> v >> w;
            }
            else
            {
                edgeData >> u >> v;
            }

            // Find the highest node number to size our lists
            int max_node = u;
            if (v > max_node)
                max_node = v;

            int required_size = max_node + 1;

            // Added (int) cast to fix signedness warning
            if (required_size > (int)temp_neighbors.size())
            {
                temp_neighbors.resize(required_size);
                temp_weights.resize(required_size);
            }

            // Store edge u -> v
            temp_neighbors[u].push_back(v);
            temp_weights[u].push_back(w);
            total_edges++;

            // If undirected, store v -> u
            if (is_directed == false)
            {
                temp_neighbors[v].push_back(u);
                temp_weights[v].push_back(w);
                total_edges++;
            }
        }

        // Build the final CSR arrays
        V = temp_neighbors.size();
        E = total_edges;
        offset.assign(V + 1, 0);
        intermediaries.clear();
        weights.clear();

        int edge_counter = 0;
        for (int i = 0; i < V; i++)
        {
            offset[i] = edge_counter;

            // Added (int) cast to fix signedness warning
            for (int j = 0; j < (int)temp_neighbors[i].size(); j++)
            {
                intermediaries.push_back(temp_neighbors[i][j]);
                weights.push_back(temp_weights[i][j]);
                edge_counter++;
            }
        }
        offset[V] = edge_counter;
        return true;
    }

    // ------------------------------------------------------------
    // FORMAT B: ADJACENCY LIST (Starts with "Vertices Edges")
    // ------------------------------------------------------------
    else
    {
        stringstream firstLine(line);
        firstLine >> V >> E;

        offset.assign(V + 1, 0);
        intermediaries.clear();
        weights.clear();
        source_vertex = 0;

        int edge_counter = 0;

        while (getline(input, line))
        {
            if (line == "" || line == "\r")
                continue;

            if (line.find("SOURCE") != string::npos)
            {
                stringstream ss(line);
                string temp;
                ss >> temp >> source_vertex;
                break;
            }

            stringstream nodeData(line);
            int node_index;
            int neighbor_count;

            nodeData >> node_index >> neighbor_count;
            offset[node_index] = edge_counter;

            for (int i = 0; i < neighbor_count; i++)
            {
                int neighbor;
                int weight = 1;

                if (is_weighted == true)
                {
                    nodeData >> neighbor >> weight;
                    weights.push_back(weight);
                }
                else
                {
                    nodeData >> neighbor;
                }

                intermediaries.push_back(neighbor);
                edge_counter++;
            }
        }

        offset[V] = edge_counter;
        return true;
    }
}

// ============================================================
// LOAD FLOYD-WARSHALL MATRIX FILE
// ============================================================
bool CSRGraph::loadMatrixFromFile(const string &filepath)
{
    ifstream input(filepath);

    if (input.is_open() == false)
    {
        cout << "Error: Cannot open file " << filepath << "\n";
        return false;
    }

    input >> V;

    if (V <= 0)
    {
        cout << "Error: Invalid number of vertices.\n";
        return false;
    }

    offset.assign(V + 1, 0);
    intermediaries.clear();
    weights.clear();
    E = 0;
    source_vertex = 0;

    for (int i = 0; i < V; i++)
    {
        offset[i] = intermediaries.size();

        for (int j = 0; j < V; j++)
        {
            string value;
            input >> value;

            if (value == "INF")
                continue;
            if (i == j)
                continue; // Skip diagonal

            int weight = stoi(value);

            intermediaries.push_back(j);
            weights.push_back(weight);
            E++;
        }
    }

    offset[V] = intermediaries.size();
    return true;
}

// ============================================================
// PRINT CSR DATA
// ============================================================
void CSRGraph::printCSR() const
{
    cout << "\n--- CSR Data ---\n";
    cout << "Vertices: " << V << ", Edges: " << E << ", Source: " << source_vertex << "\n";

    cout << "Offsets:        ";
    for (int i = 0; i < (int)offset.size(); i++)
    {
        cout << offset[i] << " ";
    }
    cout << "\n";

    cout << "Intermediaries: ";
    for (int i = 0; i < (int)intermediaries.size(); i++)
    {
        cout << intermediaries[i] << " ";
    }
    cout << "\n";

    if (is_weighted == true)
    {
        cout << "Weights:        ";
        for (int i = 0; i < (int)weights.size(); i++)
        {
            cout << weights[i] << " ";
        }
        cout << "\n";
    }

    cout << "----------------\n";
}

// ============================================================
// CONVERT ADJACENCY LIST TO CSR FORMAT (For Assignment 4)
// ============================================================
CSRGraph convertToCSR(const vector<vector<int>> &adj)
{
    CSRGraph csr(false); // Assignment 4 uses unweighted graphs by default

    csr.V = (int)adj.size();
    csr.offset.assign(csr.V + 1, 0);

    int edge_counter = 0;

    for (int i = 0; i < csr.V; i++)
    {
        csr.offset[i] = edge_counter;

        for (int j = 0; j < (int)adj[i].size(); j++)
        {
            csr.intermediaries.push_back(adj[i][j]);
            edge_counter++;
        }
    }

    csr.offset[csr.V] = edge_counter;
    csr.E = edge_counter;

    return csr;
}