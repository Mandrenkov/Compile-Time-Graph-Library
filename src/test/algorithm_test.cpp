#include <gtest/gtest.h>

#include "../h/algorithm.h"

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

// distance() Unit Tests
// -----------------------------------------------------------------------------
TEST(AlgorithmTest, DistanceEmpty) {
    using G = Graph<List<>, List<>>;
    EXPECT_EQ(distance(G{}, N1{}, N1{}), INF);
    EXPECT_EQ(distance(G{}, N1{}, N2{}), INF);
}

TEST(AlgorithmTest, DistanceIsland) {
    using G = Graph<List<N1>, List<>>;
    EXPECT_EQ(distance(G{}, N1{}, N1{}), 0);
    EXPECT_EQ(distance(G{}, N1{}, N2{}), INF);
    EXPECT_EQ(distance(G{}, N2{}, N1{}), INF);
}

TEST(AlgorithmTest, DistanceLoop) {
    using G = Graph<List<N1>, List<E11>>;
    EXPECT_EQ(distance(G{}, N1{}, N1{}), 0);
}

TEST(AlgorithmTest, DistanceArrow) {
    using G = Graph<List<N1, N2>, List<E12>>;
    EXPECT_EQ(distance(G{}, N1{}, N2{}), 1);
    EXPECT_EQ(distance(G{}, N2{}, N1{}), INF);
}

TEST(AlgorithmTest, DistanceBridge) {
    using G = Graph<List<N1, N2>, List<E12, E21>>;
    EXPECT_EQ(distance(G{}, N1{}, N2{}), 1);
    EXPECT_EQ(distance(G{}, N2{}, N1{}), 1);
}

TEST(AlgorithmTest, DistanceKite) {
    // N1 ------> N2 --> N3
    //  `--> N4 --^
    using G = Graph<List<N1, N2, N3, N4>, List<E12, E23, E14, E42>>;

    EXPECT_EQ(distance(G{}, N1{}, N1{}), 0);
    EXPECT_EQ(distance(G{}, N1{}, N2{}), 1);
    EXPECT_EQ(distance(G{}, N1{}, N3{}), 2);
    EXPECT_EQ(distance(G{}, N1{}, N4{}), 1);

    EXPECT_EQ(distance(G{}, N2{}, N1{}), INF);
    EXPECT_EQ(distance(G{}, N2{}, N2{}), 0);
    EXPECT_EQ(distance(G{}, N2{}, N3{}), 1);
    EXPECT_EQ(distance(G{}, N2{}, N4{}), INF);

    EXPECT_EQ(distance(G{}, N3{}, N1{}), INF);
    EXPECT_EQ(distance(G{}, N3{}, N2{}), INF);
    EXPECT_EQ(distance(G{}, N3{}, N3{}), 0);
    EXPECT_EQ(distance(G{}, N3{}, N4{}), INF);

    EXPECT_EQ(distance(G{}, N4{}, N1{}), INF);
    EXPECT_EQ(distance(G{}, N4{}, N2{}), 1);
    EXPECT_EQ(distance(G{}, N4{}, N3{}), 2);
    EXPECT_EQ(distance(G{}, N4{}, N4{}), 0);
}

// path() Unit Tests
// -----------------------------------------------------------------------------
template <typename G, typename S, typename T>
using PathType = decltype(path(G{}, S{}, T{}));

TEST(AlgorithmTest, PathEmpty) {
    using G = Graph<List<>, List<>>;
    EXPECT_TRUE((std::is_same<PathType<G, N1, N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N1, N2>, List<>>::value));
}

TEST(AlgorithmTest, PathIsland) {
    using G = Graph<List<N1>, List<>>;
    EXPECT_TRUE((std::is_same<PathType<G, N1, N1>, List<N1>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N1, N2>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N2, N1>, List<>>::value));
}

TEST(AlgorithmTest, PathLoop) {
    using G = Graph<List<N1>, List<E11>>;
    EXPECT_TRUE((std::is_same<PathType<G, N1, N1>, List<N1>>::value));
}

TEST(AlgorithmTest, PathArrow) {
    using G = Graph<List<N1, N2>, List<E12>>;
    EXPECT_TRUE((std::is_same<PathType<G, N1, N2>, List<N1, N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N2, N1>, List<>>::value));
}

TEST(AlgorithmTest, PathBridge) {
    using G = Graph<List<N1, N2>, List<E12, E21>>;
    EXPECT_TRUE((std::is_same<PathType<G, N1, N2>, List<N1, N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N2, N1>, List<N2, N1>>::value));
}

TEST(AlgorithmTest, PathKite) {
    // N1 ------> N2 --> N3
    //  `--> N4 --^
    using G = Graph<List<N1, N2, N3, N4>, List<E12, E23, E14, E42>>;

    EXPECT_TRUE((std::is_same<PathType<G, N1, N1>, List<N1>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N1, N2>, List<N1, N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N1, N3>, List<N1, N2, N3>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N1, N4>, List<N1, N4>>::value));

    EXPECT_TRUE((std::is_same<PathType<G, N2, N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N2, N2>, List<N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N2, N3>, List<N2, N3>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N2, N4>, List<>>::value));

    EXPECT_TRUE((std::is_same<PathType<G, N3, N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N3, N2>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N3, N3>, List<N3>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N3, N4>, List<>>::value));

    EXPECT_TRUE((std::is_same<PathType<G, N4, N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N4, N2>, List<N4, N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N4, N3>, List<N4, N2, N3>>::value));
    EXPECT_TRUE((std::is_same<PathType<G, N4, N4>, List<N4>>::value));
}