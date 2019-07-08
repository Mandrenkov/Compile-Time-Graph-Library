#pragma once

#include "list.h"
#include "utility.h"

namespace ctgl {

    // Declarations
    // -------------------------------------------------------------------------

    namespace graph {
        // Node represents a node with the |ID| identifier.
        template <int ID>
        struct Node {
            static constexpr int id = ID;
        };

        // Edge represents a directed edge from the Node |F| to the Node |T| with positive weight |W|.
        template<typename F, typename T, int W = 1, typename = std::enable_if_t<W >= 0>>
        struct Edge {
            using From = F;
            using To = T;
            static constexpr int weight = W;
        };

        // Graph represents a graph consisting of the |N| nodes and |E| edges.
        template <typename N, typename E>
        struct Graph {
            using Nodes = N;
            using Edges = E;
        };

        // Finds all Nodes adjacent to the given Node in the provided Graph.
        template <typename G, typename N>
        constexpr auto adjacent(G, N);

        // Finds all Nodes connected to the given Node in the provided Graph.
        template <typename G, typename N>
        constexpr auto connected(G, N);
    }

    // Definitions
    // -------------------------------------------------------------------------

    namespace graph {
        template <typename G, typename N>
        constexpr auto adjacent(G, N) {
            return list::unique(adjacent(N{}, typename G::Edges{}));
        }

        template <typename N, typename T, int W, typename... Es>
        constexpr auto adjacent(N, List<Edge<N, T, W>, Es...>) {
            // The first Edge in the List originates from the source Node.
            return T{} + adjacent(N{}, List<Es...>{});
        }

        template <typename N, typename F, typename T, int W, typename... Es>
        constexpr auto adjacent(N, List<Edge<F, T, W>, Es...>) {
            // The first Edge in the List does NOT originate from the source Node.
            return adjacent(N{}, List<Es...>{});
        }

        template <typename N>
        constexpr auto adjacent(N, List<>) {
            // All the Edges have been traversed.
            return List<>{};
        }

        template <typename G, typename N>
        constexpr auto connected(G, N) {
            constexpr bool feasible = list::contains(N{}, typename G::Nodes{});
            if constexpr (feasible) {
                return list::unique(N{} + connected(G{}, N{}, adjacent(G{}, N{})));
            } else {
                return List<>{};
            }
        }

        template <typename G, typename N, typename T, typename... Ts, typename = ctgl::detail::enable_if_different_t<N, T>>
        constexpr auto connected(G, N, List<T, Ts...>) {
            // The first Node in the adjacency List connects to a Node other than the target Node.
            return T{} + connected(G{}, N{}, List<Ts...>{}) + connected(G{}, T{}, adjacent(G{}, T{}));
        }

        template <typename G, typename N, typename... Ts>
        constexpr auto connected(G, N, List<N, Ts...>) {
            // The first Node in the adjacency List loops back to the target Node.
            return connected(G{}, N{}, List<Ts...>{});
        }

        template <typename G, typename N>
        constexpr auto connected(G, N, List<>) {
            // All the Edges have been traversed.
            return List<>{};
        }
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template <int ID>
    using Node = ctgl::graph::Node<ID>;

    template<typename F, typename T, int W>
    using Edge = ctgl::graph::Edge<F, T, W>;

    template <typename N, typename E>
    using Graph = ctgl::graph::Graph<N, E>;
}