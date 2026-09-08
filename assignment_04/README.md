# CS509 - Assignment 04

## Individual Assignment

This repository contains the implementation for **Assignment 04** (Greedy Vertex Coloring using Welsh-Powell ordering and PageRank) operating on graphs formatted as Compressed Sparse Row (CSR).

---

## 1. Objectives

- Implement a greedy graph-coloring algorithm using **Welsh-Powell ordering**.
- Implement the **PageRank** algorithm for directed graphs.
- Read graph data from files in adjacency-list form.
- Convert the graph to CSR before calling the algorithms.
- Measure execution time strictly for the algorithm execution phase.
- Generate result files for each test case.
- Validate result correctness.

---

## 2. Algorithms Implemented

### 2.1 Greedy Vertex Coloring - Welsh-Powell

The Welsh-Powell approach orders vertices by **non-increasing degree**. Ties are broken using the smaller vertex ID.

Vertices are colored sequentially:

1. Select the next vertex in Welsh-Powell ordering.
2. Examine its already-colored neighbors.
3. Find the smallest available color not used by adjacent neighbors.
4. Assign that color to the vertex.
5. Repeat until all vertices are colored.

The output is validated by verifying that for every edge $(u, v)$, $\text{color}[u] \neq \text{color}[v]$.

#### Dataset Sizes

- 10 vertices
- 100 vertices
- 10,000 vertices
- 50,000 vertices
- 100,000 vertices

---

### 2.2 PageRank

Iterative rank updates are computed using:

- **Damping factor ($d$)**: Specified in input file
- **Tolerance ($\epsilon$)**: Convergence threshold specified in input file
- **Maximum iterations**: Specified in input file

#### Algorithm Details

1. Initial rank allocation for each vertex: $R_0(v) = \frac{1}{V}$
2. Base teleportation contribution for each iteration: $\frac{1 - d}{V}$
3. Non-dangling vertices distribute rank equally across outgoing edges: $d \times \frac{R(u)}{\text{outdegree}(u)}$
4. **Dangling Node Handling:** Vertices with no outgoing edges have their accumulated rank collected and redistributed uniformly among all vertices.
5. Convergence is reached when total vector change $\le \epsilon$ or maximum iteration limit is met.

#### Dataset Sizes

- 10 vertices
- 100 vertices
- 1,000 vertices
- 10,000 vertices
- 50,000 vertices

---

## 3. Input Format

### 3.1 Vertex Coloring Input

Uses adjacency-list format. Line 1 specifies total vertices $V$ and edges $E$:

```text
V E
u degree v1 v2 v3 ...
```

Example:

```text
5 5
0 2 1 4
1 2 0 2
2 2 1 3
3 2 2 4
4 2 3 0
```

Validation constraints:

- Edges must appear at both endpoints ($2E$ total entries).
- No self-loops or parallel edges.

---

### 3.2 PageRank Input

Follows adjacency-list format followed by configuration parameters:

```text
4 5
0 2 1 2
1 1 2
2 1 0
3 1 2
DAMPING 0.85
TOLERANCE 0.0001
MAX_ITERATIONS 100
```

Validation constraints:

- $0 < \text{DAMPING} < 1$
- $\text{TOLERANCE} > 0$
- $\text{MAX\_ITERATIONS} > 0$

---

## 4. CSR Representation

Graphs are converted from adjacency lists to **Compressed Sparse Row (CSR)** format prior to execution.

CSR stores graph structures using compact arrays:

- `row_ptr`
- `col_idx`

For vertex $u$, neighbors are located at `col_idx[row_ptr[u] ... row_ptr[u+1]-1]`. CSR conversion time is excluded from performance timing.

---

## 5. Directory Structure

```text
assignment_04/
├── driver/
│   └── main.cpp
├── src/
│   ├── algorithms.h
│   ├── graph_io.h
│   ├── graph_io.cpp
│   ├── output.h
│   ├── output.cpp
│   ├── vertex_coloring.cpp
│   └── pagerank.cpp
├── tests/
│   ├── vertex_coloring/
│   │   ├── color_10.txt
│   │   ├── color_100.txt
│   │   ├── color_10000.txt
│   │   ├── color_50000.txt
│   │   └── color_100000.txt
│   └── pagerank/
│       ├── pagerank_10.txt
│       ├── pagerank_100.txt
│       ├── pagerank_1000.txt
│       ├── pagerank_10000.txt
│       └── pagerank_50000.txt
├── generated/
│   ├── vertex_coloring/
│   └── pagerank/
├── outputs/
│   ├── vertex_coloring/
│   └── pagerank/
├── Makefile
└── README.md
```

---

## 6. Source File Description

- **`driver/main.cpp`**: Interactive CLI driver executing selected algorithm test runs.
- **`src/graph_io.cpp`**: Parses input files and performs validation checks.
- **`src/vertex_coloring.cpp`**: Welsh-Powell sorting and coloring implementation.
- **`src/pagerank.cpp`**: Iterative PageRank computation and dangling node handler.
- **`src/output.cpp`**: Formats and outputs execution metrics and status reports.
- **`Makefile`**: Target builder configuring `g++ -std=c++17 -O2 -Wall -Wextra -pedantic`.

---

## 7. Build Instructions

### Compilation

```bash
make
```

### Clean Build Artifacts

```bash
make clean
```

### Build & Run

```bash
make run
```

---

## 8. Running the Program

Execute the binary:

```bash
./graph_runner
```

### Interface Menu Options

```text
=========================================
      Assignment 04 Test Runner
=========================================
1. Vertex Coloring (Welsh-Powell)
2. PageRank
0. Exit
=========================================
```

Selecting an option displays the corresponding dataset options (`color_*.txt` or `pagerank_*.txt`). Output execution details will print to console and write to the `generated/` directory.

---

## 9. Output Files Directory

Execution results write to:

```text
generated/vertex_coloring/
generated/pagerank/
```

Reference outputs are stored under `outputs/`.

---

## 10. Timing Methodology

Timers strictly isolate pure algorithm execution:

- **Vertex Coloring**: Timer wraps `greedyColoring(csr)` directly.
- **PageRank**: Timer wraps `pageRank(csr, damping, tolerance, maxIterations)`.

File reading, input validation, CSR construction, and file output are excluded from timing.

---

## 11. Verification Checks

- **Coloring Validity**: Asserts $\text{color}[u] \neq \text{color}[v]$ for all edges.
- **PageRank Validity**: Verifies convergence status, total iteration count, and validates that total rank sum equals approximately $1.000000$.

---

## 12. Performance Results & Experimental Report

### 12.1 Vertex Coloring Results

| File               |       V |       E | Colors Used | Valid? | Time (ms) | Status |
| ------------------ | ------: | ------: | ----------: | ------ | --------: | ------ |
| `color_10.txt`     |      10 |      20 |           3 | Yes    |  0.002500 | Pass   |
| `color_100.txt`    |     100 |     200 |           4 | Yes    |  0.010611 | Pass   |
| `color_10000.txt`  |  10,000 |  20,000 |           5 | Yes    |  3.000135 | Pass   |
| `color_50000.txt`  |  50,000 | 100,000 |           5 | Yes    | 16.689050 | Pass   |
| `color_100000.txt` | 100,000 | 200,000 |           5 | Yes    | 15.438450 | Pass   |

### 12.2 PageRank Results

| File                 |      V |       E | Damping | Top Vertex | Top Rank | Sum of Ranks | Iterations | Time (ms) | Status |
| -------------------- | -----: | ------: | ------: | ---------: | -------: | -----------: | ---------: | --------: | ------ |
| `pagerank_10.txt`    |     10 |      20 |    0.85 |          5 | 0.182210 |     1.000000 |         18 |  0.002215 | Pass   |
| `pagerank_100.txt`   |    100 |     200 |    0.85 |          7 | 0.030247 |     1.000000 |         21 |  0.026303 | Pass   |
| `pagerank_1000.txt`  |  1,000 |   2,000 |    0.85 |        740 | 0.003665 |     1.000000 |         22 |  0.145077 | Pass   |
| `pagerank_10000.txt` | 10,000 |  20,000 |    0.85 |      6,375 | 0.000397 |     1.000000 |         21 |  5.084499 | Pass   |
| `pagerank_50000.txt` | 50,000 | 100,000 |    0.85 |     34,607 | 0.000107 |     1.000000 |         21 | 21.138039 | Pass   |

---

## 13. Complexity Analysis

### Welsh-Powell Vertex Coloring

- **Degree calculation**: $\mathcal{O}(V)$
- **Vertex Sorting**: $\mathcal{O}(V \log V)$
- **Coloring Phase**: $\mathcal{O}(V + E)$
- **Validation**: $\mathcal{O}(V + E)$
- **Overall Time Complexity**: $\mathcal{O}(V \log V + E)$

### PageRank Algorithm

- **Per Iteration**: $\mathcal{O}(V + E)$
- **Total Time Complexity**: $\mathcal{O}(I \cdot (V + E))$ where $I$ is total iterations until convergence.
- **Space Complexity**: $\mathcal{O}(V + E)$ for CSR representation and rank vectors.

---

## 14. Design Decisions

- **Deterministic Welsh-Powell Ordering**: Vertices with equal degrees break ties using vertex index in ascending order.
- **Synchronous PageRank Updates**: Vector updates use double buffering ($R_{\text{new}}$ calculated exclusively from $R_{\text{old}}$) to prevent intermediate modification artifacts.
- **Isolated CSR Timings**: Excludes system IO and structure initialization overhead to isolate pure algorithmic efficiency.

---

## 15. Troubleshooting & Usage Notes

- **Input Path Execution**: Run `./graph_runner` from the root `assignment_04` directory so relative directory paths (`tests/`, `generated/`) resolve properly.
- **Compiler Compatibility**: Requires a C++17 compliant compiler (`g++` version 7+) and standard GNU `make`.
