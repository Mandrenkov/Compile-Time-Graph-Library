# Compile Time Graph Library ![Travis Status](https://travis-ci.org/Mandrenkov/Compile-Time-Graph-Library.svg?branch=master)
The Compile Time Graph Library (CTGL) is a library that can execute graph algorithms during compilation.

## Example
The following code snippet demonstrates a basic usage of CTGL.  Simply include `ctgl.h` and you're set!
```C++
// 1 --> 2 --> 3
// ^-----------'
using n1 = ctgl::Node<1>;
using n2 = ctgl::Node<2>;
using n3 = ctgl::Node<3>;
using nodes = ctgl::List<n1, n2, n3>;

using e12 = ctgl::Edge<n1, n2>;
using e23 = ctgl::Edge<n2, n3>;
using e31 = ctgl::Edge<n3, n1>;
using edges = ctgl::List<e12, e23, e31>;

using graph = ctgl::Graph<nodes, edges>;

// Find the shortest path between (1) and (3) (i.e., ctgl::List<n1, n2, n3>).
constexpr auto shortest = ctgl::path(graph{}, n1{}, n3{});
```

## Build Instructions
| Objective                         | Command |
|---                                |---      |
| Build the CTGL executable         | `make all` |
| Build the run the CTGL test suite | `make test` |
| Clean the current directory       | `make clean` |

**Note:** You can specify a compiler flag to any of the build commands to select a different compiler target.  For example, to build the test suite using Clang, run `make test COMPILER=clang`.
