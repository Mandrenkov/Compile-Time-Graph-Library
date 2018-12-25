#include "../h/graph.h"

using namespace ctgl;

namespace forge {
    // Nodes
    // -------------------------------------------------------------------------
    using N1 = Node<1>;
    using N2 = Node<2>;
    using N3 = Node<3>;
    using N4 = Node<4>;

    // Edges
    // -------------------------------------------------------------------------
    using E11 = Edge<N1, N1>;
    using E12 = Edge<N1, N2>;
    using E13 = Edge<N1, N3>;
    using E14 = Edge<N1, N4>;

    using E21 = Edge<N2, N1>;
    using E22 = Edge<N2, N2>;
    using E23 = Edge<N2, N3>;
    using E24 = Edge<N2, N4>;

    using E31 = Edge<N3, N1>;
    using E32 = Edge<N3, N2>;
    using E33 = Edge<N3, N3>;
    using E34 = Edge<N3, N4>;

    using E41 = Edge<N4, N1>;
    using E42 = Edge<N4, N2>;
    using E43 = Edge<N4, N3>;
    using E44 = Edge<N4, N4>;

    // Graphs
    // -------------------------------------------------------------------------
    //
    using Empty = Graph<List<>, List<>>;

    // (N1)
    using Island = Graph<List<N1>, List<>>;

    //  v----.
    // (N1) -'
    using Loopback = Graph<List<N1>, List<E11>>;

    // (N1) --> (N2)
    using Arrow = Graph<List<N1, N2>, List<E12>>;

    // (N1) --v
    //  ^--- (N2)
    using Bridge = Graph<List<N1, N2>, List<E12, E21>>;

    // (N1) --> (N2) --> (N3)
    //  '-----------------^
    using Leap = Graph<List<N1, N2, N3>, List<E12, E23, E13>>;

    // (N1) ----> (N2)
    //  ^-- (N3) --'
    using Triangle = Graph<List<N1, N2, N3>, List<E12, E23, E31>>;

    // (N1) ------> (N2) --> (N3)
    //  '--> (N4) ---^
    using Pan = Graph<List<N1, N2, N3, N4>, List<E12, E23, E14, E42>>;
}