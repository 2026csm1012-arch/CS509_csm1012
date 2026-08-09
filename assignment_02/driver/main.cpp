#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int V, E;

    for (string filename : {"test (1).txt", "test (2).txt", "test (3).txt", "test (4).txt", "test (5).txt"})
    {
        ifstream input_list("../tests/" + filename);

        if (!input_list.is_open())
        {
            cerr << "Error: Could not open file " << filename << endl;
            continue;
        }
        if (input_list.peek() == ifstream::traits_type::eof())
        {
            cerr << "Invalid input: File " << filename << " is empty." << endl;
            continue;
        }

        input_list >> V >> E;
        string st;
        getline(input_list, st);

        char choice;
        cout << "Is the graph in " << filename << " weighted? (y/n): ";
        cin >> choice;
        bool is_weighted = (choice == 'y' || choice == 'Y');

        // arrays
        vector<int> offset(V + 1);
        vector<int> intermediateries;
        vector<int> weights;

        // node list with neighbor starts
        string line;
        int itm = 0;

        while (getline(input_list, line))
        {
            if (line.rfind("SOURCE", 0) == 0)
            {
                break;
            }

            stringstream node_details(line);

            int node_index, neighbor_count;
            node_details >> node_index >> neighbor_count;
            cout << "offset: " << offset[node_index] << " node index: " << node_index << " node neighbor: " << neighbor_count << endl;

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
                cout << neighbor;
                intermediateries.push_back(neighbor);
                itm++;
            }
            cout << endl;
        }
        offset[V]=itm;

        cout << "File: " << filename << "\n";
        cout << "offset: ";
        for (int i : offset)
            cout << i << " ";
        cout << "\nneigh: ";
        for (int x : intermediateries)
            cout << x << " ";
        if (is_weighted)
        {
            cout << "\nweights: ";
            for (int w : weights)
                cout << w << " ";
        }
        cout << "\n\n";
    }

    return 0;
}
