# Graph to CSR (Compressed Sparse Row) Converter

This C++ program reads graph data from a series of text files and converts the adjacency list representation into a **Compressed Sparse Row (CSR)** format. It supports both weighted and unweighted graphs and interactively prompts the user for the graph type during execution.

## Features
- Parses graphs from text files located in a `../tests/` directory.
- Interactively asks whether each graph is weighted or unweighted.
- Generates and outputs the `row_ptr` and `col_idx` arrays (and a `weights` array if applicable) representing the graph in CSR format.
- Automatically handles up to 5 test files (`test (1).txt` through `test (5).txt`).

## Prerequisites
- A standard C++ compiler (e.g., `g++`, `clang++`, or MSVC).

## Directory Structure
The program expects a specific directory structure to locate the input files correctly. It assumes the executable is run from a directory parallel to a `tests` folder:

```text
project_root/
│
├── src/
│   └── main.cpp         <-- (Your C++ source code)
│
└── tests/               <-- (Input files must be placed here)
    ├── test (1).txt
    ├── test (2).txt
    ├── test (3).txt
    ├── test (4).txt
    └── test (5).txt
```

## Input File Format
Each text file should be structured as follows:

1. **First line:** `V E` (Number of Vertices and Number of Edges).
2. **Subsequent lines:** Each line represents a node and its neighbors in the following format:
   - **Unweighted:** `[node_index] [neighbor_count] [neighbor_1] [neighbor_2] ...`
   - **Weighted:** `[node_index] [neighbor_count] [neighbor_1] [weight_1] [neighbor_2] [weight_2] ...`
3. **Termination string:** The graph parsing will stop if a line starts with the word `SOURCE`.

### Example Input File (`test (1).txt`) - Unweighted
```text
4 4
0 2 1 2
1 1 3
2 1 3
3 0
SOURCE 0
```

## How to Build and Run

1. Open your terminal or command prompt.
2. Navigate to the directory containing your C++ file (e.g., `cd src`).
3. Compile the code using `g++`:
   ```bash
   g++ main.cpp -o graph_csr
   ```
4. Run the executable:
   ```bash
   ./graph_csr
   ```

## Usage
Upon running, the program will process each file one by one. For each valid file found, it will pause and prompt you:
```text
Is the graph in test (1).txt weighted? (y/n):
```
- Type `y` or `Y` and press Enter if the file contains edge weights.
- Type `n` or `N` and press Enter if the file represents an unweighted graph.

The program will then output the CSR arrays to the console:
```text
File: test (1).txt
row_ptr: 0 2 3 4 4 
col_idx: 1 2 3 3 
```
Assignment 02 -- Graph Algorithms

Implementation and performance evaluation of graph algorithms usingC++17.

Current Status

The current implementation covers:

Bellman-Ford

Floyd-Warshall

CSR graph representation

Separate input formats for the two algorithms

Expected-output comparison

Algorithm-only execution-time measurement

Automatic execution of all test cases for the selected algorithm

PASS/FAIL reporting

All currently executed Bellman-Ford and Floyd-Warshall test cases passagainst their expected outputs.

Note: Triangle Counting, Betweenness Centrality, and ConnectedComponents are planned for the next stage and are not included in thecurrent results.

1. Project Structure

assignment_02/
│
├── src/
│   ├── CSR.h
│   ├── CSR.cpp
│   ├── GraphAlgo.h
│   └── GraphAlgo.cpp
│
├── driver/
│   └── main.cpp
│
├── tests/
│   ├── Bellman-Ford/
│   │   ├── bf_10.txt
│   │   ├── bf_100.txt
│   │   ├── bf_10000.txt
│   │   ├── bf_50000.txt
│   │   └── bf_100000.txt
│   │
│   └── Floyd-Warshall/
│       ├── fw_10.txt
│       ├── fw_100.txt
│       ├── fw_500.txt
│       ├── fw_1000.txt
│       └── fw_2000.txt
│
├── expected/
│   ├── Bellman-Ford/
│   │   ├── bf_10.txt
│   │   ├── bf_100.txt
│   │   ├── bf_10000.txt
│   │   ├── bf_50000.txt
│   │   └── bf_100000.txt
│   │
│   └── Floyd-Warshall/
│       ├── fw_10.txt
│       ├── fw_100.txt
│       ├── fw_500.txt
│       ├── fw_1000.txt
│       └── fw_2000.txt
│
├── Makefile
├── README.md
└── build/
    └── assignment_02.exe

2. File Responsibilities

File / Folder                       Responsibility

src/CSR.h                         Declares the CSR graph structureand graph-loading functions.

src/CSR.cpp                       Implements CSR construction andinput loading.

src/GraphAlgo.h                   Declares graph algorithms and theirresult structures.

src/GraphAlgo.cpp                 Implements Bellman-Ford andFloyd-Warshall.

driver/main.cpp                   Menu, test execution, timing,expected-output comparison andreporting.

tests/                            Contains algorithm-specific inputtest cases.

expected/                         Contains expected outputs used forPASS/FAIL validation.

Makefile                          Builds the project using C++17 andoptimization.

3. Working Flow

                    Program Start
                         │
                         ▼
                 Select Algorithm
                    /          \
                   /            \
          Bellman-Ford       Floyd-Warshall
               │                   │
               ▼                   ▼
       Read edge-list        Read adjacency matrix
               │                   │
               ▼                   ▼
          Validate input       Validate input
               │                   │
               ▼                   ▼
          Build CSR graph      Convert matrix to CSR
               │                   │
               └─────────┬─────────┘
                         ▼
                  Call algorithm
                         │
                         ▼
              Measure algorithm time
                         │
                         ▼
                 Generate result
                         │
                         ▼
               Read expected result
                         │
                         ▼
                   Compare results
                         │
                         ▼
                    PASS / FAIL
                         │
                         ▼
                 Run next test case

Only the algorithm execution is included in the measured timing. Inputloading, CSR construction, expected-file reading and result comparisonare outside the measured interval.

4. Bellman-Ford

Input

Bellman-Ford uses the graph/edge-list input format supported by the CSRloader.

Current test files:

Test File           Vertices     Edges

bf_10.txt               10        30bf_100.txt             100       300bf_10000.txt        10,000    30,000bf_50000.txt        50,000   150,000bf_100000.txt      100,000   300,000

The source vertex for the current tests is 0.

Expected Output

Expected Bellman-Ford files contain information such as:

Execution Time : 0.00792 ms
Bellman-Ford Shortest Path Distances
Source: 0

0 -> 0 : 0
0 -> 1 : 36
0 -> 2 : 8
...

The Execution Time line is ignored during PASS/FAIL comparison becauseexecution time is machine-dependent.

The distance results are compared against the actual algorithm output.

5. Floyd-Warshall

Input

Floyd-Warshall uses an adjacency-matrix input format.

Example:

10
0 INF INF INF INF INF INF INF INF 12
INF 0 1 INF 14 INF 7 INF INF INF
INF 12 0 INF 15 INF 19 INF INF INF
22 13 13 0 27 28 20 30 27 34
...

The first line specifies the number of vertices.

The following N × N values represent the adjacency matrix.

INF means there is no direct edge.

The matrix is read by loadMatrixFromFile() and converted into the CSRgraph representation before calling Floyd-Warshall.

Current Test Files

Test File         Vertices

fw_10.txt             10fw_100.txt           100fw_500.txt           500fw_1000.txt        1,000fw_2000.txt        2,000

6. Expected Output -- Floyd-Warshall

Expected files have the following format:

Execution Time : 0.030783 ms
0 33 31 22 46 18 40 35 17 12
9 0 1 19 14 15 7 17 14 21
21 12 0 31 15 27 19 29 26 32
...

The Execution Time line is ignored.

The complete distance matrix is compared with the actual Floyd-Warshallresult.

7. Build Instructions

From the project root:

make clean
make

The executable is generated as:

build/assignment_02.exe

8. Running the Program

Run:

.\build\assignment_02.exe

The program displays:

1. Bellman-Ford
2. Floyd-Warshall

Choice:

Enter:

1

to run all Bellman-Ford tests.

Enter:

2

to run all Floyd-Warshall tests.

The program automatically executes every test case for the selectedalgorithm.

9. Current Bellman-Ford Results

The following results were obtained from the latest project run.

Algorithm      Test File           Vertices     Edges   Source Negative   Expected Output Actual     Time (ms) StatusCycle                      Output

Bellman-Ford   bf_10.txt               10        30        0 No         Shortest-path   Matched      0.00180 PASSdistances

Bellman-Ford   bf_100.txt             100       300        0 No         Shortest-path   Matched      0.01230 PASSdistances

Bellman-Ford   bf_10000.txt        10,000    30,000        0 No         Shortest-path   Matched      0.05060 PASSdistances

Bellman-Ford   bf_50000.txt        50,000   150,000        0 No         Shortest-path   Matched      7.90610 PASSdistances

10. Current Floyd-Warshall Results

Algorithm        Test File         Vertices       Edges Negative   Expected   Actual        Time (ms) StatusCycle      Output     Output

Floyd-Warshall   fw_10.txt             10          23 No         Distance   Matched         0.01300 PASSmatrix

Floyd-Warshall   fw_100.txt           100       2,964 No         Distance   Matched         1.26610 PASSmatrix

Floyd-Warshall   fw_500.txt           500      74,856 No         Distance   Matched       138.80820 PASSmatrix

Floyd-Warshall   fw_1000.txt        1,000     299,973 No         Distance   Matched       926.95910 PASSmatrix

11. Performance Analysis

Bellman-Ford

Bellman-Ford has a theoretical time complexity of:

O(VE)

The current measurements show increasing execution time as the number ofvertices and edges grows.

Vertices     Edges   Time (ms)

      10        30     0.00180
     100       300     0.01230
  10,000    30,000     0.05060
  50,000   150,000     7.90610
 100,000   300,000    19.74260

Floyd-Warshall

Floyd-Warshall has a theoretical time complexity of:

O(V³)

The current results show a much stronger increase as the matrix sizegrows.

Vertices       Edges     Time (ms)

      10          23       0.01300
     100       2,964       1.26610
     500      74,856     138.80820
   1,000     299,973     926.95910
   2,000   1,197,808   7,497.46210

The 2,000-vertex Floyd-Warshall test currently takes approximately:

7.497 seconds

for the measured algorithm execution.

These timings are machine-dependent and may change between runs.

12. Negative-Cycle Handling

The driver reports whether the selected graph contains a negative cycle.

Current test results:

Bellman-Ford: no negative cycle detected in the current test cases.

Floyd-Warshall: no negative cycle detected in the current testcases.

The driver also supports comparing a negative-cycle result when thealgorithm reports one.

13. Test Naming

The current naming follows the assignment requirements.

Bellman-Ford

bf_10.txt
bf_100.txt
bf_10000.txt
bf_50000.txt
bf_100000.txt

Floyd-Warshall

fw_10.txt
fw_100.txt
fw_500.txt
fw_1000.txt
fw_2000.txt

14. Assignment Requirements -- Current Implementation

Requirement                                   Status

Select algorithm through common driver/menu   CompletedRun all test cases for selected algorithm     CompletedRead and validate input                       Completed for current BF/FW formatsReject invalid input                          Implemented in input loadingConstruct CSR representation                  CompletedCall selected algorithm from driver           CompletedCompare with expected output                  CompletedMeasure algorithm execution time              CompletedExclude input/output processing from timing   CompletedReport PASS/FAIL                              CompletedClear error for missing input file            ImplementedBellman-Ford test suite                       CompletedFloyd-Warshall test suite                     CompletedTriangle Counting                             PendingBetweenness Centrality                        PendingConnected Components                          PendingFinal complete Assignment 02 results          Pending

15. Development Time Frame

Phase                               Work

Phase 1                             Project structure, Makefile and CSRrepresentation

Phase 2                             Bellman-Ford implementation andtest integration

Phase 3                             Bellman-Ford expected-outputcomparison

Phase 4                             Floyd-Warshall implementation andseparate matrix input handling

Phase 5                             Floyd-Warshall expected-outputcomparison

Phase 6                             Algorithm-only timing and PASS/FAILreporting

Phase 7                             Performance testing using allcurrent BF/FW test cases

Phase 8                             Triangle Counting, BetweennessCentrality and Connected Components

16. Next Work

The remaining Assignment 02 algorithms are:

Triangle Counting

Betweenness Centrality

Connected Components

For each remaining algorithm, the same general workflow will befollowed:

Input Test File
      ↓
Validate Input
      ↓
Build Adjacency / CSR Representation
      ↓
Call Algorithm
      ↓
Measure Algorithm Time
      ↓
Generate Actual Result
      ↓
Read Expected Result
      ↓
Compare
      ↓
PASS / FAIL
      ↓
Add Result to README

The final README will contain result tables for every required algorithmand test case.

17. Current Conclusion

The current Bellman-Ford and Floyd-Warshall implementation is workingsuccessfully with separate test-case sets and separate input formats.

The latest run produced:

Bellman-Ford:     5/5 PASS
Floyd-Warshall:   5/5 PASS
Total:           10/10 PASS

The project is ready for integration of the remaining graph-analyticsalgorithms.