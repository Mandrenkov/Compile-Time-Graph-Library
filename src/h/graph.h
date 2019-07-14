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

        // Edge represents a directed edge from the tail Node |T| to the head
        // Node |H| with positive weight |W|.
        template<typename T, typename H, int W = 1, typename = std::enable_if_t<W >= 0>>
        struct Edge {
            using Tail = T;
            using Head = H;
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
        constexpr auto adjacent(G, N) noexcept;

        // Finds all Nodes connected to the given Node in the provided Graph.
        template <typename G, typename N>
        constexpr auto connected(G, N) noexcept;

        // Finds all outgoing Edges from the given Node in the provided Graph.
        template <typename G, typename N>
        constexpr auto outgoing(G, N) noexcept;
    }

    // Definitions
    // -------------------------------------------------------------------------

    namespace graph {
        template <typename G, typename N>
        constexpr auto adjacent(G, N) noexcept {
            return list::unique(adjacent(N{}, typename G::Edges{}));
        }

        template <typename N, typename H, int W, typename... Es>
        constexpr auto adjacent(N, List<Edge<N, H, W>, Es...>) noexcept {
            // The first Edge in the List originates from the source Node.
            return H{} + adjacent(N{}, List<Es...>{});
        }

        template <typename N, typename E, typename... Es>
        constexpr auto adjacent(N, List<E, Es...>) noexcept {
            // The first Edge in the List does NOT originate from the source Node.
            return adjacent(N{}, List<Es...>{});
        }

        template <typename N>
        constexpr auto adjacent(N, List<>) noexcept {
            // All the Edges have been traversed.
            return List<>{};
        }

        template <typename G, typename N>
        constexpr auto connected(G, N) noexcept {
            constexpr bool feasible = list::contains(N{}, typename G::Nodes{});
            if constexpr (feasible) {
                constexpr auto next = adjacent(G{}, N{});
                constexpr auto span = connected(G{}, N{}, next, List<N>{});
                return list::unique(span);
            } else {
                return List<>{};
            }
        }

        template <typename G, typename N, typename T, typename... Ts, typename... Ps>
        constexpr auto connected(G, N, List<T, Ts...>, List<Ps...>) noexcept {
            constexpr auto skip = connected(G{}, N{}, List<Ts...>{}, List<Ps...>{});
            constexpr auto cycle = list::contains(T{}, List<Ps...>{});
            if constexpr (cycle) {
                return skip;
            } else {
                constexpr auto next = adjacent(G{}, T{});
                constexpr auto take = connected(G{}, T{}, next, List<T, Ps...>{});
                return skip + take;
            }
        }

        template <typename G, typename N, typename... Ps>
        constexpr auto connected(G, N, List<>, List<Ps...>) noexcept {
            return List<Ps...>{};
        }

        template <typename G, typename N>
        constexpr auto outgoing(G, N) noexcept {
            return list::unique(outgoing(N{}, typename G::Edges{}));
        }

        template <typename N, typename E, typename... Es>
        constexpr auto outgoing(N, List<E, Es...>) noexcept {
            constexpr bool match = std::is_same_v<N, typename E::Tail>;
            constexpr auto after = outgoing(N{}, List<Es...>{});
            if constexpr (match) {
                return E{} + after;
            } else {
                return after;
            }
        }

        template <typename N>
        constexpr auto outgoing(N, List<>) noexcept {
            return List<>{};
        }
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template <int ID>
    using Node = ctgl::graph::Node<ID>;

    template<typename T, typename H, int W>
    using Edge = ctgl::graph::Edge<T, H, W>;

    template <typename N, typename E>
    using Graph = ctgl::graph::Graph<N, E>;
}