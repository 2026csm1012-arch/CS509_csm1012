#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
        input_list.ignore();

        char choice;
        cout << "Is the graph in " << filename << " weighted? (y/n): ";
        cin >> choice;
        bool is_weighted = (choice == 'y' || choice == 'Y');

        int* offset = new int[V + 1]();         // row_ptr
        int* Intermediataries = new int[2 * E]; // col_idx
        int* weight = new int[2 * E];           // optional weights

        

        string line;
        int last = 0;
        int neighbor_count = 0;
        int node_index = 0;

        while (getline(input_list, line)) {
            if (line.rfind("SOURCE", 0) == 0) break; // stop at SOURCE line

            stringstream node_details(line);
            node_details >> node_index >> neighbor_count;

            if (!is_weighted) {
                for (int i = last; i < last + neighbor_count; i++) {
                    node_details >> Intermediataries[i];
                }
            } else {
                for (int i = last; i < last + neighbor_count; i++) {
                    node_details >> Intermediataries[i] >> weight[i];
                }
            }

            last += neighbor_count;
            offset[node_index + 1] = last;
        }

        cout << "File: " << filename << "\n";
        cout << "offset: ";
        for (int i = 0; i < V; i++) cout << offset[i] << " ";
        cout << "\n Intermediataries: ";
        for (int i = 0; i < last; i++) cout << Intermediataries[i] << " ";
        cout << "\n\n";

        delete[] offset;
        delete[] Intermediataries;
        delete[] weight;
    }

    return 0;
}
