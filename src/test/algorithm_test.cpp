#include <gtest/gtest.h>

#include "../h/algorithm.h"
#include "forge.h"

using namespace ctgl;
using namespace forge;


// Unit tests for the ctgl::algorithm::findDistance() function.
TEST(AlgorithmTest, FindDistance) {
    // Empty
    EXPECT_EQ(algorithm::findDistance(Empty{}, N1{}, N1{}), INF);
    EXPECT_EQ(algorithm::findDistance(Empty{}, N1{}, N2{}), INF);

    // Island
    EXPECT_EQ(algorithm::findDistance(Island{}, N1{}, N1{}), 0);
    EXPECT_EQ(algorithm::findDistance(Island{}, N1{}, N2{}), INF);
    EXPECT_EQ(algorithm::findDistance(Island{}, N2{}, N1{}), INF);

    // Loopback
    EXPECT_EQ(algorithm::findDistance(Loopback{}, N1{}, N1{}), 0);

    // Arrow
    EXPECT_EQ(algorithm::findDistance(Arrow{}, N1{}, N2{}), 2);
    EXPECT_EQ(algorithm::findDistance(Arrow{}, N2{}, N1{}), INF);

    // Bridge
    EXPECT_EQ(algorithm::findDistance(Bridge{}, N1{}, N2{}), 2);
    EXPECT_EQ(algorithm::findDistance(Bridge{}, N2{}, N1{}), 4);

    // Pan
    EXPECT_EQ(algorithm::findDistance(Pan{}, N1{}, N1{}), 0);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N1{}, N2{}), 2);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N1{}, N3{}), 4);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N1{}, N4{}), 4);

    EXPECT_EQ(algorithm::findDistance(Pan{}, N2{}, N1{}), INF);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N2{}, N2{}), 0);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N2{}, N3{}), 2);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N2{}, N4{}), INF);

    EXPECT_EQ(algorithm::findDistance(Pan{}, N3{}, N1{}), INF);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N3{}, N2{}), INF);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N3{}, N3{}), 0);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N3{}, N4{}), INF);

    EXPECT_EQ(algorithm::findDistance(Pan{}, N4{}, N1{}), INF);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N4{}, N2{}), 3);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N4{}, N3{}), 5);
    EXPECT_EQ(algorithm::findDistance(Pan{}, N4{}, N4{}), 0);

    // Bow
    EXPECT_EQ(algorithm::findDistance(Bow{}, N5{}, N6{}), 2);
    EXPECT_EQ(algorithm::findDistance(Bow{}, N5{}, N7{}), 1);
    EXPECT_EQ(algorithm::findDistance(Bow{}, N6{}, N5{}), INF);
    EXPECT_EQ(algorithm::findDistance(Bow{}, N6{}, N7{}), INF);
    EXPECT_EQ(algorithm::findDistance(Bow{}, N7{}, N5{}), INF);
    EXPECT_EQ(algorithm::findDistance(Bow{}, N7{}, N6{}), 1);
}

// Unit tests for the ctgl::algorithm::findShortestPath() function.
TEST(AlgorithmTest, FindShortestPath) {
    // Empty
    EXPECT_EQ(algorithm::findShortestPath(Empty{}, N1{}, N1{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Empty{}, N1{}, N2{}), path::DNE);

    // Island
    EXPECT_EQ(algorithm::findShortestPath(Island{}, N1{}, N1{}), Path<>{});
    EXPECT_EQ(algorithm::findShortestPath(Island{}, N1{}, N2{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Island{}, N2{}, N1{}), path::DNE);

    // Loopback
    EXPECT_EQ(algorithm::findShortestPath(Loopback{}, N1{}, N1{}), Path<>{});

    // Arrow
    EXPECT_EQ(algorithm::findShortestPath(Arrow{}, N1{}, N2{}), Path<E12>{});
    EXPECT_EQ(algorithm::findShortestPath(Arrow{}, N2{}, N1{}), path::DNE);

    // Bridge
    EXPECT_EQ(algorithm::findShortestPath(Bridge{}, N1{}, N2{}), Path<E12>{});
    EXPECT_EQ(algorithm::findShortestPath(Bridge{}, N2{}, N1{}), Path<E21>{});

    // Pan
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N1{}, N1{}), Path<>{});
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N1{}, N2{}), Path<E12>{});
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N1{}, N3{}), (Path<E12, E23>{}));
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N1{}, N4{}), Path<E14>{});

    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N2{}, N1{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N2{}, N2{}), Path<>{});
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N2{}, N3{}), Path<E23>{});
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N2{}, N4{}), path::DNE);

    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N3{}, N1{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N3{}, N2{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N3{}, N3{}), Path<>{});
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N3{}, N4{}), path::DNE);

    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N4{}, N1{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N4{}, N2{}), Path<E42>{});
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N4{}, N3{}), (Path<E42, E23>{}));
    EXPECT_EQ(algorithm::findShortestPath(Pan{}, N4{}, N4{}), Path<>{});

    // Bow
    EXPECT_EQ(algorithm::findShortestPath(Bow{}, N5{}, N6{}), (Path<E57, E76>{}));
    EXPECT_EQ(algorithm::findShortestPath(Bow{}, N5{}, N7{}), Path<E57>{});
    EXPECT_EQ(algorithm::findShortestPath(Bow{}, N6{}, N5{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Bow{}, N6{}, N7{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Bow{}, N7{}, N5{}), path::DNE);
    EXPECT_EQ(algorithm::findShortestPath(Bow{}, N7{}, N6{}), Path<E76>{});
}