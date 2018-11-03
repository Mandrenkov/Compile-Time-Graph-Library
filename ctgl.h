#include <algorithm>

// CTGL Constants
// -----------------------------------------------------------------------------
namespace ctgl {
    // Denotes an invalid distance (e.g., the distance between two disconnected nodes).
    constexpr int INVALID_DISTANCE = -1;
}

// CTGL Data Structures
// -----------------------------------------------------------------------------
namespace ctgl {
    // List represents the list of types specified by |Ts|.
    template <typename... Ts>
    struct List {};

    // Node represents a graph node with the given ID and edges.
    template <int ID, typename... Es>
    struct Node {
        static constexpr int id = ID;
        using EdgeList = List<Es...>;
    };
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

    template <typename S, typename T>
    constexpr int dfs(S, T) {
        return detail::dfs(S{}, T{}, typename S::EdgeList{});
    }
}