#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int V, E;

    for (string filename : {"test (1).txt", "test (2).txt", "test (3).txt", "test (4).txt", "test (5).txt"}) {
        ifstream input_list("../tests/" + filename);

        if (!input_list.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            continue;
        }
        if (input_list.peek() == ifstream::traits_type::eof()) {
            cerr << "Invalid input: File " << filename << " is empty." << endl;
            continue;
        }

        input_list >> V >> E;

        char choice;
        cout << "Is the graph in " << filename << " weighted? (y/n): ";
        cin >> choice;
        bool is_weighted = (choice == 'y' || choice == 'Y');

        vector<int> row_ptr(V + 1, 0);
        vector<int> col_idx;
        vector<int> weights;

        string line;
        int last = 0;

        while (getline(input_list, line)) {
            if (line.rfind("SOURCE", 0) == 0) break; // stop at SOURCE line

            stringstream node_details(line);
            int node_index, neighbor_count;
            node_details >> node_index >> neighbor_count;

            for (int i = 0; i < neighbor_count; i++) {
                int neighbor, w = 1;
                if (is_weighted) {
                    node_details >> neighbor >> w;
                    weights.push_back(w);
                } else {
                    node_details >> neighbor;
                }
                col_idx.push_back(neighbor);
            }

            last += neighbor_count;
            row_ptr[node_index + 1] = last;
        }

        cout << "File: " << filename << "\n";
        cout << "row_ptr: ";
        for (int i = 0; i <= V; i++) cout << row_ptr[i] << " ";
        cout << "\ncol_idx: ";
        for (int x : col_idx) cout << x << " ";
        if (is_weighted) {
            cout << "\nweights: ";
            for (int w : weights) cout << w << " ";
        }
        cout << "\n\n";
    }

    return 0;
}
