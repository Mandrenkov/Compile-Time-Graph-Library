# Compile Time Graph Library ![Travis Status](https://travis-ci.org/Mandrenkov/Compile-Time-Graph-Library.svg?branch=master)
The Compile Time Graph Library (CTGL) is a library that can execute graph algorithms during compilation.

## Build Instructions
| Objective                         | Command |
|---                                |---      |
| Build the CTGL executable         | `make all` |
| Build the run the CTGL test suite | `make test` |
| Clean the current directory       | `make clean` |

**Note:** You can specify a compiler flag to any of the build commands to select a different compiler target.  For example, to build the test suite using Clang, run `make test COMPILER=clang`.
