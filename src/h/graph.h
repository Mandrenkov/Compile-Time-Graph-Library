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

        // Returns the Nodes in the Graph |G| that are adjacent to Node |N|.
        template <typename N>
        constexpr auto adjacent(N, List<>) -> decltype(List<>{});

        template <typename N, typename T, typename... Es>
        constexpr auto adjacent(N, List<Edge<N, T>, Es...>) -> decltype(push(T{}, adjacent(N{}, List<Es...>{})));

        template <typename N, typename F, typename T, typename... Es>
        constexpr auto adjacent(N, List<Edge<F, T>, Es...>) -> decltype(adjacent(N{}, List<Es...>{}));

        template <typename G, typename N>
        constexpr auto adjacent(G, N) -> decltype(adjacent(N{}, typename G::Edges{}));
        

        // Returns the Nodes in the Graph |G| that are connected to Node |N|.
        template <typename G, typename N>
        constexpr auto connected(G, N, List<>) -> decltype(List<>{});

        template <typename G, typename N, typename... Ts>
        constexpr auto connected(G, N, List<N, Ts...>) -> decltype(connected(G{}, N{}, List<Ts...>{}));

        template <typename G, typename N, typename T, typename... Ts, typename = ctgl::detail::enable_if_different_t<N, T>>
        constexpr auto connected(G, N, List<T, Ts...>) -> decltype(list::push(T{}, list::link(connected(G{}, N{}, List<Ts...>{}), connected(G{}, T{}, adjacent(G{}, T{})))));

        template <typename G, typename N>
        constexpr auto connected(G, N) {
            constexpr bool feasible = list::contains(N{}, typename G::Nodes{});
            if constexpr (!feasible) {
                // The Graph does not contain Node |N|.
                return List<>{};
            } else {
                // The Graph contains Node |N|.
                return decltype(list::unique(list::push(N{}, connected(G{}, N{}, adjacent(G{}, N{}))))){};
            }
        }
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