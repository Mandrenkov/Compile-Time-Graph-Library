#include "graph.h"
#include "list.h"
#include "utility.h"

namespace ctgl {
    // Implementation of path().
    // -------------------------------------------------------------------------
    namespace detail {
        // [Template Specialization] The source Node |S| differs from the target
        // Node |T| and there is at least one Edge from |S| that has yet to be traversed.
        template <typename G, typename S, typename T, typename N, typename... Ns, typename = enable_if_different_t<S, T>>
        constexpr auto path(ADL, G, S, T, List<N, Ns...>) noexcept {
            constexpr auto skip = path(ADL{}, G{}, S{}, T{}, List<Ns...>{});
            constexpr auto branch = path(ADL{}, G{}, N{}, T{}, decltype(graph::adjacent(G{}, N{})){});

            if constexpr (list::empty(skip) && list::empty(branch)) {
                // Node |T| is not reachable from Node |S|.
                return List<>{};
            } else if constexpr (list::empty(skip)) {
                // Node |T| is transitively connected to Node |S| through Node |N|.
                return S{} + branch;
            } else if constexpr (list::empty(branch)) {
                // Node |T| is transivitely connected to Node |S| through a Node in |Ns|.
                return skip;
            } else if constexpr (list::size(skip) > list::size(branch)) {
                // The shortest path to Node |T| from Node |S| is through Node |N|.
                return S{} + branch;
            } else {
                // The shortest path to Node |T| from Node |S| is through a Node in |Ns|.
                return skip;
            }
        }

        // [Template Specialization] The source Node |S| is the same as the target Node |T|.
        template <typename G, typename S, typename... Ns>
        constexpr auto path(ADL, G, S, S, List<Ns...>) noexcept {
            return List<S>{};
        }

        // [Template Specialization] The source Node |S| differs from the target
        // Node |T| and all Edges from |S| have been traversed.
        template <typename G, typename S, typename T, typename = enable_if_different_t<S, T>>
        constexpr auto path(ADL, G, S, T, List<>) noexcept {
            return List<>{};
        }
    }

    // Returns the shortest path between Node |S| and Node |T| in the |G| Graph.
    // If there is no path from |S| to |T|, an empty List is returned.
    template <typename G, typename S, typename T>
    constexpr auto path(G, S, T) noexcept {
        constexpr auto nodes = typename G::Nodes{};
        constexpr bool feasible = list::contains(S{}, nodes) && list::contains(T{}, nodes);
        if constexpr (!feasible) {
            // The Graph is missing Node |S| or Node |T|.
            return List<>{};
        } else {
            // The Graph contains both Node |S| and Node |T|.
            return detail::path(detail::ADL{}, G{}, S{}, T{}, decltype(graph::adjacent(G{}, S{})){});
        }
    }

    // Implementation of distance().
    // -------------------------------------------------------------------------
    // Returns the shortest distance between Node |S| and Node |T| in the Graph |G|.
    // If there is no path from |S| to |T|, INF is returned.
    template <typename G, typename S, typename T>
    constexpr int distance(G, S, T) noexcept {
        constexpr auto size = list::size(ctgl::path(G{}, S{}, T{}));
        return size == 0 ? ctgl::INF : size - 1;
    }
}