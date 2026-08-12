#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

const int INF = 1073741823; // or 1e9, 0x3f3f3f3f, INT_MAX

class CSRGraph
{
private:
    int V, E;
    bool is_weighted;
    vector<int> offset;
    vector<int> intermediaries;
    vector<int> weights;

public:
    CSRGraph(bool weighted = false) : V(0), E(0), is_weighted(weighted) {}

    bool loadFromFile(const string &filepath)
    {
        ifstream input_list(filepath);
        if (!input_list.is_open())
        {
            cerr << "Error: Could not open file " << filepath << endl;
            return false;
        }
        if (input_list.peek() == ifstream::traits_type::eof())
        {
            cerr << "Invalid input: File " << filepath << " is empty." << endl;
            return false;
        }

        input_list >> V >> E;
        string st;
        getline(input_list, st);

        offset.assign(V + 1, 0);
        intermediaries.clear();
        weights.clear();

        string line;
        int itm = 0;

        while (getline(input_list, line))
        {
            if (line.rfind("SOURCE", 0) == 0)
                break;

            stringstream node_details(line);
            int node_index, neighbor_count;
            node_details >> node_index >> neighbor_count;

            offset[node_index] = itm;

            for (int i = 0; i < neighbor_count; i++)
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
                itm++;
            }
        }
        offset[V] = itm;
        return true;
    }

    void print(const string &filename) const
    {
        cout << "File: " << filename << "\n";
        cout << "offset: ";
        for (int i : offset)
            cout << i << " ";
        cout << "\nneigh: ";
        for (int x : intermediaries)
            cout << x << " ";
        if (is_weighted)
        {
            cout << "\nweights: ";
            for (int w : weights)
                cout << w << " ";
        }
        cout << "\n\n";
    }

    // Getters
    int getVertices() const { return V; }
    int getEdges() const { return E; }
    const vector<int> &getOffset() const { return offset; }
    const vector<int> &getIntermediaries() const { return intermediaries; }
    const vector<int> &getWeights() const { return weights; }
    bool weighted() const { return is_weighted; }
};

class GraphAlgorithms
{
public:
    static vector<int> bellmanFord(const CSRGraph &graph, int source)
    {
        int V = graph.getVertices();
        const int INF = numeric_limits<int>::max() / 2;
        vector<int> dist(V, INF);
        dist[source] = 0;

        for (int i = 1; i < V; i++)
        {
            for (int u = 0; u < V; u++)
            {
                for (int j = graph.getOffset()[u]; j < graph.getOffset()[u + 1]; j++)
                {
                    int v = graph.getIntermediaries()[j];
                    int w = graph.weighted() ? graph.getWeights()[j] : 1;
                    if (dist[u] != INF && dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }
        return dist;
    }

    static vector<vector<int>> floydWarshall(const CSRGraph &graph)
    {
        int V = graph.getVertices();
        const int INF = numeric_limits<int>::max() / 2;
        vector<vector<int>> dist(V, vector<int>(V, INF));

        for (int i = 0; i < V; i++)
            dist[i][i] = 0;

        for (int u = 0; u < V; u++)
        {
            for (int j = graph.getOffset()[u]; j < graph.getOffset()[u + 1]; j++)
            {
                int v = graph.getIntermediaries()[j];
                int w = graph.weighted() ? graph.getWeights()[j] : 1;
                dist[u][v] = min(dist[u][v], w);
            }
        }

        for (int k = 0; k < V; k++)
            for (int i = 0; i < V; i++)
                for (int j = 0; j < V; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        return dist;
    }
};

int main()
{
    for (string filename : {"test (1).txt", "test (2).txt"})
    {
        char choice;
        cout << "Is the graph in " << filename << " weighted? (y/n): ";
        cin >> choice;
        bool is_weighted = (choice == 'y' || choice == 'Y');

        CSRGraph graph(is_weighted);
        int algo;
        cout << "want to runn bellmen ford or floyd warshal" << endl;

        cin >> algo;
        if (graph.loadFromFile("../tests/" + filename))
        {
            graph.print(filename);
            if (algo == 1)
            {

                cout << "Bellman-Ford from source 0:\n";
                cout << filename << endl;

                auto dist = GraphAlgorithms::bellmanFord(graph, 0);
                for (int i = 0; i < graph.getVertices(); i++)
                {
                    if (dist[i] == INF || dist[i] >= 1e9)
                    {
                        std::cout << "0 -> " << i << " = INF\n";
                    }
                    else
                    {
                        std::cout << "0 -> " << i << " = " << dist[i] << "\n";
                    }
                }
                // cout << "0 -> " << i << " = " << dist[i] << "\n";
            }
            else
            {
                cout << "\nFloyd-Warshall all pairs:\n";
                auto allPairs = GraphAlgorithms::floydWarshall(graph);
                for (int i = 0; i < graph.getVertices(); i++)
                {
                    for (int j = 0; j < graph.getVertices(); j++)
                    {
                        if (allPairs[i][j] >= numeric_limits<int>::max() / 2)
                            cout << "INF ";
                        else
                            cout << allPairs[i][j] << " ";
                    }
                    cout << "\n";
                }
            }
        }
    }
    return 0;
}
