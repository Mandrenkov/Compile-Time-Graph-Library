## Source Repository Guide

The `cpp` directory implements the examples from the root README.

| File                         | Description                   |
|---                           |---                            |
| [ctgl.cpp](cpp/ctgl.cpp)     | Example from the root README. |

The `h` directory implements the CTGL.  This directory contains everything needed to use CTGL in an external project.

| File                         | Description                         |
|---                           |---                                  |
| [algorithm.h](h/algorithm.h) | Graph algorithm definitions.        |
| [ctgl.h](h/ctgl.h)           | Graph algorithm declarations.       |
| [graph.h](h/graph.h)         | `Graph` data structure definitions. |
| [list.h](h/list.h)           | `List` data structure definitions.  |
| [path.h](h/path.h)           | `Path` data structure definitions.  |
| [utility.h](h/utility.h)     | Template metaprogramming utilities. |

The `test` directory contains unit tests for the CTGL.  Unit tests are written using the [Google Test](https://github.com/google/googletest) framework.

| File                                          | Description                      |
|---                                            |---                               |
| [algorithm_test.cpp](test/algorithm_test.cpp) | Unit tests for graph algorithms. |
| [forge.h](test/forge.h)                       | Graph repository for testing.    |
| [graph_test.cpp](test/graph_test.cpp)         | Unit tests for `Graph`.          |
| [list_test.cpp](test/list_test.cpp)           | Unit tests for `List`.           |
| [path_test.cpp](test/path_test.cpp)           | Unit tests for `Path`.           |
