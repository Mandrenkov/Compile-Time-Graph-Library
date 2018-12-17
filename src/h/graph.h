#pragma once

#include "list.h"
#include "utility.h"

namespace ctgl {
    namespace graph {
        // Node represents a node with the |ID| identifier.
        template <int ID>
        struct Node {
            static constexpr int id = ID;
        };

        // Edge represents a directed edge from the |F| Node to the |T| Node.
        template<typename F, typename T>
        struct Edge {
            using From = F;
            using To = T;
        };

        // Graph represents a graph consisting of the |N| nodes and |E| edges.
        template <typename N, typename E>
        struct Graph {
            using Nodes = N;
            using Edges = E;
        };


        // Compile-Time Functions
        // -------------------------------------------------------------------------

        // Returns a List of Nodes in the |G| Graph that are adjacent to the |N| Node.
        template <typename N>
        constexpr auto adjacent(N, List<>) -> decltype(List<>{});

        template <typename N, typename T, typename... Es>
        constexpr auto adjacent(N, List<Edge<N, T>, Es...>) -> decltype(push(T{}, adjacent(N{}, List<Es...>{})));

        template <typename N, typename F, typename T, typename... Es>
        constexpr auto adjacent(N, List<Edge<F, T>, Es...>) -> decltype(adjacent(N{}, List<Es...>{}));

        template <typename G, typename N>
        constexpr auto adjacent(G, N) -> decltype(adjacent(N{}, typename G::Edges{}));
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template <int ID>
    using Node = ctgl::graph::Node<ID>;

    template<typename F, typename T>
    using Edge = ctgl::graph::Edge<F, T>;

    template <typename N, typename E>
    using Graph = ctgl::graph::Graph<N, E>;
}