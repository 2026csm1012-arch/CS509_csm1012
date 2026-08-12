#include "CSR.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CSRGraph::CSRGraph(bool weighted)
    : V(0),
      E(0),
      is_weighted(weighted),
      source_vertex(0)
{
}


// ============================================================
// BELLMAN-FORD INPUT
//
// Format:
//
// V E
// vertex neighbour_count neighbour weight ...
// ...
// SOURCE source
// ============================================================

bool CSRGraph::loadFromFile(const string &filepath)
{
    ifstream input_list(filepath);

    if (!input_list.is_open())
    {
        cerr << "Error: Could not open file "
             << filepath << "\n";

        return false;
    }

    if (input_list.peek() == ifstream::traits_type::eof())
    {
        cerr << "Error: File "
             << filepath
             << " is empty.\n";

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

        int node_index;
        int neighbor_count;

        node_details >>
            node_index >>
            neighbor_count;

        offset[node_index] =
            edge_counter;

        for (int i = 0;
             i < neighbor_count;
             ++i)
        {
            int neighbor;
            int w = 1;

            if (is_weighted)
            {
                node_details >>
                    neighbor >>
                    w;

                weights.push_back(w);
            }
            else
            {
                node_details >>
                    neighbor;
            }

            intermediaries.push_back(
                neighbor);

            edge_counter++;
        }
    }

    offset[V] =
        edge_counter;

    return true;
}


// ============================================================
// FLOYD-WARSHALL INPUT
//
// Format:
//
// V
// 0 INF 5 INF ...
// INF 0 2  ...
// ...
//
// The matrix is converted into CSR.
//
// INF means there is no edge.
//
// Diagonal values are not stored as edges.
// ============================================================

bool CSRGraph::loadMatrixFromFile(
    const string &filepath)
{
    ifstream input(filepath);

    if (!input.is_open())
    {
        cerr << "Error: Could not open file "
             << filepath << "\n";

        return false;
    }

    if (!(input >> V))
    {
        cerr << "Error: Invalid matrix file "
             << filepath << "\n";

        return false;
    }

    if (V <= 0)
    {
        cerr << "Error: Invalid number of vertices.\n";

        return false;
    }

    offset.assign(V + 1, 0);

    intermediaries.clear();
    weights.clear();

    E = 0;
    source_vertex = 0;

    // --------------------------------------------------------
    // Read matrix
    // --------------------------------------------------------

    for (int i = 0; i < V; ++i)
    {
        offset[i] =
            static_cast<int>(
                intermediaries.size());

        for (int j = 0; j < V; ++j)
        {
            string value;

            if (!(input >> value))
            {
                cerr << "Error: Matrix in "
                     << filepath
                     << " is incomplete.\n";

                return false;
            }

            // No edge
            if (value == "INF")
                continue;

            int weight;

            try
            {
                weight = stoi(value);
            }
            catch (...)
            {
                cerr << "Error: Invalid matrix value '"
                     << value
                     << "' in "
                     << filepath
                     << "\n";

                return false;
            }

            // Don't store diagonal.
            // Floyd-Warshall itself initializes
            // dist[i][i] = 0.
            if (i == j)
                continue;

            intermediaries.push_back(j);

            weights.push_back(weight);

            E++;
        }
    }

    offset[V] =
        static_cast<int>(
            intermediaries.size());

    return true;
}


// ============================================================
// PRINT CSR
// ============================================================

void CSRGraph::printCSR() const
{
    cout << "--- CSR Representation ---\n";

    cout << "Vertices: "
         << V
         << ", Edges: "
         << E
         << ", Source: "
         << source_vertex
         << "\n";

    cout << "Offsets:        ";

    for (int i : offset)
        cout << i << " ";

    cout << "\n";

    cout << "Intermediaries: ";

    for (int x : intermediaries)
        cout << x << " ";

    if (is_weighted)
    {
        cout << "\nWeights:        ";

        for (int w : weights)
            cout << w << " ";
    }

    cout << "\n";

    cout << "--------------------------\n";
}