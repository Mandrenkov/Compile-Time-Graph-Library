#include "algorithm.h"

namespace ctgl {
    // Returns the distance between Node |S| and Node |T| in the |G| Graph.
    // If there is no path from |S| to |T|, INF is returned.
    template <typename G, typename S, typename T>
    constexpr int distance(G, S, T) noexcept;

    // Returns the shortest path between Node |S| and Node |T| in the |G| Graph.
    // If there is no path from |S| to |T|, an empty List is returned.
    template <typename G, typename S, typename T>
    constexpr auto path(G, S, T) noexcept;
}