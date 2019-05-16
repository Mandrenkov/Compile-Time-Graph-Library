## Source Repository Guide

### `cpp`

The `cpp` directory implements the example in the root README.

| File                         | Contents                            |
|---                           |---                                  |
| [ctgl.cpp](cpp/ctgl.cpp)     | Example from the root README.       |


### `h`

The `h` directory implements the CTGL.

| File                         | Contents                            |
|---                           |---                                  |
| [algorithm.h](h/algorithm.h) | Graph algorithm definitions.        |
| [ctgl.h](h/ctgl.h)           | Graph algorithm declarations.       |
| [graph.h](h/graph.h)         | `Graph` data structure definitions. |
| [list.h](h/list.h)           | `List` data structure definitions.  |
| [utility.h](h/utility.h)     | Constants and template utilities.   |

### `test`

The `test` directory contains unit tests for the CTGL.

| File                         | Contents                            |
|---                           |---                                  |
| [algorithm_test.cpp](test/algorithm_test.cpp) | Unit tests for graph algorithms. |
| [forge.h](test/forge.h)                       | Repository of test graphs. |
| [graph_test.cpp](test/graph_test.cpp)         | Unit tests for `Graph`. |
| [list_test.cpp](test/list_test.cpp)           | Unit tests for `List`. |