#include <algorithm>
#include <iostream>
#include <typeinfo>

#include "list.h"
#include "graph.h"

// CTGL Constants
// -----------------------------------------------------------------------------
namespace ctgl {
    // Denotes an invalid distance (e.g., the distance between two disconnected nodes).
    constexpr int INVALID_DISTANCE = -1;
}

// CTGL Algorithms
// -----------------------------------------------------------------------------
namespace ctgl {
    // Returns the distance between Node |S| and Node |T| using a DFS algorithm.
    template <typename S, typename T>
    constexpr int dfs(S, T);
}


// CTGL Implementation
// -----------------------------------------------------------------------------
namespace ctgl {
    // Graph
    namespace detail {
        template <typename G, typename N>
        constexpr auto findEdges(G, N) -> decltype(findEdges(N{}, typename G::EdgeList{}));


        template <typename N>
        constexpr auto findEdges(N, List<>) -> List<>;

        template <typename N, typename E, typename... Es>
        constexpr auto findEdges(N, List<E, Es...>) -> decltype(findEdges(N{}, typename E::From{}, typename E::To{}, List<Es...>{}));


        template <typename N, typename F, typename T>
        constexpr auto findEdges(N, F, T, List<>) -> List<>;
    
        template <typename N, typename F, typename T, typename E, typename... Es>
        constexpr auto findEdges(N, F, T, List<E, Es...>) -> decltype(findEdges(T{}, typename E::From{}, typename E::To{}, List<Es...>{}));

        template <typename N, typename T>
        constexpr auto findEdges(N, N, T, List<>) -> List<T>;

        template <typename N, typename T, typename E, typename... Es>
        constexpr auto findEdges(N, N, T, List<E, Es...>) -> decltype(push(T{}, findEdges(N{}, typename E::From{}, typename E::To{}, List<Es...>{})));
    }

    // DFS
    namespace detail {
        template <typename S, typename T, typename N, typename... Es> constexpr int dfs(S, T, List<N, Es...>);
        template <typename S, typename T>                             constexpr int dfs(S, T, List<>);
        template <typename T, typename... Es>                         constexpr int dfs(T, T, List<Es...>);
        template <typename T>                                         constexpr int dfs(T, T, List<>);

        template <typename T, typename... Es>
        constexpr int dfs(T, T, List<Es...>) {
            return 0;
        }

        template <typename T>
        constexpr int dfs(T, T, List<>) {
            return 0;
        }

        template <typename S, typename T, typename N, typename... Es>
        constexpr int dfs(S, T, List<N, Es...>) {
            constexpr int branch = dfs(N{}, T{}, typename N::EdgeList{});
            constexpr int skip = dfs(S{}, T{}, List<Es...>{});
            if constexpr (skip == INVALID_DISTANCE && branch == INVALID_DISTANCE) {
                return INVALID_DISTANCE;
            } else if constexpr (skip == INVALID_DISTANCE && branch != INVALID_DISTANCE) {
                return branch + 1;
            } else if constexpr (skip != INVALID_DISTANCE && branch == INVALID_DISTANCE) {
                return skip;
            } else {
                return std::min(skip, branch + 1);
            }
        }

        template <typename S, typename T>
        constexpr int dfs(S, T, List<>) {
            return INVALID_DISTANCE;
        }
    }

    template <typename G, typename S, typename T>
    constexpr int dfs(G, S, T) {
        return detail::dfs(G{}, S{}, T{}, typename S::EdgeList{});
    }
}