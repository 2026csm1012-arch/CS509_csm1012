#include "../src/MST.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace chrono;

// ============================================================
// HELPER: READ EXPECTED WEIGHT
// ============================================================
bool readExpectedMST(const string &path, long long &expected_weight)
{
    ifstream file(path);

    if (file.is_open() == false)
    {
        return false;
    }

    string key;

    // Read the file word by word
    while (file >> key)
    {
        // Look for the exact text "EXPECTED_WEIGHT"
        if (key == "EXPECTED_WEIGHT")
        {
            file >> expected_weight;
            return true;
        }
    }

    return false;
}

// ============================================================
// HELPER: RUN TEST
// ============================================================
void runMSTTest(const string &test_name, int choice)
{
    // 1. Setup file paths
    string input_path = "tests/MST/" + test_name + ".txt";
    string expected_path = "expected/MST/" + test_name + ".txt";

    // 2. Load the graph (true means the graph has weights)
    CSRGraph graph(true);
    bool is_loaded = graph.loadFromFile(input_path);

    if (is_loaded == false)
    {
        cout << test_name << " : FAIL (Could not open input file)\n";
        return;
    }

    // 3. Read the expected correct weight
    long long expected_weight = 0;
    bool has_expected = readExpectedMST(expected_path, expected_weight);

    if (has_expected == false)
    {
        cout << test_name << " : FAIL (Could not find expected weight file)\n";
        return;
    }

    // Variables to hold our algorithm's results
    // Variables to hold our algorithm's results
    MSTResult result;
    result.total_weight = 0;
    result.connected = false;

    double milliseconds = 0.0;
    string algo_name = "";
    string output_path = "";

    // 4. Run the chosen algorithm and time it
    if (choice == 1) // Prim
    {
        algo_name = "Prim's Algorithm";
        output_path = "output/MST/" + test_name + "_prim.txt";

        auto start = high_resolution_clock::now();
        result = MSTAlgorithms::prim(graph);
        auto stop = high_resolution_clock::now();

        milliseconds = duration<double, milli>(stop - start).count();
    }
    else if (choice == 2) // Kruskal
    {
        algo_name = "Kruskal's Algorithm";
        output_path = "output/MST/" + test_name + "_kruskal.txt";

        auto start = high_resolution_clock::now();
        result = MSTAlgorithms::kruskal(graph);
        auto stop = high_resolution_clock::now();

        milliseconds = duration<double, milli>(stop - start).count();
    }

    // 5. Check if our answer is correct
    bool pass = false;
    if (result.connected == true && result.total_weight == expected_weight)
    {
        pass = true;
    }

    // 6. Print result to the screen
    cout << test_name << " : ";
    if (pass == true)
    {
        cout << "PASS";
    }
    else
    {
        cout << "FAIL";
    }
    cout << " | Time: " << milliseconds << " ms\n";

    // 7. Save detailed results to an output file
    ofstream output(output_path);
    if (output.is_open() == true)
    {
        output << "Algorithm: " << algo_name << "\n";

        if (result.connected == true)
        {
            output << "Connected: YES\n";
        }
        else
        {
            output << "Connected: NO\n";
        }

        output << "Edges:\n";
        for (int i = 0; i < (int)result.edges.size(); i++)
        {
            MSTEdge current = result.edges[i];
            output << current.u << " " << current.v << " " << current.weight << "\n";
        }

        output << "Total MST weight: " << result.total_weight << "\n";
    }
}

// ============================================================
// MAIN MENU
// ============================================================
int main()
{
    int choice = 0;

    cout << "\n";
    cout << "CS509 - Assignment 3 (MST)\n";
    cout << "==========================\n\n";

    cout << "1. Prim's Algorithm\n";
    cout << "2. Kruskal's Algorithm\n\n";

    cout << "Choice: ";
    cin >> choice;

    if (choice != 1 && choice != 2)
    {
        cout << "Invalid choice.\n";
        return 1;
    }

    cout << "\n";

    if (choice == 1)
    {
        cout << "Running Prim's Algorithm\n";
    }
    else
    {
        cout << "Running Kruskal's Algorithm\n";
    }

    cout << "--------------------------\n";

    // Run tests
    runMSTTest("mst_10", choice);
    runMSTTest("mst_100", choice);
    runMSTTest("mst_10000", choice);
    runMSTTest("mst_50000", choice);

    cout << "\nAll selected tests completed.\n";

    return 0;
}