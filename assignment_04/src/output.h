#ifndef ASSIGNMENT_04_OUTPUT_H
#define ASSIGNMENT_04_OUTPUT_H
#include <string>
#include "algorithms.h"
void writeColoringOutput(const std::string& file, const ColoringResult& result, double ms);
void writePageRankOutput(const std::string& file, const PageRankResult& result,
                         double damping, double ms);
#endif
