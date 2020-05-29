# Compile Time Graph Library ![Travis Status](https://travis-ci.org/Mandrenkov/Compile-Time-Graph-Library.svg?branch=master)
The Compile Time Graph Library (CTGL) implements `constexpr` graph algorithms and data structures.

## Example
The following code snippet demonstrates a basic usage of CTGL.  Simply include `ctgl.h` and you're set!
```C++
// Create Nodes with IDs 1, 2, and 3.
using n1 = ctgl::Node<1>;
using n2 = ctgl::Node<2>;
using n3 = ctgl::Node<3>;
using nodes = ctgl::List<n1, n2, n3>;

// Create Edges that connect some of the Nodes.
// (1) --4--> (2) --4--> (3)
//  `----------9----------^
using e12 = ctgl::Edge<n1, n2, 4>;
using e13 = ctgl::Edge<n1, n3, 9>;
using e23 = ctgl::Edge<n2, n3, 4>;
using edges = ctgl::List<e12, e13, e23>;

// Compose the Nodes and Edges to form a Graph.
using graph = ctgl::Graph<nodes, edges>;

// Find the distance between Node 1 and Node 3 (i.e., 8).
constexpr int dist = ctgl::algorithm::findDistance(graph{}, n1{}, n3{});
```

## Build Instructions
| Command      | Objective                              |
|---           |---                                     |
| `make all`   | Build the CTGL and run the examples.   |
| `make test`  | Build the CTGL and run the test suite. |
| `make clean` | Clean the current directory.           |

**Note:** You can specify a compiler flag to any of the build commands to select a different compiler target.  For example, to build the test suite using Clang, run `make test COMPILER=clang++`.
