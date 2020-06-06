#pragma once

#include "graph.h"
#include "list.h"
#include "path.h"
#include "utility.h"

namespace ctgl {

    // Declarations
    // -------------------------------------------------------------------------
    
    namespace algorithm {
        // Finds the shortest path (without negative cycles) between Node |S| and
        // Node |T| in the Graph |G|.  If there is no path from |S| to |T|, DNE
        // is returned.
        template <typename G, typename S, typename T>
        constexpr auto findShortestPath(G, S, T) noexcept;

        // Finds the shortest route (without negative cycles) in the Graph |G|
        // that starts at Node |S|, visits each Node in |Ns|, and then returns
        // back to Node |S|.  If such a route does not exist, DNE is returned.
        template <typename G, typename S, typename... Ns>
        constexpr auto findShortestRoute(G, S, List<Ns...>) noexcept;

        // Finds the distance (ignoring negative cycles) between Node |S| and
        // Node |T| in the Graph |G|.  If there is no path from |S| to |T|, INF
        // is returned.
        template <typename G, typename S, typename T>
        constexpr int findDistance(G, S, T) noexcept;
    }

    // Definitions
    // -------------------------------------------------------------------------

    namespace algorithm {
        template <typename G, typename S, typename T, typename... Ps, typename = ctgl::util::enable_if_diff_t<S, T>>
        constexpr auto findShortestPath(G, S, T, List<>, List<Ps...>) noexcept {
            // The source Node |S| differs from the target Node |T| and all Edges
            // from |S| have been traversed.
            return path::DNE;
        }

        template <typename G, typename S, typename... Ns, typename... Ps>
        constexpr auto findShortestPath(G, S, S, List<Ns...>, List<Ps...>) noexcept {
            // The source Node |S| is the same as the target Node |T|.
            return List<Ps...>{};
        }

        template <typename G, typename S, typename T, typename E, typename... Es, typename... Ps, typename = ctgl::util::enable_if_diff_t<S, T>>
        constexpr auto findShortestPath(G, S, T, List<E, Es...>, List<Ps...>) noexcept {
            // Compute the shortest path that ignores the current Edge.
            constexpr auto skip = findShortestPath(G{}, S{}, T{}, List<Es...>{}, List<Ps...>{});

            // Check if following the current Edge leads to a cycle.
            constexpr auto seen = List<S>{} + path::nodes(List<Ps...>{});
            constexpr bool cycle = list::contains(typename E::Head{}, seen);
            if constexpr (cycle) {
                return skip;
            } else {
                // Compute the shortest path that follows the current Edge.
                constexpr auto next = graph::getOutgoingEdges(G{}, typename E::Head{});
                constexpr auto take = findShortestPath(G{}, typename E::Head{}, T{}, next, List<Ps..., E>{});
                return path::shortest(skip, take);
            }
        }

        template <typename G, typename S, typename T>
        constexpr auto findShortestPath(G, S, T) noexcept {
            constexpr auto nodes = typename G::Nodes{};
            constexpr bool hasS = list::contains(S{}, nodes);
            constexpr bool hasT = list::contains(T{}, nodes);
            constexpr bool feasible = hasS && hasT;
            if constexpr (!feasible) {
                return path::DNE;
            } else {
                constexpr auto next = graph::getOutgoingEdges(G{}, S{});
                return findShortestPath(G{}, S{}, T{}, next, List<>{});
            }
        }

        template <typename G, typename N1, typename N2>
        constexpr auto findShortestPaths(G, List<N1, N2>) noexcept {
            return findShortestPath(G{}, N1{}, N2{});
        }

        template <typename G, typename N1, typename N2, typename N3, typename... Ns>
        constexpr auto findShortestPaths(G, List<N1, N2, N3, Ns...>) noexcept {
            constexpr auto head = findShortestPath(G{}, N1{}, N2{});
            if constexpr (head == path::DNE) {
                return path::DNE;
            } else {
                constexpr auto tail = findShortestPaths(G{}, List<N2, N3, Ns...>{});
                return path::join(head, tail);
            }
        }

        template <typename G>
        constexpr auto findShortestRoutes(G, List<>) noexcept {
            return path::DNE;
        }

        template <typename G, typename... O, typename... Os>
        constexpr auto findShortestRoutes(G, List<List<O...>, Os...>) noexcept {
            constexpr auto take = findShortestPaths(G{}, List<O...>{});
            constexpr auto skip = findShortestRoutes(G{}, List<Os...>{});
            return path::shortest(take, skip);
        }

        template <typename G, typename S, typename... Ns>
        constexpr auto findShortestRoute(G, S, List<Ns...>) noexcept {
            constexpr auto unique = list::remove(S{}, list::unique(List<Ns...>{}));
            constexpr auto middle = list::permutations(unique);
            constexpr auto orders = S{} * middle * S{};
            if constexpr (list::empty(orders)) {
                return findShortestRoutes(G{}, List<List<S, S>>{});
            } else {
                return findShortestRoutes(G{}, orders);
            }
        }

        template <typename G, typename S, typename T>
        constexpr int findDistance(G, S, T) noexcept {
            constexpr auto journey = findShortestPath(G{}, S{}, T{});
            if constexpr (journey == path::DNE) {
                return INF;
            } else {
                return path::length(journey);
            }
        }
    }
}