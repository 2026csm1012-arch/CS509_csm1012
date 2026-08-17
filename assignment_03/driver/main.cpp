#include "../src/MST.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace chrono;

static bool readExpectedMST(
    const string &path,
    long long &expected_weight)
{
    ifstream file(path);

    if (!file)
        return false;

    string key;

    while (file >> key)
    {
        if (key == "EXPECTED_WEIGHT")
        {
            return static_cast<bool>(file >> expected_weight);
        }
    }

    return false;
}

static void runMSTTest(
    const string &test_name,
    int choice)
{
    const string input_path =
        "tests/MST/" + test_name + ".txt";

    const string expected_path =
        "expected/MST/" + test_name + ".txt";

    CSRGraph graph(true);

    // Read input file
    if (!graph.loadFromFile(input_path))
    {
        cout << test_name << " : FAIL\n";
        return;
    }

    // Read expected result
    long long expected_weight = 0;

    if (!readExpectedMST(expected_path, expected_weight))
    {
        cout << test_name << " : FAIL\n";
        return;
    }

    if (choice == 1)
    {
        auto start = high_resolution_clock::now();

        MSTResult result =
            MSTAlgorithms::prim(graph);

        auto stop = high_resolution_clock::now();

        double milliseconds =
            duration<double, milli>(stop - start).count();

        bool pass =
            result.connected &&
            result.total_weight == expected_weight;

        cout << test_name << " : "
             << (pass ? "PASS" : "FAIL")
             << " | Time: "
             << milliseconds
             << " ms\n";
    }
    else if (choice == 2)
    {
        auto start = high_resolution_clock::now();

        MSTResult result =
            MSTAlgorithms::kruskal(graph);

        auto stop = high_resolution_clock::now();

        double milliseconds =
            duration<double, milli>(stop - start).count();

        bool pass =
            result.connected &&
            result.total_weight == expected_weight;

        cout << test_name << " : "
             << (pass ? "PASS" : "FAIL")
             << " | Time: "
             << milliseconds
             << " ms\n";
    }
}

int main()
{
    int choice = 0;

    cout << "\n";
    cout << "CS509 - Assignment 3\n";
    cout << "===================\n\n";

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

    runMSTTest("mst_10", choice);
    runMSTTest("mst_100", choice);
    runMSTTest("mst_10000", choice);
    runMSTTest("mst_50000", choice);

    cout << "\nAll selected tests completed.\n";

    return 0;
}