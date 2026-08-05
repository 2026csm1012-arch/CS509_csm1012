CS509 Assignments

This repository contains the C++ implementations for Assignment 01 (Matrix Multiplication) and Assignment 02 (Graph Representation) for the CS509 course.

---

## Assignment 01: Matrix Multiplication

### Overview & Working
This assignment evaluates and compares the performance of two distinct matrix multiplication algorithms:
1. **Standard GEMM (General Matrix Multiply):** The traditional three-nested-loops approach.
2. **Blocked Matrix Multiplication:** A cache-optimized approach that divides matrices into smaller sub-blocks (e.g., blocking factor of 3). 

The program parses matrix dimensions and elements from input text files, executes the selected multiplication method, and measures the execution time to allow for performance comparison. For small matrices, the Standard GEMM method typically outperforms the Blocked method due to the overhead of managing blocks when the entire dataset already fits in the CPU's L1 cache.

### Directory Structure
```text
assignment_01/
├── driver/
│   └── main.cpp         # Main execution, user I/O handling, and execution timing logic
├── src/
│   └── algorithm.cpp    # Core logic and implementation of GEMM and Blocked multiplication
├── Makefile             # Compilation instructions
└── test (*).txt         # Sample matrix input files
```

### Compilation & Execution
1. Navigate to the `assignment_01` directory.
2. Compile the program using make:
   ```bash
   make
   ```
   *(Alternatively: `g++ driver/main.cpp src/algorithm.cpp -o matrix`)*
3. Run the generated executable:
   ```bash
   ./matrix
   ```
4. Follow the on-screen prompts to select the method (1 for GEMM, 2 for Blocking) and enter the blocking factor if requested.

---

## Assignment 02: Graph Representation (CSR Format)

### Overview & Working
This assignment focuses on memory-efficient graph representation. It reads graph edge data (both unweighted and weighted) and converts it into the **Compressed Sparse Row (CSR)** format.

The program interacts with the user to determine if an input graph is weighted, reads the edges from the text file, and constructs the following arrays:
* **`row_ptr` (Row Pointer):** Stores the cumulative degree (the starting index in the `col_idx` array for each vertex's outgoing edges).
* **`col_idx` (Column Index):** Stores the destination vertices for all edges in a contiguous array.
* **`weights`:** Stores the corresponding edge weights (populated only if the graph is weighted).

*Important Developer Note:* When running this code, ensure that memory allocated for `row_ptr` and `col_idx` is properly zero-initialized (e.g., using `calloc` instead of `malloc`, or utilizing `std::vector`) to prevent reading garbage memory values during execution.

### Directory Structure
```text
assignment_02/
├── driver/
│   └── main.cpp         # Core graph parsing, edge processing, and CSR array construction logic
└── test (*).txt         # Sample graph edge input files
```

### Compilation & Execution
1. Navigate to the `assignment_02/driver` directory.
2. Compile the source code:
   ```bash
   g++ main.cpp -o main
   ```
3. Run the generated executable:
   ```bash
   ./main
   ```
4. Answer the prompt (`y` or `n`) to specify whether the provided test file contains weighted edges

# CS509 Execution Report

**Assignments 01 & 02 | Performance and Memory Analysis**

## Part 1: Matrix Multiplication (Assignment 01)

*   **Overview:** This section evaluates a C++ matrix multiplication program comparing standard GEMM (General Matrix Multiply) and Blocked Matrix Multiplication (Blocking Factor = 3).
*   **Environment:** Executed in a Linux/Unix Workspace. Compiled via `g++ driver/main.cpp src/algorithm.cpp -o matrix`.

### Performance Results

| Test File | Matrix 1 Dimensions | Matrix 2 Dimensions | Standard GEMM Time (µs) | Blocked Method (µs) |
| :--- | :--- | :--- | :--- | :--- |
| test (1).txt | 20x26 | 26x10 | 31 | 43 |
| test (2).txt | 16x42 | 42x4 | 16 | 24 |
| test (3).txt | 3x8 | 8x22 | 6 | 7 |
| test (4).txt | 21x37 | 37x29 | 130 | 191 |
| test (5).txt | 4x39 | 39x10 | 10 | 16 |

### Analysis

Across all five test cases, the Standard GEMM method outperformed the Blocked method. This is highly expected for matrices of this scale. Blocking is an optimization technique designed to maximize cache efficiency for very large matrices. Because these test matrices are extremely small (e.g., 3x8, 21x37), the entire dataset readily fits within the CPU's L1 cache. The additional loop overhead required to manage the blocks causes the blocked implementation to run slower than the standard nested loops.

---

## Part 2: Graph Representation (Assignment 02)

*   **Overview:** Execution of a C++ program parsing graph data into a Compressed Sparse Row (CSR) format, utilizing `row_ptr`, `col_idx`, and `weights` arrays.
*   **Environment:** Compiled via `g++ main.cpp -o main`.

### Test Case Results

| Test File | Weighted? | `row_ptr` (Sample) | `col_idx` (Sample) | `weights` (Sample) |
| :--- | :--- | :--- | :--- | :--- |
| test (1).txt | No | 0,-756390250... | 1, 2, 2, 0 | N/A |
| test (2).txt | Yes | 0, 3, 4, 5 | 460565792, 1, 2.... | 1, 5, 3, 2, 4 |
| test (3).txt | No | 0, 4, 6, 8... | 460554948, 1, 2... | N/A |
| test (4).txt | No | 0, 3, 5, 7... | 460565980, 1, 5... | N/A |
| test (5).txt | No | 0, 5, 8, 11... | 460566144, 460566144... | N/A |