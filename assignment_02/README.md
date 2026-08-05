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
