#include <gtest/gtest.h>

#include "../h/graph.h"

using namespace ctgl;

// Graph Building Blocks
// -----------------------------------------------------------------------------
// Nodes
using N1 = Node<1>;
using N2 = Node<2>;
using N3 = Node<3>;
using N4 = Node<4>;

// Edges
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

// adjacent() Unit Tests
// -----------------------------------------------------------------------------
template <typename T, typename U>
using AdjacentType = decltype(adjacent(T{}, U{}));

TEST(GraphTest, AdjacentEmpty) {
    using G = Graph<List<>, List<>>;
    EXPECT_TRUE((std::is_same<AdjacentType<G, N1>, List<>>::value));
}

TEST(GraphTest, AdjacentIsland) {
    using G = Graph<List<N1>, List<>>;
    EXPECT_TRUE((std::is_same<AdjacentType<G, N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<G, N2>, List<>>::value));
}

TEST(GraphTest, AdjacentLoop) {
    using G = Graph<List<N1>, List<E11>>;
    EXPECT_TRUE((std::is_same<AdjacentType<G, N1>, List<N1>>::value));
}

TEST(GraphTest, AdjacentArrow) {
    using G = Graph<List<N1, N2>, List<E12>>;
    EXPECT_TRUE((std::is_same<AdjacentType<G, N1>, List<N2>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<G, N2>, List<>>::value));
}

TEST(GraphTest, AdjacentBridge) {
    using G = Graph<List<N1, N2>, List<E12, E21>>;
    EXPECT_TRUE((std::is_same<AdjacentType<G, N1>, List<N2>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<G, N2>, List<N1>>::value));
}

TEST(GraphTest, AdjacentThreeway) {
    using G = Graph<List<N1, N2, N3>, List<E23, E12, E13>>;
    EXPECT_TRUE((std::is_same<AdjacentType<G, N1>, List<N2, N3>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<G, N2>, List<N3>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<G, N3>, List<>>::value));
}