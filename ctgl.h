#include <algorithm>

namespace ctgl {
    // List represents the list of types given by |Ts|.
    template <typename... Ts>
    struct List {};

    // A |List| specialization without any types.
    using EmptyList = List<>;
}

// The public interface of the CTGL.
namespace ctgl {
    template <typename S, typename T>
    constexpr int dfs(S, T);
}

namespace ctgl {
    constexpr int NOT_FOUND = -1;

    // List represents the list of types given by |Ts|.
    template <int ID, typename... Es>
    struct Node {
        static constexpr int id = ID;
        using EdgeList = List<Es...>;
    };

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
            if constexpr (skip == NOT_FOUND && branch == NOT_FOUND) {
                return NOT_FOUND;
            } else if constexpr (skip == NOT_FOUND && branch != NOT_FOUND) {
                return branch + 1;
            } else if constexpr (skip != NOT_FOUND && branch == NOT_FOUND) {
                return skip;
            } else {
                return std::min(skip, branch + 1);
            }
        }

        template <typename S, typename T>
        constexpr int dfs(S, T, List<>) {
            return NOT_FOUND;
        }
    }

    template <typename S, typename T>
    constexpr int dfs(S, T) {
        return detail::dfs(S{}, T{}, typename S::EdgeList{});
    }
}