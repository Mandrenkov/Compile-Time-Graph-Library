#pragma once

//#include <type_traits>

#include "list.h"

namespace ctgl {
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

    namespace detail {
        // DetailADL must be passed as the first argument to each function to
        // ensure that ADL can resolve recursive trailing return types.
        struct DetailADL {};

        template <typename N>
        constexpr auto adjacent(DetailADL, N, List<>) -> decltype(List<>{});

        template <typename N, typename T, typename... Es>
        constexpr auto adjacent(DetailADL, N, List<Edge<N, T>, Es...>) -> decltype(push(T{}, adjacent(DetailADL{}, N{}, List<Es...>{})));

        template <typename N, typename F, typename T, typename... Es>
        constexpr auto adjacent(DetailADL, N, List<Edge<F, T>, Es...>) -> decltype(adjacent(DetailADL{}, N{}, List<Es...>{}));
    }

    // Returns a List of Nodes in the |G| graph that are adjacent to the |N| Node.
    template <typename G, typename N>
    constexpr auto adjacent(G, N) -> decltype(detail::adjacent(detail::DetailADL{}, N{}, typename G::Edges{}));
}