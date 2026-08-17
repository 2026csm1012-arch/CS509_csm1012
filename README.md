# CS509 / PGSL Assignments

This repository contains the implementations for **Assignment 01, Assignment 02, and Assignment 03**.

A root-level **wrapper program** is used to build and start the selected assignment. Each assignment remains an independent project with its own source files, tests, expected outputs, and Makefile.

---

# 1. Repository Structure

```text
PGSL/
│
├── wrapper.cpp
├── wrapper.exe
├── Makefile
├── README.md
│
├── assignment_01/
│   ├── build/
│   ├── driver/
│   ├── src/
│   ├── tests/
│   └── makefile
│
├── assignment_02/
│   ├── build/
│   ├── driver/
│   ├── expected/
│   ├── src/
│   ├── tests/
│   └── Makefile
│
└── assignment_03/
    ├── build/
    ├── driver/
    ├── expected/
    ├── src/
    ├── tests/
    └── Makefile
```

The important design is:

```text
PGSL
 │
 ├── wrapper.cpp
 │
 ├── assignment_01
 │
 ├── assignment_02
 │
 └── assignment_03
```

The wrapper is **outside** the assignment folders.

---

# 2. Root Wrapper

The root `wrapper.cpp` provides one common entry point for all assignments.

When the user runs:

```bash
make run
```

the wrapper displays:

```text
====================================
        PGSL Assignment Wrapper
====================================

1. Assignment 1
2. Assignment 2
3. Assignment 3

Enter assignment number:
```

The selected assignment is then:

1. Built using its own Makefile.
2. Started from inside that assignment's directory.
3. Run independently from the other assignments.

The wrapper uses the following pattern:

```cpp
make -C assignment_01
```

to build Assignment 01, and:

```cpp
cd /d assignment_01 && build\assignment_01.exe
```

to start it.

The same structure is used for Assignment 02 and Assignment 03.

## Why the wrapper changes directory

Relative paths used by an assignment are resolved from the **current working directory**.

For example, Assignment 03 uses:

```text
tests/MST/mst_10.txt
```

The wrapper therefore starts Assignment 03 from:

```text
PGSL/assignment_03/
```

so the path correctly resolves to:

```text
PGSL/assignment_03/tests/MST/mst_10.txt
```

This avoids depending on the location of `main.cpp` or the executable itself.

---

# 3. Root Makefile

The root Makefile builds the wrapper:

```makefile
all:
	g++ -std=c++17 -Wall -Wextra wrapper.cpp -o wrapper

run:
	./wrapper

clean:
	rm -f wrapper wrapper.exe
```

## Build wrapper

From the repository root:

```bash
make
```

## Run wrapper

```bash
make run
```

## Clean wrapper

```bash
make clean
```

---

# 4. Assignment 01 — Matrix Multiplication

## Overview

Assignment 01 compares two matrix multiplication approaches:

1. **GEMM**
2. **Blocked Matrix Multiplication**

The program reads matrix data from test files, executes the selected method, and measures execution time.

## Program menu

```text
1. GEMM
2. Blocking
```

If Blocking is selected, the program also asks for the blocking factor.

Example:

```text
select the method you want to proceed with:
1. GEMM
2. Blocking

2

Enter Blocking factor:
4
```

## Structure

```text
assignment_01/
├── build/
│   └── assignment_01.exe
├── driver/
│   └── main.cpp
├── src/
│   └── algorithm.cpp
├── tests/
│   ├── test (1).txt
│   ├── test (2).txt
│   ├── test (3).txt
│   ├── test (4).txt
│   └── test (5).txt
└── makefile
```

## Build

From the repository root:

```bash
make -C assignment_01
```

or enter the directory:

```bash
cd assignment_01
make
```

## Run directly

From `assignment_01`:

```bash
./build/assignment_01.exe
```

When using the root wrapper, the wrapper changes into `assignment_01` before starting the executable.

---

# 5. Assignment 02 — Graph Algorithms

Assignment 02 contains graph algorithms operating on graph representations built using CSR-related structures.

The current implementation contains:

- Bellman-Ford
- Floyd-Warshall
- CSR graph representation
- Expected-output comparison
- PASS/FAIL reporting
- Algorithm-only execution-time measurement

## Structure

```text
assignment_02/
├── build/
│   └── assignment_02.exe
├── driver/
│   └── main.cpp
├── src/
│   ├── CSR.h
│   ├── CSR.cpp
│   ├── GraphAlgo.h
│   └── GraphAlgo.cpp
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
│   └── Floyd-Warshall/
│
└── Makefile
```

## Program menu

```text
1. Bellman-Ford
2. Floyd-Warshall
```

Only the algorithm selected by the user is executed.

## Bellman-Ford

Bellman-Ford uses the graph/edge-list input format and reports:

- Vertices
- Edges
- Source
- Negative-cycle status
- Execution time
- PASS/FAIL status

The expected output is used for verification.

## Floyd-Warshall

Floyd-Warshall uses an adjacency-matrix input format.

The expected output contains the shortest-path distance matrix. Execution time is not used for correctness comparison because it is machine-dependent.

## Timing

The measured interval contains the algorithm execution only.

Input loading, graph preparation, expected-file reading, and result comparison are outside the measured timing interval.

## Build

```bash
make -C assignment_02
```

## Run through wrapper

```bash
make run
```

Then select:

```text
2
```

---

# 6. Assignment 03 — Minimum Spanning Tree

Assignment 03 currently focuses on the **Minimum Spanning Tree (MST)** portion.

The implemented algorithms are:

1. **Prim's Algorithm**
2. **Kruskal's Algorithm**

Gradient Descent and Maxflow-Mincut are not part of the current Assignment 03 implementation.

## Structure

```text
assignment_03/
├── build/
│   └── assignment_03.exe
├── driver/
│   └── main.cpp
├── src/
│   ├── MST.h
│   └── MST.cpp
├── tests/
│   └── MST/
│       ├── mst_10.txt
│       ├── mst_100.txt
│       ├── mst_10000.txt
│       └── mst_50000.txt
├── expected/
│   └── MST/
│       ├── mst_10.txt
│       ├── mst_100.txt
│       ├── mst_10000.txt
│       └── mst_50000.txt
└── Makefile
```

## Program menu

```text
1. Prim's Algorithm
2. Kruskal's Algorithm
```

The algorithms run **separately**.

If the user selects Prim:

```text
1
```

only Prim is executed.

If the user selects Kruskal:

```text
2
```

only Kruskal is executed.

They are never executed together.

## Output

The driver intentionally keeps the output simple.

For each test it reports:

```text
mst_10 : PASS | Time: 0.12345 ms
```

or:

```text
mst_10 : FAIL | Time: 0.12345 ms
```

The MST edges and detailed algorithm result are not printed.

Correctness is determined by:

```text
graph is connected
AND
calculated MST weight == expected MST weight
```

## Timing

The timer starts immediately before:

```cpp
MSTAlgorithms::prim(graph);
```

or:

```cpp
MSTAlgorithms::kruskal(graph);
```

and stops immediately afterward.

Therefore file loading and expected-result reading are not included in the reported algorithm time.

## Build

```bash
make -C assignment_03
```

## Run directly

From `assignment_03`:

```bash
./build/assignment_03.exe
```

## Run through wrapper

From the repository root:

```bash
make run
```

Select:

```text
3
```

Then choose:

```text
1. Prim's Algorithm
2. Kruskal's Algorithm
```

---

# 7. Path Handling

All assignments use paths relative to their own working directory.

The wrapper therefore starts each assignment from its own directory.

For example:

```text
PGSL/
└── assignment_03/
    ├── tests/
    │   └── MST/
    │       └── mst_10.txt
    └── build/
        └── assignment_03.exe
```

The wrapper runs:

```cmd
cd /d assignment_03 && build\assignment_03.exe
```

The program then uses:

```cpp
"tests/MST/mst_10.txt"
```

which resolves correctly.

### Important

Do not change:

```text
tests/MST/
```

to:

```text
../tests/MST/
```

when the wrapper starts the program from inside `assignment_03`.

Similarly, Assignment 02 paths such as:

```text
tests/Bellman-Ford/
tests/Floyd-Warshall/
```

are relative to `assignment_02`.

---

# 8. Complete Execution Flow

The repository is intended to be used from the root directory.

```text
                    PGSL
                     │
                     ▼
                 make run
                     │
                     ▼
               wrapper.cpp
                     │
          ┌──────────┼──────────┐
          │          │          │
          ▼          ▼          ▼
     Assignment 1 Assignment 2 Assignment 3
          │          │          │
          ▼          ▼          ▼
        make       make       make
          │          │          │
          ▼          ▼          ▼
      build exe   build exe   build exe
          │          │          │
          ▼          ▼          ▼
       run from   run from   run from
       own dir    own dir    own dir
```

This keeps each assignment independent while providing a single entry point.

---

# 9. Recommended Commands

## Build everything individually

```bash
make -C assignment_01
make -C assignment_02
make -C assignment_03
```

## Build the wrapper

```bash
make
```

## Start the assignment selector

```bash
make run
```

## Clean individual assignments

```bash
make -C assignment_01 clean
make -C assignment_02 clean
make -C assignment_03 clean
```

## Clean the wrapper

```bash
make clean
```

---

# 10. Design Summary

The project follows a simple separation of responsibilities.

### Root level

```text
wrapper.cpp
```

Responsible for:

- Selecting an assignment
- Building the selected assignment
- Starting the selected executable
- Setting the correct working directory

### Assignment level

Each assignment has its own:

- `driver/`
- `src/`
- `tests/`
- `expected/` where required
- `build/`
- `Makefile`

The assignment driver is responsible for:

- User menu
- Test execution
- Input validation
- Algorithm execution
- Timing
- Expected-result comparison
- PASS/FAIL reporting

---

# 11. Current Scope

| Assignment | Current Algorithms / Methods |
|---|---|
| Assignment 01 | GEMM, Blocking |
| Assignment 02 | Bellman-Ford, Floyd-Warshall, CSR |
| Assignment 03 | Prim, Kruskal |

Assignment 03 intentionally does not include Gradient Descent or Maxflow-Mincut.

---

# 12. Important Notes

1. Run the root wrapper from the `PGSL` directory.
2. Each assignment should be executed from its own directory so relative test paths work correctly.
3. Do not mix test paths between assignments.
4. The wrapper builds only the assignment selected by the user.
5. Prim and Kruskal are selected independently.
6. Execution time measures the algorithm section, not file loading or result comparison.
7. Expected output files are used to determine PASS/FAIL where applicable.
8. Large test cases should only be enabled when required by the assignment/testing setup.

---

# 13. Quick Start

From:

```text
PGSL/
```

run:

```bash
make
make run
```

Then choose:

```text
1  -> Assignment 01
2  -> Assignment 02
3  -> Assignment 03
```

The wrapper will build and launch only the selected assignment.
