# Compile Time Graph Library ![Travis Status](https://travis-ci.org/Mandrenkov/Compile-Time-Graph-Library.svg?branch=master)
The *Compile Time Graph Library* (CTGL) is a C++ header-only library that implements `constexpr` graph algorithms.

## Setup
To integrate CTGL with your project, add the files in the [header](src/h) directory to your include path.  Then, include [`ctgl.h`](src/h/ctgl.h) in the source files of your choice!

**Note:** This library uses C++17 features.

## Examples
The first example finds the shortest distance between two nodes in a graph.
```C++
// The nodes of a CTGL graph are ctgl::Node<> types with unique ID parameters.
using n1 = ctgl::Node<1>;
using n2 = ctgl::Node<2>;
using n3 = ctgl::Node<3>;
using nodes = ctgl::List<n1, n2, n3>;

// The directed, weighted edges of a CTGL graph are ctgl::Edge<> types.
// 1 --(4)--> 2 --(4)--> 3
// '---------(9)---------^
using e12 = ctgl::Edge<n1, n2, 4>;
using e13 = ctgl::Edge<n1, n3, 9>;
using e23 = ctgl::Edge<n2, n3, 4>;
using edges = ctgl::List<e12, e13, e23>;

// By definition, a Graph is a composition of Nodes and Edges.
using graph = ctgl::Graph<nodes, edges>;

// |distance| represents the (shortest) distance between Node 1 and Node 3.
// In this case, the value of |distance| will be 8.
constexpr int distance = ctgl::algorithm::findDistance(graph{}, n1{}, n3{});
```

The second example solves the [Travelling Salesman Problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem) in O(1) running time.
```C++
// Nodes represent cities in the TSP instance.
using dubai = ctgl::Node<1>;
using miami = ctgl::Node<2>;
using paris = ctgl::Node<3>;
using tokyo = ctgl::Node<4>;
using cities = ctgl::List<dubai, miami, paris, tokyo>;

// Edges represent unidirectional routes between cities.
//                  .-------------(1)-------------v
// Dubai --(1)--> Miami --(2)--> Paris --(1)--> Tokyo
// ^   ^-----------(3)-----------'   ^---(4)----'   |
// '----------------------(3)-----------------------'
using routes = ctgl::List<ctgl::Edge<dubai, miami, 1>,
                          ctgl::Edge<miami, paris, 2>,
                          ctgl::Edge<miami, tokyo, 1>,
                          ctgl::Edge<paris, dubai, 3>,
                          ctgl::Edge<paris, tokyo, 1>,
                          ctgl::Edge<tokyo, dubai, 3>,
                          ctgl::Edge<tokyo, paris, 4>>;

// |circuit| represents an optimal solution to the TSP instance from Dubai.
// The type of |circuit| will express Dubai --> Miami --> Paris --> Tokyo --> Dubai.
using world = ctgl::Graph<cities, routes>;
constexpr auto circuit = ctgl::algorithm::findShortestRoute(world{}, dubai{}, cities{});
```

The third example detects opportunities for arbitrage in a foreign exchange market.
```C++
// Nodes represent currencies in the foreign exchange market.
using aud = ctgl::Node<1>;
using cad = ctgl::Node<2>;
using nzd = ctgl::Node<3>;
using usd = ctgl::Node<4>;
using currencies = ctgl::List<aud, cad, nzd, usd>;

// Edges represent logarithmic exchange rates between currencies. Why? If the
// product of the exchange rates along a cycle is less than one, then the sum
// of the logarithmic exchanges rates along that cycle must be less than zero.
//                v----------(-2)----------.
// NZD --(1)--> AUD --(-3)--> CAD --(3)--> USD
using log_rates = ctgl::List<ctgl::Edge<nzd, aud,  1>,
                             ctgl::Edge<aud, cad, -3>,
                             ctgl::Edge<cad, usd,  3>,
                             ctgl::Edge<usd, aud, -2>>;

// |arbitrage| represents the possibility of arbitrage in the currency market.
// Here, |arbitrage| will be set to true because AUD --> CAD --> USD --> AUD
// forms a negative cycle.
using market = ctgl::Graph<currencies, log_rates>;
constexpr bool arbitrage = ctgl::graph::hasNegativeCycle(market{});
```

## Development
| Command      | Description                        |
|---           |---                                 |
| `make all`   | Build and run the CTGL examples.   |
| `make test`  | Build and run the CTGL test suite. |
| `make clean` | Clean the current directory.       |

You can provide a `COMPILER` or `FLAGS` argument to any of the build commands to select a different compiler or add custom flags to a compiler invocation. For example, to build the test suite using Clang, use `make test COMPILER=clang++`.
