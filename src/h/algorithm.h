#include "graph.h"
#include "list.h"
#include "path.h"
#include "utility.h"

namespace ctgl {

    // Declarations
    // -------------------------------------------------------------------------
    
    /*
    namespace detail {
        // Finds the shortest path between Node |S| and |T| in the Graph |G|.
        // 
        // If there is no path from |S| to |T|, an empty List is returned.
        template <typename G, typename S, typename T, typename... Ns>
        constexpr auto shortest(ADL, G, S, T, List<Ns...>) noexcept;
    }*/


    // Implementation of shortest().
    // -------------------------------------------------------------------------
    namespace detail {
        template <typename G, typename S, typename T, typename E, typename... Es, typename... Ps, typename = enable_if_diff_t<S, T>>
        constexpr auto shortest(ADL, G, S, T, List<E, Es...>, List<Ps...>) noexcept {
            // Compute the shortest path that ignores the current Edge.
            constexpr auto skip = shortest(ADL{}, G{}, S{}, T{}, List<Es...>{}, List<Ps...>{});

            // Check if following the current Edge leads to a cycle.
            constexpr auto nodes = path::nodes(List<Es...>{});
            constexpr bool cycle = list::contains(typename E::Head{}, nodes);
            if constexpr (cycle) {
                return skip;
            }

            // Compute the shortest path that follows the current Edge.
            constexpr auto next = graph::outgoing(G{}, typename E::Head{});
            constexpr auto take = shortest(ADL{}, G{}, typename E::Head{}, T{}, next, List<Ps..., E>{});

            // The shortest path is selected based on the following tabular expresssion:
            // +-------------+-------------+     +------+
            // | skip == DNE | take == DNE | --> | DNE  |
            // |             |-------------+     +------+
            // |             | take != DNE | --> | take |
            // +-------------+-------------+     +------+
            // | skip <= x   | take == DNE | --> | skip |
            // |             |-------------+     +------+
            // |             | take > x    | --> | skip |
            // +-------------+-------------+     +------+
            // | skip > x    | take == DNE | --> | skip |
            // |             |-------------+     +------+
            // |             | take <= x   | --> | take |
            // +-------------+-------------+     +------+
            if constexpr (skip == path::DNE && take == path::DNE) {
                return path::DNE;
            } else if constexpr (skip == path::DNE) {
                return take;
            } else if constexpr (take == path::DNE) {
                return skip;
            } else if constexpr (path::length(skip) <= path::length(take)) {
                return skip;
            } else {
                return take;
            }
        }

        template <typename G, typename S, typename... Ns, typename... Es>
        constexpr auto shortest(ADL, G, S, S, List<Ns...>, List<Es...>) noexcept {
            // The source Node |S| is the same as the target Node |T|.
            return List<Es...>{};
        }

        template <typename G, typename S, typename T, typename... Es, typename = enable_if_diff_t<S, T>>
        constexpr auto shortest(ADL, G, S, T, List<>, List<Es...>) noexcept {
            // The source Node |S| differs from the target Node |T| and all Edges
            // from |S| have been traversed.
            return path::DNE;
        }
    }

    // Returns the shortest path between Node |S| and Node |T| in the Graph |G|.
    // If there is no path from |S| to |T|, an empty List is returned.
    template <typename G, typename S, typename T>
    constexpr auto shortest(G, S, T) noexcept {
        constexpr auto nodes = typename G::Nodes{};
        constexpr bool memberS = list::contains(S{}, nodes);
        constexpr bool memberT = list::contains(T{}, nodes);
        constexpr bool feasible = memberS && memberT;
        if constexpr (!feasible) {
            return path::DNE;
        } else {
            constexpr auto next = graph::outgoing(G{}, S{});
            return detail::shortest(detail::ADL{}, G{}, S{}, T{}, next, List<>{});
        }
    }

    // Implementation of distance().
    // -------------------------------------------------------------------------
    // Returns the shortest distance between Node |S| and Node |T| in the Graph |G|.
    // If there is no path from |S| to |T|, INF is returned.
    template <typename G, typename S, typename T>
    constexpr int distance(G, S, T) noexcept {
        constexpr auto journey = ctgl::shortest(G{}, S{}, T{});
        if constexpr (journey == path::DNE) {
            return INF;
        } else {
            return path::length(journey);
        }
    }
}