# CS509 - Assignment 04

**Candidates:** Deepak Kumar, Rajan Jha

This folder implements the **Individual Task** from Assignment 4:

- Greedy Vertex Coloring using Welsh-Powell ordering
- PageRank

The assignment inputs are adjacency lists. They are parsed into an adjacency-list graph and converted to a local CSR representation before the algorithms are called. CSR conversion is preprocessing and is outside the timed section.

## Directory Structure

```text
assignment_04/
├── src/
│   ├── CSR.h
│   ├── CSR.cpp
│   ├── algorithms.h
│   ├── graph_io.h
│   ├── graph_io.cpp
│   ├── output.h
│   ├── output.cpp
│   ├── vertex_coloring.cpp
│   └── pagerank.cpp
├── tests/
│   ├── vertex_coloring/
│   └── pagerank/
├── outputs/              # existing/reference output files
├── generated/             # files written by the test runner
├── driver/
│   └── main.cpp
├── Makefile
└── README.md
```

## Build and Run

From the `assignment_04` directory:

```bash
make
./graph_runner
```

Or:

```bash
make run
```

On Windows with MinGW, the executable is normally:

```text
graph_runner.exe
```

## Vertex Coloring

Uses Welsh-Powell ordering: vertices are sorted by non-increasing degree, with vertex ID used as the deterministic tie-breaker. Each vertex receives the smallest color not used by an already-colored neighbour.

The driver also verifies that every edge connects vertices with different colors.

Required sizes:

- 10
- 100
- 10,000
- 50,000
- 100,000

## PageRank

Uses simultaneous PageRank updates with the damping factor, tolerance, and maximum iterations read from the input file.

Dangling vertices distribute their rank uniformly over all vertices.

Required sizes:

- 10
- 100
- 1,000
- 10,000
- 50,000

## Timing

The timer starts immediately before the selected algorithm and stops immediately afterward.

Therefore the following are not included in algorithm timing:

- file reading
- input validation
- CSR conversion
- output writing

For PageRank, all iterations up to convergence or `MAX_ITERATIONS` are timed.

## Important Fixes

The original Assignment 04 source referenced:

```text
../../assignment_01/src/graph.h
../../assignment_01/src/csr.h
../assignment_01/src/csr.cpp
```

Those files do not exist in this repository. Assignment 04 is now self-contained with:

```text
src/CSR.h
src/CSR.cpp
```

The Makefile now compiles the actual Assignment 04 sources only.

Output directories are also created automatically when needed.
