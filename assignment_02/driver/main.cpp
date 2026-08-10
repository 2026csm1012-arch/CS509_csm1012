#include "../src/CSR.h"
#include "../src/GraphAlgo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;

// Helper to trim trailing spaces and carriage returns (\r) from string
string trimTrailing(const string &str)
{
    string s = str;
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r'))
    {
        s.pop_back();
    }
    return s;
}

vector<string> readExpectedOutput(const string &filepath)
{
    vector<string> lines;
    ifstream file(filepath);
    string line;
    while (getline(file, line))
    {
        string trimmed = trimTrailing(line);
        if (!trimmed.empty())
            lines.push_back(trimmed);
    }
    return lines;
}

void runTestCase(const string &testBaseName, bool isWeighted, int algoChoice)
{
    string inputPath = "tests/" + testBaseName + ".txt";
    string algoSubfolder = (algoChoice == 1) ? "Bellman-Ford" : "Floyd-Warshall";
    string expectedPath = "tests/" + algoSubfolder + "/" + testBaseName + "_expected.txt";

    CSRGraph graph(isWeighted);

    // 1. Time graph loading
    auto loadStart = chrono::high_resolution_clock::now();
    if (!graph.loadFromFile(inputPath))
    {
        cerr << "Failed to load " << inputPath << "\n";
        return;
    }
    auto loadEnd = chrono::high_resolution_clock::now();
    double loadTime = chrono::duration<double, milli>(loadEnd - loadStart).count();

    // 2. Time algorithm execution
    auto algoStart = chrono::high_resolution_clock::now();
    vector<string> actualOutput;

    if (algoChoice == 1)
    { // Bellman-Ford
        int source = graph.getSource();
        auto result = GraphAlgorithms::bellmanFord(graph, source);
        auto algoEnd = chrono::high_resolution_clock::now();
        double algoTime = chrono::duration<double, milli>(algoEnd - algoStart).count();

        cout << "\n----------------------------------------\n";
        cout << "Test: " << testBaseName << ".txt | Algorithm: Bellman-Ford\n";
        cout << "Load Time: " << fixed << setprecision(3) << loadTime << " ms | ";
        cout << "Execution Time: " << fixed << setprecision(3) << algoTime << " ms\n";

        if (result.has_negative_cycle)
        {
            actualOutput.push_back("NEGATIVE_CYCLE");
        }
        else
        {
            for (int i = 0; i < graph.getVertices(); ++i)
            {
                if (result.distances[i] >= GRAPH_INF)
                {
                    actualOutput.push_back(trimTrailing(to_string(source) + " -> " + to_string(i) + " = INF"));
                }
                else
                {
                    actualOutput.push_back(trimTrailing(to_string(source) + " -> " + to_string(i) + " = " + to_string(result.distances[i])));
                }
            }
        }
    }
    else if (algoChoice == 2)
    { // Floyd-Warshall
        auto result = GraphAlgorithms::floydWarshall(graph);
        auto algoEnd = chrono::high_resolution_clock::now();
        double algoTime = chrono::duration<double, milli>(algoEnd - algoStart).count();

        cout << "\n----------------------------------------\n";
        cout << "Test: " << testBaseName << ".txt | Algorithm: Floyd-Warshall\n";
        cout << "Load Time: " << fixed << setprecision(3) << loadTime << " ms | ";
        cout << "Execution Time: " << fixed << setprecision(3) << algoTime << " ms\n";

        if (result.has_negative_cycle)
        {
            actualOutput.push_back("NEGATIVE_CYCLE");
        }
        else
        {
            for (int i = 0; i < graph.getVertices(); ++i)
            {
                string row = "";
                for (int j = 0; j < graph.getVertices(); ++j)
                {
                    if (result.distances[i][j] >= GRAPH_INF)
                        row += "INF ";
                    else
                        row += to_string(result.distances[i][j]) + " ";
                }
                actualOutput.push_back(trimTrailing(row));
            }
        }
    }

    // 3. Verification step
    vector<string> expectedOutput = readExpectedOutput(expectedPath);
    if (!expectedOutput.empty())
    {
        bool match = (actualOutput == expectedOutput);
        cout << "Verification: [" << (match ? "PASSED" : "FAILED") << "]\n";
    }
    else
    {
        cout << "Verification: [NO EXPECTED FILE FOUND]\n";
    }
    cout << "----------------------------------------\n";
}

int main()
{
    vector<string> testBases = {"test1", "test2", "test3", "test4", "test5"};

    int algoChoice;
    cout << "Select Algorithm:\n1. Bellman-Ford\n2. Floyd-Warshall\nChoice: ";
    cin >> algoChoice;

    char isWeightedChar;
    cout << "Are graphs weighted? (y/n): ";
    cin >> isWeightedChar;
    bool isWeighted = (isWeightedChar == 'y' || isWeightedChar == 'Y');

    for (const auto &testName : testBases)
    {
        runTestCase(testName, isWeighted, algoChoice);
    }

    return 0;
}