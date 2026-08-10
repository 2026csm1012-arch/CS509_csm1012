#include "CSR.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CSRGraph::CSRGraph(bool weighted)
    : V(0), E(0), is_weighted(weighted), source_vertex(0) {}

bool CSRGraph::loadFromFile(const std::string &filepath)
{
    ifstream input_list(filepath);
    if (!input_list.is_open())
    {
        cerr << "Error: Could not open file " << filepath << "\n";
        return false;
    }

    if (input_list.peek() == ifstream::traits_type::eof())
    {
        cerr << "Error: File " << filepath << " is empty.\n";
        return false;
    }

    input_list >> V >> E;
    string dummy;
    getline(input_list, dummy);

    offset.assign(V + 1, 0);
    intermediaries.clear();
    weights.clear();

    string line;
    int edge_counter = 0;

    while (getline(input_list, line))
    {
        if (line.empty())
            continue;

        if (line.rfind("SOURCE", 0) == 0)
        {
            stringstream ss(line);
            string prefix;
            ss >> prefix >> source_vertex;
            break;
        }

        stringstream node_details(line);
        int node_index, neighbor_count;
        node_details >> node_index >> neighbor_count;

        offset[node_index] = edge_counter;

        for (int i = 0; i < neighbor_count; ++i)
        {
            int neighbor, w = 1;
            if (is_weighted)
            {
                node_details >> neighbor >> w;
                weights.push_back(w);
            }
            else
            {
                node_details >> neighbor;
            }
            intermediaries.push_back(neighbor);
            edge_counter++;
        }
    }

    offset[V] = edge_counter;
    return true;
}

void CSRGraph::printCSR() const
{
    cout << "--- CSR Representation ---\n";
    cout << "Vertices: " << V << ", Edges: " << E << ", Source: " << source_vertex << "\n";
    cout << "Offsets:        ";
    for (int i : offset)
        cout << i << " ";
    cout << "\nIntermediaries: ";
    for (int x : intermediaries)
        cout << x << " ";
    if (is_weighted)
    {
        cout << "\nWeights:        ";
        for (int w : weights)
            cout << w << " ";
    }
    cout << "\n--------------------------\n";
}