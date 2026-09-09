#include "../src/CSR.h"
#include "../src/GraphAlgo.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// READ EXPECTED OUTPUT FILES

vector<string> readExpectedBellmanFord(const string &path)
{
    vector<string> result;
    ifstream file(path);
    string line;

    while (getline(file, line))
    {
        if (line == "" || line == "\r")
            continue;
        if (line.find("Execution Time") != string::npos)
            continue;
        if (line.find("Bellman-Ford Shortest") != string::npos)
            continue;

        result.push_back(line);
    }
    return result;
}

vector<string> readExpectedFloydWarshall(const string &path)
{
    vector<string> result;
    ifstream file(path);
    string line;

    while (getline(file, line))
    {
        if (line == "" || line == "\r")
            continue;
        if (line.find("Execution Time") != string::npos)
            continue;

        result.push_back(line);
    }
    return result;
}

// FORMAT ACTUAL RESULTS AS STRINGS

vector<string> generateBellmanFordResult(const ShortestPathResult &result, int source, int vertices)
{
    vector<string> actual;
    actual.push_back("Source: " + to_string(source));

    for (int i = 0; i < vertices; i++)
    {
        string line = to_string(source) + " -> " + to_string(i) + " : ";
        if (result.distances[i] >= GRAPH_INF)
        {
            line = line + "INF";
        }
        else
        {
            line = line + to_string(result.distances[i]);
        }
        actual.push_back(line);
    }
    return actual;
}

vector<string> generateFloydWarshallResult(const AllPairsResult &result, int vertices)
{
    vector<string> actual;

    for (int i = 0; i < vertices; i++)
    {
        string row = "";
        for (int j = 0; j < vertices; j++)
        {
            if (result.distances[i][j] >= GRAPH_INF)
            {
                row = row + "INF";
            }
            else
            {
                row = row + to_string(result.distances[i][j]);
            }
            if (j != vertices - 1)
                row = row + " ";
        }
        actual.push_back(row);
    }
    return actual;
}

// TEST RUNNERS
void runBellmanFordTest(const string &testName)
{
    string inputPath = "tests/Bellman-Ford/" + testName + ".txt";
    string expectedPath = "expected/Bellman-Ford/" + testName + ".txt";

    CSRGraph graph(true);
    bool isLoaded = graph.loadFromFile(inputPath);

    if (isLoaded == false)
    {
        cout << "Error: Cannot open file " << inputPath << "\n";
        return;
    }

    int source = graph.getSource();

    auto start = high_resolution_clock::now();
    ShortestPathResult result = GraphAlgorithms::bellmanFord(graph, source);
    auto stop = high_resolution_clock::now();
    double executionTime = duration<double, milli>(stop - start).count();

    vector<string> actual;
    if (result.has_negative_cycle == true)
    {
        actual.push_back("NEGATIVE_CYCLE");
    }
    else
    {
        actual = generateBellmanFordResult(result, source, graph.getVertices());
    }

    vector<string> expected = readExpectedBellmanFord(expectedPath);

    string passStatus = "FAIL";
    if (actual == expected)
        passStatus = "PASS";

    string negCycleStatus = "No";
    if (result.has_negative_cycle == true)
        negCycleStatus = "Yes";

    cout << left
         << setw(18) << (testName + ".txt")
         << setw(10) << graph.getVertices()
         << setw(10) << graph.getEdges()
         << setw(10) << source
         << setw(12) << negCycleStatus
         << setw(14) << fixed << setprecision(5) << executionTime
         << passStatus << "\n";
}

void runFloydWarshallTest(const string &testName)
{
    string inputPath = "tests/Floyd-Warshall/" + testName + ".txt";
    string expectedPath = "expected/Floyd-Warshall/" + testName + ".txt";

    CSRGraph graph(true);
    bool isLoaded = graph.loadMatrixFromFile(inputPath);

    if (isLoaded == false)
    {
        cout << "Error: Cannot open file " << inputPath << "\n";
        return;
    }

    auto start = high_resolution_clock::now();
    AllPairsResult result = GraphAlgorithms::floydWarshall(graph);
    auto stop = high_resolution_clock::now();
    double executionTime = duration<double, milli>(stop - start).count();

    vector<string> actual;
    if (result.has_negative_cycle == true)
    {
        actual.push_back("NEGATIVE_CYCLE");
    }
    else
    {
        actual = generateFloydWarshallResult(result, graph.getVertices());
    }

    vector<string> expected = readExpectedFloydWarshall(expectedPath);

    string passStatus = "FAIL";
    if (actual == expected)
        passStatus = "PASS";

    string negCycleStatus = "No";
    if (result.has_negative_cycle == true)
        negCycleStatus = "Yes";

    cout << left
         << setw(18) << (testName + ".txt")
         << setw(10) << graph.getVertices()
         << setw(10) << graph.getEdges()
         << setw(12) << negCycleStatus
         << setw(14) << fixed << setprecision(5) << executionTime
         << passStatus << "\n";
}

// NEW: Blocked Floyd-Warshall Test
void block_runFloydWarshallTest(const string &testName, int block)
{
    string inputPath = "tests/Floyd-Warshall/" + testName + ".txt";
    string expectedPath = "expected/Floyd-Warshall/" + testName + ".txt";

    CSRGraph graph(true);
    bool isLoaded = graph.loadMatrixFromFile(inputPath);

    if (isLoaded == false)
    {
        cout << left << setw(18) << (testName + ".txt") << "ERROR: Invalid matrix file\n";
        return;
    }

    auto start = high_resolution_clock::now();
    AllPairsResult result = GraphAlgorithms::block_floydWarshall(graph, block);
    auto stop = high_resolution_clock::now();
    double executionTime = duration<double, milli>(stop - start).count();

    vector<string> actual;
    if (result.has_negative_cycle == true)
    {
        actual.push_back("NEGATIVE_CYCLE");
    }
    else
    {
        actual = generateFloydWarshallResult(result, graph.getVertices());
    }

    vector<string> expected = readExpectedFloydWarshall(expectedPath);

    string passStatus = "FAIL";
    if (actual == expected)
        passStatus = "PASS";

    string negCycleStatus = "No";
    if (result.has_negative_cycle == true)
        negCycleStatus = "Yes";

    cout << left
         << setw(18) << (testName + ".txt")
         << setw(10) << block
         << setw(10) << graph.getVertices()
         << setw(10) << graph.getEdges()
         << setw(12) << negCycleStatus
         << setw(14) << fixed << setprecision(5) << executionTime
         << passStatus << "\n";
}

// MAIN MENU
int main()
{
    int choice;
    cout << "\n1. Bellman-Ford\n";
    cout << "2. Floyd-Warshall\n";
    cout << "3. Blocked Floyd-Warshall\n\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "\n";
        cout << left
             << setw(18) << "Test File"
             << setw(10) << "Vertices"
             << setw(10) << "Edges"
             << setw(10) << "Source"
             << setw(12) << "Neg Cycle"
             << setw(14) << "Time(ms)"
             << "Status\n";
        cout << string(80, '-') << "\n";

        runBellmanFordTest("bf_10");
        runBellmanFordTest("bf_100");
        runBellmanFordTest("bf_10000");
        runBellmanFordTest("bf_50000");
        runBellmanFordTest("bf_100000");
    }
    else if (choice == 2)
    {
        cout << "\n";
        cout << left
             << setw(18) << "Test File"
             << setw(10) << "Vertices"
             << setw(10) << "Edges"
             << setw(12) << "Neg Cycle"
             << setw(14) << "Time(ms)"
             << "Status\n";
        cout << string(70, '-') << "\n";

        runFloydWarshallTest("fw_10");
        runFloydWarshallTest("fw_100");
        runFloydWarshallTest("fw_500");
        runFloydWarshallTest("fw_1000");
        runFloydWarshallTest("fw_2000");
    }
    else if (choice == 3)
    {
        int blockSize;
        cout << "Enter block size (e.g., 32, 64): ";
        cin >> blockSize;

        cout << "\n";
        cout << left
             << setw(18) << "Test File"
             << setw(10) << "Block"
             << setw(10) << "Vertices"
             << setw(10) << "Edges"
             << setw(12) << "Neg Cycle"
             << setw(14) << "Time(ms)"
             << "Status\n";
        cout << string(80, '-') << "\n";

        block_runFloydWarshallTest("fw_10", blockSize);
        block_runFloydWarshallTest("fw_100", 2 * blockSize);
        block_runFloydWarshallTest("fw_500", 4 * blockSize);
        block_runFloydWarshallTest("fw_1000", 8 * blockSize);
        block_runFloydWarshallTest("fw_2000", 16 * blockSize);
    }
    else
    {
        cout << "Invalid choice.\n";
        return 1;
    }

    cout << "\nAll tests completed.\n";
    return 0;
}