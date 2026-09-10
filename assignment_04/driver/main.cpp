#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <limits>
#include "../src/CSR.h"
#include "../src/graph_io.h"
#include "../src/algorithms.h"
#include "../src/output.h"

using namespace std;
namespace fs = std::filesystem;

// Helper to safely clear bad input
static void safeCinWait()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void runColoring()
{
    const string names[] = {
        "color_10.txt",
        "color_100.txt",
        "color_10000.txt",
        "color_50000.txt",
        "color_100000.txt"};

    string out_dir = "generated/vertex_coloring/";
    fs::create_directories(out_dir);

    cout << "\nRunning ALL Vertex Coloring Tests...\n";
    cout << string(50, '-') << "\n";

    for (int i = 0; i < 5; i++)
    {
        string name = names[i];
        cout << "Testing: " << name << "\n";

        string path = "tests/vertex_coloring/" + name;
        string out_path = out_dir + name;

        try
        {
            Graph g = readUnweightedGraph(path, true);
            CSRGraph csr = convertToCSR(g);

            auto start = chrono::high_resolution_clock::now();
            ColoringResult result = greedyColoring(csr);
            auto end = chrono::high_resolution_clock::now();

            double ms = chrono::duration<double, milli>(end - start).count();
            writeColoringOutput(out_path, result, ms);

            cout << "  Colors used : " << result.colorsUsed << "\n";
            cout << "  Valid       : " << (result.valid ? "true" : "false") << "\n";
            cout << "  Time        : " << fixed << setprecision(3) << ms << " ms\n";
        }
        catch (const exception &e)
        {
            cout << "  Error: " << e.what() << "\n";
        }
        cout << string(50, '-') << "\n";
    }
}

static void runPageRank()
{
    const string names[] = {
        "pagerank_10.txt",
        "pagerank_100.txt",
        "pagerank_1000.txt",
        "pagerank_10000.txt",
        "pagerank_50000.txt"};

    string out_dir = "generated/pagerank/";
    fs::create_directories(out_dir);

    cout << "\nRunning ALL PageRank Tests...\n";
    cout << string(50, '-') << "\n";

    for (int i = 0; i < 5; i++)
    {
        string name = names[i];
        cout << "Testing: " << name << "\n";

        string path = "tests/pagerank/" + name;
        string out_path = out_dir + name;

        try
        {
            PageRankInput in = readPageRankGraph(path);
            CSRGraph csr = convertToCSR(in.graph);

            auto start = chrono::high_resolution_clock::now();
            PageRankResult result = pageRank(csr, in.damping, in.tolerance, in.maxIterations);
            auto end = chrono::high_resolution_clock::now();

            double ms = chrono::duration<double, milli>(end - start).count();
            writePageRankOutput(out_path, result, in.damping, ms);

            double sum = 0.0;
            for (double x : result.rank)
                sum += x;

            cout << "  Sum of ranks: " << fixed << setprecision(6) << sum << "\n";
            cout << "  Iterations  : " << result.iterations << "\n";
            cout << "  Converged   : " << (result.converged ? "true" : "false") << "\n";
            cout << "  Time        : " << fixed << setprecision(3) << ms << " ms\n";
        }
        catch (const exception &e)
        {
            cout << "  Error: " << e.what() << "\n";
        }
        cout << string(50, '-') << "\n";
    }
}

int main()
{
    while (true)
    {
        cout << "\n=========================================\n"
             << "       Assignment 04 Test Runner\n"
             << "=========================================\n"
             << "1. Vertex Coloring (Welsh-Powell)\n"
             << "2. PageRank\n"
             << "0. Exit\n"
             << "=========================================\nChoice: ";

        int choice;
        if (!(cin >> choice))
        {
            safeCinWait();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 0)
            return 0;
        if (choice == 1)
            runColoring();
        else if (choice == 2)
            runPageRank();
        else
            cout << "Invalid choice.\n";
    }
}