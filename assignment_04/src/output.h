#ifndef ASSIGNMENT_04_OUTPUT_H
#define ASSIGNMENT_04_OUTPUT_H

#include <string>
#include "algorithms.h"

using namespace std;

// ============================================================
// OUTPUT WRITER FUNCTIONS
// ============================================================

// Saves the final results of the Vertex Coloring algorithm to a text file
void writeColoringOutput(const string &file, const ColoringResult &result, double ms);

// Saves the final results of the PageRank algorithm to a text file
void writePageRankOutput(const string &file, const PageRankResult &result, double damping, double ms);

#endif