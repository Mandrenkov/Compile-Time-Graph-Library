#include <gtest/gtest.h>

#include "../h/algorithm.h"
#include "forge.h"

using namespace ctgl;


// Convenient Type Aliases
// -----------------------------------------------------------------------------
template <typename G, typename S, typename T>
using ShortestType = decltype(shortest(G{}, S{}, T{}));


// Unit Tests
// -----------------------------------------------------------------------------
// Tests for the distance() function.
TEST(AlgorithmTest, Distance) {
    // Empty
    EXPECT_EQ(distance(forge::Empty{}, forge::N1{}, forge::N1{}), INF);
    EXPECT_EQ(distance(forge::Empty{}, forge::N1{}, forge::N2{}), INF);

    // Island
    EXPECT_EQ(distance(forge::Island{}, forge::N1{}, forge::N1{}), 0);
    EXPECT_EQ(distance(forge::Island{}, forge::N1{}, forge::N2{}), INF);
    EXPECT_EQ(distance(forge::Island{}, forge::N2{}, forge::N1{}), INF);

    // Loopback
    EXPECT_EQ(distance(forge::Loopback{}, forge::N1{}, forge::N1{}), 0);

    // Arrow
    EXPECT_EQ(distance(forge::Arrow{}, forge::N1{}, forge::N2{}), 2);
    EXPECT_EQ(distance(forge::Arrow{}, forge::N2{}, forge::N1{}), INF);

    // Bridge
    EXPECT_EQ(distance(forge::Bridge{}, forge::N1{}, forge::N2{}), 2);
    EXPECT_EQ(distance(forge::Bridge{}, forge::N2{}, forge::N1{}), 4);

    // Pan
    EXPECT_EQ(distance(forge::Pan{}, forge::N1{}, forge::N1{}), 0);
    EXPECT_EQ(distance(forge::Pan{}, forge::N1{}, forge::N2{}), 2);
    EXPECT_EQ(distance(forge::Pan{}, forge::N1{}, forge::N3{}), 4);
    EXPECT_EQ(distance(forge::Pan{}, forge::N1{}, forge::N4{}), 4);

    EXPECT_EQ(distance(forge::Pan{}, forge::N2{}, forge::N1{}), INF);
    EXPECT_EQ(distance(forge::Pan{}, forge::N2{}, forge::N2{}), 0);
    EXPECT_EQ(distance(forge::Pan{}, forge::N2{}, forge::N3{}), 2);
    EXPECT_EQ(distance(forge::Pan{}, forge::N2{}, forge::N4{}), INF);

    EXPECT_EQ(distance(forge::Pan{}, forge::N3{}, forge::N1{}), INF);
    EXPECT_EQ(distance(forge::Pan{}, forge::N3{}, forge::N2{}), INF);
    EXPECT_EQ(distance(forge::Pan{}, forge::N3{}, forge::N3{}), 0);
    EXPECT_EQ(distance(forge::Pan{}, forge::N3{}, forge::N4{}), INF);

    EXPECT_EQ(distance(forge::Pan{}, forge::N4{}, forge::N1{}), INF);
    EXPECT_EQ(distance(forge::Pan{}, forge::N4{}, forge::N2{}), 3);
    EXPECT_EQ(distance(forge::Pan{}, forge::N4{}, forge::N3{}), 5);
    EXPECT_EQ(distance(forge::Pan{}, forge::N4{}, forge::N4{}), 0);

    // Bow
    EXPECT_EQ(distance(forge::Bow{}, forge::N5{}, forge::N6{}), 2);
    EXPECT_EQ(distance(forge::Bow{}, forge::N5{}, forge::N7{}), 1);
    EXPECT_EQ(distance(forge::Bow{}, forge::N6{}, forge::N5{}), INF);
    EXPECT_EQ(distance(forge::Bow{}, forge::N6{}, forge::N7{}), INF);
    EXPECT_EQ(distance(forge::Bow{}, forge::N7{}, forge::N5{}), INF);
    EXPECT_EQ(distance(forge::Bow{}, forge::N7{}, forge::N6{}), 1);
}

// Tests for the shortest() function.
TEST(AlgorithmTest, Shortest) {
    // Empty
    EXPECT_EQ(shortest(forge::Empty{}, forge::N1{}, forge::N1{}), path::DNE);
    EXPECT_EQ(shortest(forge::Empty{}, forge::N1{}, forge::N2{}), path::DNE);

    // Island
    EXPECT_EQ(shortest(forge::Island{}, forge::N1{}, forge::N1{}), Path<>{});
    EXPECT_EQ(shortest(forge::Island{}, forge::N1{}, forge::N2{}), path::DNE);
    EXPECT_EQ(shortest(forge::Island{}, forge::N2{}, forge::N1{}), path::DNE);

    // Loopback
    EXPECT_EQ(shortest(forge::Loopback{}, forge::N1{}, forge::N1{}), Path<>{});

    // Arrow
    EXPECT_EQ(shortest(forge::Arrow{}, forge::N1{}, forge::N2{}), Path<forge::E12>{});
    EXPECT_EQ(shortest(forge::Arrow{}, forge::N2{}, forge::N1{}), path::DNE);

    // Bridge
    EXPECT_EQ(shortest(forge::Bridge{}, forge::N1{}, forge::N2{}), Path<forge::E12>{});
    EXPECT_EQ(shortest(forge::Bridge{}, forge::N2{}, forge::N1{}), Path<forge::E21>{});

    // Pan
    EXPECT_EQ(shortest(forge::Pan{}, forge::N1{}, forge::N1{}), Path<>{});
    EXPECT_EQ(shortest(forge::Pan{}, forge::N1{}, forge::N2{}), Path<forge::E12>{});
    EXPECT_EQ(shortest(forge::Pan{}, forge::N1{}, forge::N3{}), (Path<forge::E12, forge::E23>{}));
    EXPECT_EQ(shortest(forge::Pan{}, forge::N1{}, forge::N4{}), Path<forge::E14>{});

    EXPECT_EQ(shortest(forge::Pan{}, forge::N2{}, forge::N1{}), path::DNE);
    EXPECT_EQ(shortest(forge::Pan{}, forge::N2{}, forge::N2{}), Path<>{});
    EXPECT_EQ(shortest(forge::Pan{}, forge::N2{}, forge::N3{}), Path<forge::E23>{});
    EXPECT_EQ(shortest(forge::Pan{}, forge::N2{}, forge::N4{}), path::DNE);

    EXPECT_EQ(shortest(forge::Pan{}, forge::N3{}, forge::N1{}), path::DNE);
    EXPECT_EQ(shortest(forge::Pan{}, forge::N3{}, forge::N2{}), path::DNE);
    EXPECT_EQ(shortest(forge::Pan{}, forge::N3{}, forge::N3{}), Path<>{});
    EXPECT_EQ(shortest(forge::Pan{}, forge::N3{}, forge::N4{}), path::DNE);

    EXPECT_EQ(shortest(forge::Pan{}, forge::N4{}, forge::N1{}), path::DNE);
    EXPECT_EQ(shortest(forge::Pan{}, forge::N4{}, forge::N2{}), Path<forge::E42>{});
    EXPECT_EQ(shortest(forge::Pan{}, forge::N4{}, forge::N3{}), (Path<forge::E42, forge::E23>{}));
    EXPECT_EQ(shortest(forge::Pan{}, forge::N4{}, forge::N4{}), Path<>{});

    // Bow
    EXPECT_EQ(shortest(forge::Bow{}, forge::N5{}, forge::N6{}), (Path<forge::E57, forge::E76>{}));
    EXPECT_EQ(shortest(forge::Bow{}, forge::N5{}, forge::N7{}), Path<forge::E57>{});
    EXPECT_EQ(shortest(forge::Bow{}, forge::N6{}, forge::N5{}), path::DNE);
    EXPECT_EQ(shortest(forge::Bow{}, forge::N6{}, forge::N7{}), path::DNE);
    EXPECT_EQ(shortest(forge::Bow{}, forge::N7{}, forge::N5{}), path::DNE);
    EXPECT_EQ(shortest(forge::Bow{}, forge::N7{}, forge::N6{}), Path<forge::E76>{});
}