#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "../src/CSR.h"
#include "../src/graph_io.h"
#include "../src/algorithms.h"
#include "../src/output.h"

using namespace std;
namespace fs = std::filesystem;

static void runColoring() {
    cout << "\nVertex Coloring test files:\n"
         << "1. color_10.txt\n2. color_100.txt\n3. color_10000.txt\n"
         << "4. color_50000.txt\n5. color_100000.txt\n0. Back\nChoice: ";
    int c; cin >> c; if (c == 0) return; if (c < 1 || c > 5) { cout << "Invalid choice.\n"; return; }
    const string names[] = {"color_10.txt","color_100.txt","color_10000.txt","color_50000.txt","color_100000.txt"};
    string path = "tests/vertex_coloring/" + names[c-1];
    try {
        Graph g = readUnweightedGraph(path, true);
        CSRGraph csr = convertToCSR(g); // required preprocessing; not timed
        auto start = chrono::high_resolution_clock::now();
        ColoringResult result = greedyColoring(csr);
        auto end = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(end-start).count();
        string out = "generated/vertex_coloring/" + names[c-1];
        writeColoringOutput(out, result, ms);
        cout << "\nAlgorithm: Greedy Vertex Coloring\nColors used: " << result.colorsUsed
             << "\nValid: " << (result.valid ? "true" : "false")
             << "\nExecution time: " << fixed << setprecision(3) << ms << " ms\n";
    } catch (const exception& e) { cout << e.what() << "\n"; }
}

static void runPageRank() {
    cout << "\nPageRank test files:\n"
         << "1. pagerank_10.txt\n2. pagerank_100.txt\n3. pagerank_1000.txt\n"
         << "4. pagerank_10000.txt\n5. pagerank_50000.txt\n0. Back\nChoice: ";
    int c; cin >> c; if (c == 0) return; if (c < 1 || c > 5) { cout << "Invalid choice.\n"; return; }
    const string names[] = {"pagerank_10.txt","pagerank_100.txt","pagerank_1000.txt","pagerank_10000.txt","pagerank_50000.txt"};
    string path = "tests/pagerank/" + names[c-1];
    try {
        PageRankInput in = readPageRankGraph(path);
        CSRGraph csr = convertToCSR(in.graph); // required preprocessing; not timed
        auto start = chrono::high_resolution_clock::now();
        PageRankResult result = pageRank(csr, in.damping, in.tolerance, in.maxIterations);
        auto end = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(end-start).count();
        string out = "generated/pagerank/" + names[c-1];
        writePageRankOutput(out, result, in.damping, ms);
        double sum = 0.0; for (double x : result.rank) sum += x;
        cout << "\nAlgorithm: PageRank\nDamping: " << in.damping
             << "\nSum of ranks: " << fixed << setprecision(6) << sum
             << "\nIterations: " << result.iterations
             << "\nConverged: " << (result.converged ? "true" : "false")
             << "\nExecution time: " << setprecision(3) << ms << " ms\n";
    } catch (const exception& e) { cout << e.what() << "\n"; }
}

int main() {
    while (true) {
        cout << "\n=========================================\n"
             << "      Assignment 04 Test Runner\n"
             << "=========================================\n"
             << "1. Vertex Coloring (Welsh-Powell)\n"
             << "2. PageRank\n"
             << "0. Exit\n"
             << "=========================================\nChoice: ";
        int choice; if (!(cin >> choice)) return 1;
        if (choice == 0) return 0;
        if (choice == 1) runColoring();
        else if (choice == 2) runPageRank();
        else cout << "Invalid choice.\n";
    }
}
