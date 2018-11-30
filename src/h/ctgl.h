#include "algorithm.h"

namespace ctgl {
    // Returns the distance between Node |S| and Node |T| in the |G| Graph.
    // If there is no path from |S| to |T|, INF is returned.
    template <typename G, typename S, typename T>
    constexpr int distance(G, S, T);

    // Returns the shortest path between Node |S| and Node |T| in the |G| Graph.
    // If there is no path from |S| to |T|, an empty List is returned.
    template <typename G, typename S, typename T>
    constexpr auto path(G, S, T);

    // Returns the furthest Node from the |N| Node in the |G| Graph.  If more than
    // one Node fits this criterion, only one of the furthest Nodes is returned.
    // template <typename G, typename N>
    // constexpr auto furthest(G, N);
}