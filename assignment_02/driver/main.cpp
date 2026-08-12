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


// ============================================================
// BELLMAN-FORD EXPECTED OUTPUT
//
// Expected:
//
// Execution Time : 0.00792 ms
// Bellman-Ford Shortest Path Distances
// Source: 0
//
// 0 -> 0 : 0
// 0 -> 1 : 36
// ...
//
// We ignore execution time and headings.
// ============================================================

vector<string> readExpectedBellmanFord(
    const string &path)
{
    vector<string> result;

    ifstream file(path);

    if (!file)
        return result;

    string line;

    bool readingDistances = false;

    while (getline(file, line))
    {
        if (!line.empty() &&
            line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.rfind("Source:", 0) == 0)
        {
            readingDistances = true;
            continue;
        }

        if (!readingDistances)
            continue;

        if (line.empty())
            continue;

        result.push_back(line);
    }

    return result;
}


// ============================================================
// FLOYD-WARSHALL EXPECTED OUTPUT
//
// Expected:
//
// Execution Time : 0.030783 ms
// 0 33 31 ...
// 9 0 1 ...
//
// We ignore ONLY the execution time line.
// ============================================================

vector<string> readExpectedFloydWarshall(
    const string &path)
{
    vector<string> result;

    ifstream file(path);

    if (!file)
        return result;

    string line;

    while (getline(file, line))
    {
        if (!line.empty() &&
            line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.rfind("Execution Time", 0) == 0)
            continue;

        if (line.empty())
            continue;

        result.push_back(line);
    }

    return result;
}


// ============================================================
// GENERATE BELLMAN-FORD ACTUAL RESULT
// ============================================================

vector<string> generateBellmanFordResult(
    const ShortestPathResult &result,
    int source,
    int vertices)
{
    vector<string> actual;

    for (int i = 0;
         i < vertices;
         i++)
    {
        string line;

        if (result.distances[i] >= GRAPH_INF)
        {
            line =
                to_string(source) +
                " -> " +
                to_string(i) +
                " : INF";
        }
        else
        {
            line =
                to_string(source) +
                " -> " +
                to_string(i) +
                " : " +
                to_string(
                    result.distances[i]);
        }

        actual.push_back(line);
    }

    return actual;
}


// ============================================================
// GENERATE FLOYD-WARSHALL ACTUAL RESULT
// ============================================================

vector<string> generateFloydWarshallResult(
    const AllPairsResult &result,
    int vertices)
{
    vector<string> actual;

    for (int i = 0;
         i < vertices;
         i++)
    {
        string row;

        for (int j = 0;
             j < vertices;
             j++)
        {
            if (result.distances[i][j] >= GRAPH_INF)
            {
                row += "INF";
            }
            else
            {
                row +=
                    to_string(
                        result.distances[i][j]);
            }

            if (j != vertices - 1)
                row += " ";
        }

        actual.push_back(row);
    }

    return actual;
}


// ============================================================
// BELLMAN-FORD TEST
// ============================================================

void runBellmanFordTest(
    const string &testName)
{
    string inputPath =
        "tests/Bellman-Ford/" +
        testName +
        ".txt";

    string expectedPath =
        "expected/Bellman-Ford/" +
        testName +
        ".txt";


    CSRGraph graph(true);


    // --------------------------------------------------------
    // Load input
    // --------------------------------------------------------

    if (!graph.loadFromFile(inputPath))
    {
        cout << left
             << setw(18)
             << (testName + ".txt")
             << "ERROR: Invalid input file\n";

        return;
    }


    int source =
        graph.getSource();


    // --------------------------------------------------------
    // ONLY ALGORITHM IS TIMED
    // --------------------------------------------------------

    auto start =
        high_resolution_clock::now();

    ShortestPathResult result =
        GraphAlgorithms::bellmanFord(
            graph,
            source);

    auto stop =
        high_resolution_clock::now();


    double executionTime =
        duration<double, milli>(
            stop - start).count();


    // --------------------------------------------------------
    // Actual result
    // --------------------------------------------------------

    vector<string> actual;

    if (result.has_negative_cycle)
    {
        actual.push_back(
            "NEGATIVE_CYCLE");
    }
    else
    {
        actual =
            generateBellmanFordResult(
                result,
                source,
                graph.getVertices());
    }


    // --------------------------------------------------------
    // Expected result
    // --------------------------------------------------------

    vector<string> expected =
        readExpectedBellmanFord(
            expectedPath);


    bool pass =
        (actual == expected);


    // --------------------------------------------------------
    // Report
    // --------------------------------------------------------

    cout << left
         << setw(18)
         << (testName + ".txt")

         << setw(10)
         << graph.getVertices()

         << setw(10)
         << graph.getEdges()

         << setw(8)
         << source

         << setw(12)
         << (result.has_negative_cycle
                 ? "Yes"
                 : "No")

         << setw(14)
         << fixed
         << setprecision(5)
         << executionTime

         << (pass ? "PASS" : "FAIL")

         << "\n";
}


// ============================================================
// FLOYD-WARSHALL TEST
// ============================================================

void runFloydWarshallTest(
    const string &testName)
{
    string inputPath =
        "tests/Floyd-Warshall/" +
        testName +
        ".txt";

    string expectedPath =
        "expected/Floyd-Warshall/" +
        testName +
        ".txt";


    CSRGraph graph(true);


    // --------------------------------------------------------
    // IMPORTANT:
    // Floyd-Warshall input is an adjacency matrix.
    // --------------------------------------------------------

    if (!graph.loadMatrixFromFile(
            inputPath))
    {
        cout << left
             << setw(18)
             << (testName + ".txt")
             << "ERROR: Invalid matrix file\n";

        return;
    }


    // --------------------------------------------------------
    // ONLY ALGORITHM IS TIMED
    // --------------------------------------------------------

    auto start =
        high_resolution_clock::now();

    AllPairsResult result =
        GraphAlgorithms::floydWarshall(
            graph);

    auto stop =
        high_resolution_clock::now();


    double executionTime =
        duration<double, milli>(
            stop - start).count();


    // --------------------------------------------------------
    // Actual result
    // --------------------------------------------------------

    vector<string> actual;

    if (result.has_negative_cycle)
    {
        actual.push_back(
            "NEGATIVE_CYCLE");
    }
    else
    {
        actual =
            generateFloydWarshallResult(
                result,
                graph.getVertices());
    }


    // --------------------------------------------------------
    // Expected result
    // --------------------------------------------------------

    vector<string> expected =
        readExpectedFloydWarshall(
            expectedPath);


    bool pass =
        (actual == expected);


    // --------------------------------------------------------
    // Report
    // --------------------------------------------------------

    cout << left
         << setw(18)
         << (testName + ".txt")

         << setw(10)
         << graph.getVertices()

         << setw(10)
         << graph.getEdges()

         << setw(12)
         << (result.has_negative_cycle
                 ? "Yes"
                 : "No")

         << setw(14)
         << fixed
         << setprecision(5)
         << executionTime

         << (pass ? "PASS" : "FAIL")

         << "\n";
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    int choice;

    cout << "\n";
    cout << "1. Bellman-Ford\n";
    cout << "2. Floyd-Warshall\n\n";

    cout << "Choice: ";

    cin >> choice;


    // ========================================================
    // BELLMAN-FORD
    // ========================================================

    if (choice == 1)
    {
        cout << "\n";
        cout << "Bellman-Ford Results\n\n";

        cout << left
             << setw(18)
             << "Test File"

             << setw(10)
             << "Vertices"

             << setw(10)
             << "Edges"

             << setw(8)
             << "Source"

             << setw(12)
             << "Neg Cycle"

             << setw(14)
             << "Time(ms)"

             << "Status\n";

        cout << string(82, '-')
             << "\n";


        runBellmanFordTest("bf_10");

        runBellmanFordTest("bf_100");

        runBellmanFordTest("bf_10000");

        runBellmanFordTest("bf_50000");

        runBellmanFordTest("bf_100000");
    }


    // ========================================================
    // FLOYD-WARSHALL
    // ========================================================

    else if (choice == 2)
    {
        cout << "\n";
        cout << "Floyd-Warshall Results\n\n";

        cout << left
             << setw(18)
             << "Test File"

             << setw(10)
             << "Vertices"

             << setw(10)
             << "Edges"

             << setw(12)
             << "Neg Cycle"

             << setw(14)
             << "Time(ms)"

             << "Status\n";

        cout << string(74, '-')
             << "\n";


        runFloydWarshallTest("fw_10");

        runFloydWarshallTest("fw_100");

        runFloydWarshallTest("fw_500");

        runFloydWarshallTest("fw_1000");

        runFloydWarshallTest("fw_2000");
    }


    // ========================================================
    // INVALID
    // ========================================================

    else
    {
        cout << "Invalid choice.\n";
        return 1;
    }


    cout << "\n";
    cout << "All tests completed.\n";

    return 0;
}