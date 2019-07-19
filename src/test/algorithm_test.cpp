#include <gtest/gtest.h>

#include "../h/algorithm.h"
#include "forge.h"

using namespace ctgl;
using namespace forge;


// Unit Tests
// -----------------------------------------------------------------------------
// Tests for the distance() function.
TEST(AlgorithmTest, Distance) {
    // Empty
    EXPECT_EQ(distance(Empty{}, N1{}, N1{}), INF);
    EXPECT_EQ(distance(Empty{}, N1{}, N2{}), INF);

    // Island
    EXPECT_EQ(distance(Island{}, N1{}, N1{}), 0);
    EXPECT_EQ(distance(Island{}, N1{}, N2{}), INF);
    EXPECT_EQ(distance(Island{}, N2{}, N1{}), INF);

    // Loopback
    EXPECT_EQ(distance(Loopback{}, N1{}, N1{}), 0);

    // Arrow
    EXPECT_EQ(distance(Arrow{}, N1{}, N2{}), 2);
    EXPECT_EQ(distance(Arrow{}, N2{}, N1{}), INF);

    // Bridge
    EXPECT_EQ(distance(Bridge{}, N1{}, N2{}), 2);
    EXPECT_EQ(distance(Bridge{}, N2{}, N1{}), 4);

    // Pan
    EXPECT_EQ(distance(Pan{}, N1{}, N1{}), 0);
    EXPECT_EQ(distance(Pan{}, N1{}, N2{}), 2);
    EXPECT_EQ(distance(Pan{}, N1{}, N3{}), 4);
    EXPECT_EQ(distance(Pan{}, N1{}, N4{}), 4);

    EXPECT_EQ(distance(Pan{}, N2{}, N1{}), INF);
    EXPECT_EQ(distance(Pan{}, N2{}, N2{}), 0);
    EXPECT_EQ(distance(Pan{}, N2{}, N3{}), 2);
    EXPECT_EQ(distance(Pan{}, N2{}, N4{}), INF);

    EXPECT_EQ(distance(Pan{}, N3{}, N1{}), INF);
    EXPECT_EQ(distance(Pan{}, N3{}, N2{}), INF);
    EXPECT_EQ(distance(Pan{}, N3{}, N3{}), 0);
    EXPECT_EQ(distance(Pan{}, N3{}, N4{}), INF);

    EXPECT_EQ(distance(Pan{}, N4{}, N1{}), INF);
    EXPECT_EQ(distance(Pan{}, N4{}, N2{}), 3);
    EXPECT_EQ(distance(Pan{}, N4{}, N3{}), 5);
    EXPECT_EQ(distance(Pan{}, N4{}, N4{}), 0);

    // Bow
    EXPECT_EQ(distance(Bow{}, N5{}, N6{}), 2);
    EXPECT_EQ(distance(Bow{}, N5{}, N7{}), 1);
    EXPECT_EQ(distance(Bow{}, N6{}, N5{}), INF);
    EXPECT_EQ(distance(Bow{}, N6{}, N7{}), INF);
    EXPECT_EQ(distance(Bow{}, N7{}, N5{}), INF);
    EXPECT_EQ(distance(Bow{}, N7{}, N6{}), 1);
}

// Tests for the shortest() function.
TEST(AlgorithmTest, Shortest) {
    // Empty
    EXPECT_EQ(shortest(Empty{}, N1{}, N1{}), path::DNE);
    EXPECT_EQ(shortest(Empty{}, N1{}, N2{}), path::DNE);

    // Island
    EXPECT_EQ(shortest(Island{}, N1{}, N1{}), Path<>{});
    EXPECT_EQ(shortest(Island{}, N1{}, N2{}), path::DNE);
    EXPECT_EQ(shortest(Island{}, N2{}, N1{}), path::DNE);

    // Loopback
    EXPECT_EQ(shortest(Loopback{}, N1{}, N1{}), Path<>{});

    // Arrow
    EXPECT_EQ(shortest(Arrow{}, N1{}, N2{}), Path<E12>{});
    EXPECT_EQ(shortest(Arrow{}, N2{}, N1{}), path::DNE);

    // Bridge
    EXPECT_EQ(shortest(Bridge{}, N1{}, N2{}), Path<E12>{});
    EXPECT_EQ(shortest(Bridge{}, N2{}, N1{}), Path<E21>{});

    // Pan
    EXPECT_EQ(shortest(Pan{}, N1{}, N1{}), Path<>{});
    EXPECT_EQ(shortest(Pan{}, N1{}, N2{}), Path<E12>{});
    EXPECT_EQ(shortest(Pan{}, N1{}, N3{}), (Path<E12, E23>{}));
    EXPECT_EQ(shortest(Pan{}, N1{}, N4{}), Path<E14>{});

    EXPECT_EQ(shortest(Pan{}, N2{}, N1{}), path::DNE);
    EXPECT_EQ(shortest(Pan{}, N2{}, N2{}), Path<>{});
    EXPECT_EQ(shortest(Pan{}, N2{}, N3{}), Path<E23>{});
    EXPECT_EQ(shortest(Pan{}, N2{}, N4{}), path::DNE);

    EXPECT_EQ(shortest(Pan{}, N3{}, N1{}), path::DNE);
    EXPECT_EQ(shortest(Pan{}, N3{}, N2{}), path::DNE);
    EXPECT_EQ(shortest(Pan{}, N3{}, N3{}), Path<>{});
    EXPECT_EQ(shortest(Pan{}, N3{}, N4{}), path::DNE);

    EXPECT_EQ(shortest(Pan{}, N4{}, N1{}), path::DNE);
    EXPECT_EQ(shortest(Pan{}, N4{}, N2{}), Path<E42>{});
    EXPECT_EQ(shortest(Pan{}, N4{}, N3{}), (Path<E42, E23>{}));
    EXPECT_EQ(shortest(Pan{}, N4{}, N4{}), Path<>{});

    // Bow
    EXPECT_EQ(shortest(Bow{}, N5{}, N6{}), (Path<E57, E76>{}));
    EXPECT_EQ(shortest(Bow{}, N5{}, N7{}), Path<E57>{});
    EXPECT_EQ(shortest(Bow{}, N6{}, N5{}), path::DNE);
    EXPECT_EQ(shortest(Bow{}, N6{}, N7{}), path::DNE);
    EXPECT_EQ(shortest(Bow{}, N7{}, N5{}), path::DNE);
    EXPECT_EQ(shortest(Bow{}, N7{}, N6{}), Path<E76>{});
}