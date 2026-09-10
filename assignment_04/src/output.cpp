#include "output.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <filesystem>

using namespace std;
using namespace filesystem;
// namespace filesystem;

// ============================================================
// HELPER: OPEN FILE SAFELY
// ============================================================
ofstream openOutput(const string &filepath)
{
    // Ensure the folder exists before trying to save the file
    filesystem::path p(filepath);
    if (p.has_parent_path())
    {
        filesystem::create_directories(p.parent_path());
    }

    ofstream out(filepath);
    if (out.is_open() == false)
    {
        throw runtime_error("Error: unable to open output file: " + filepath);
    }
    return out;
}

// ============================================================
// WRITE VERTEX COLORING RESULTS
// ============================================================
void writeColoringOutput(const string &file, const ColoringResult &result, double ms)
{
    ofstream out = openOutput(file);

    out << "Algorithm: Greedy Vertex Coloring\n";
    out << "Vertex colors:\n";

    for (int i = 0; i < (int)result.color.size(); i++)
    {
        out << i << " " << result.color[i] << "\n";
    }

    out << "Colors used: " << result.colorsUsed << "\n";

    if (result.valid == true)
    {
        out << "Valid: true\n";
    }
    else
    {
        out << "Valid: false\n";
    }

    out << fixed << setprecision(6) << "Execution time: " << ms << " ms\n";
}

// ============================================================
// WRITE PAGERANK RESULTS
// ============================================================
void writePageRankOutput(const string &file, const PageRankResult &result, double damping, double ms)
{
    ofstream out = openOutput(file);

    out << "Algorithm: PageRank\n";
    out << fixed << setprecision(6) << "Damping: " << damping << "\n";
    out << "Vertex ranks:\n";

    double sum = 0.0;
    for (int i = 0; i < (int)result.rank.size(); i++)
    {
        out << i << " " << result.rank[i] << "\n";
        sum += result.rank[i]; // Calculate the sum manually
    }

    out << "Sum of ranks: " << sum << "\n";
    out << "Iterations: " << result.iterations << "\n";

    if (result.converged == true)
    {
        out << "Converged: true\n";
    }
    else
    {
        out << "Converged: false\n";
    }

    out << "Execution time: " << ms << " ms\n";
}