#include "graph.h"
#include "list.h"
#include "utility.h"

namespace ctgl {
    // Implementation of distance().
    namespace detail {
        template <typename G, typename S, typename... Ns>
        constexpr int distance(ADL, G, S, S, List<Ns...>) {
            return 0;
        }

        template <typename G, typename S, typename T, typename N, typename... Ns, typename = enable_if_different_t<S, T>>
        constexpr int distance(ADL, G, S, T, List<N, Ns...>) {
            constexpr int skip = distance(ADL{}, G{}, S{}, T{}, List<Ns...>{});
            constexpr int branch = distance(ADL{}, G{}, N{}, T{}, decltype(adjacent(G{}, N{})){});
            return branch == INF ? skip : std::min(skip, branch + 1);
        }

        template <typename G, typename S, typename T, typename = enable_if_different_t<S, T>>
        constexpr int distance(ADL, G, S, T, List<>) {
            return INF;
        }
    }

    template <typename G, typename S, typename T>
    constexpr int distance(G, S, T) {
        constexpr bool feasible = contains(S{}, typename G::Nodes{}) && contains(T{}, typename G::Nodes{});
        return feasible ? detail::distance(detail::ADL{}, G{}, S{}, T{}, decltype(adjacent(G{}, S{})){}) : INF;
    }

    // Implementation of path().
    namespace detail {
        template <typename G, typename S, typename... Ns>
        constexpr auto path(ADL, G, S, S, List<Ns...>) {
            return List<S>{};
        }

        template <typename G, typename S, typename T, typename N, typename... Ns, typename = enable_if_different_t<S, T>>
        constexpr auto path(ADL, G, S, T, List<N, Ns...>) {
            constexpr auto skip = path(ADL{}, G{}, S{}, T{}, List<Ns...>{});
            constexpr auto branch = path(ADL{}, G{}, N{}, T{}, decltype(adjacent(G{}, N{})){});

            if constexpr (empty(skip) && empty(branch)) {
                return List<>{};
            } else if constexpr (empty(skip)) {
                return decltype(push(S{}, branch)){};
            } else if constexpr (empty(branch)) {
                return skip;
            } else if constexpr (size(skip) > size(branch)) {
                return decltype(push(S{}, branch)){};
            } else {
                return skip;
            }
        }

        template <typename G, typename S, typename T, typename = enable_if_different_t<S, T>>
        constexpr auto path(ADL, G, S, T, List<>) {
            return List<>{};
        }
    }

    template <typename G, typename S, typename T>
    constexpr auto path(G, S, T) {
        constexpr auto nodes = typename G::Nodes{};
        constexpr bool feasible = contains(S{}, nodes) && contains(T{}, nodes);
        if constexpr (!feasible) {
            return List<>{};
        } else {
            constexpr auto next = decltype(adjacent(G{}, S{})){};
            return detail::path(detail::ADL{}, G{}, S{}, T{}, next);
        }
    }
}