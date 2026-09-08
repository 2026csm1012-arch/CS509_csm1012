#include "output.h"
#include <fstream>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <filesystem>

using namespace std;

static ofstream openOutput(const string& file) {
    filesystem::path path(file);
    if (path.has_parent_path())
        filesystem::create_directories(path.parent_path());

    ofstream out(file);
    if (!out)
        throw runtime_error("Error: unable to open output file: " + file);
    return out;
}

void writeColoringOutput(const string& file, const ColoringResult& result, double ms) {
    ofstream out = openOutput(file);
    out << "Algorithm: Greedy Vertex Coloring\n";
    out << "Vertex colors:\n";
    for (int i = 0; i < static_cast<int>(result.color.size()); ++i)
        out << i << " " << result.color[i] << "\n";
    out << "Colors used: " << result.colorsUsed << "\n";
    out << "Valid: " << (result.valid ? "true" : "false") << "\n";
    out << fixed << setprecision(6) << "Execution time: " << ms << " ms\n";
}

void writePageRankOutput(const string& file, const PageRankResult& result,
                         double damping, double ms) {
    ofstream out = openOutput(file);
    out << "Algorithm: PageRank\n";
    out << fixed << setprecision(6) << "Damping: " << damping << "\n";
    out << "Vertex ranks:\n";
    for (int i = 0; i < static_cast<int>(result.rank.size()); ++i)
        out << i << " " << result.rank[i] << "\n";
    double sum = accumulate(result.rank.begin(), result.rank.end(), 0.0);
    out << "Sum of ranks: " << sum << "\n";
    out << "Iterations: " << result.iterations << "\n";
    out << "Converged: " << (result.converged ? "true" : "false") << "\n";
    out << "Execution time: " << ms << " ms\n";
}
