#include <gtest/gtest.h>

#include "../h/algorithm.h"
#include "forge.h"

using namespace ctgl;


// Convenient Type Aliases
// -----------------------------------------------------------------------------
template <typename G, typename S, typename T>
using PathType = decltype(path(G{}, S{}, T{}));


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
    EXPECT_EQ(distance(forge::Arrow{}, forge::N1{}, forge::N2{}), 1);
    EXPECT_EQ(distance(forge::Arrow{}, forge::N2{}, forge::N1{}), INF);

    // Bridge
    EXPECT_EQ(distance(forge::Bridge{}, forge::N1{}, forge::N2{}), 1);
    EXPECT_EQ(distance(forge::Bridge{}, forge::N2{}, forge::N1{}), 1);

    // Pan
    EXPECT_EQ(distance(forge::Pan{}, forge::N1{}, forge::N1{}), 0);
    EXPECT_EQ(distance(forge::Pan{}, forge::N1{}, forge::N2{}), 1);
    EXPECT_EQ(distance(forge::Pan{}, forge::N1{}, forge::N3{}), 2);
    EXPECT_EQ(distance(forge::Pan{}, forge::N1{}, forge::N4{}), 1);

    EXPECT_EQ(distance(forge::Pan{}, forge::N2{}, forge::N1{}), INF);
    EXPECT_EQ(distance(forge::Pan{}, forge::N2{}, forge::N2{}), 0);
    EXPECT_EQ(distance(forge::Pan{}, forge::N2{}, forge::N3{}), 1);
    EXPECT_EQ(distance(forge::Pan{}, forge::N2{}, forge::N4{}), INF);

    EXPECT_EQ(distance(forge::Pan{}, forge::N3{}, forge::N1{}), INF);
    EXPECT_EQ(distance(forge::Pan{}, forge::N3{}, forge::N2{}), INF);
    EXPECT_EQ(distance(forge::Pan{}, forge::N3{}, forge::N3{}), 0);
    EXPECT_EQ(distance(forge::Pan{}, forge::N3{}, forge::N4{}), INF);

    EXPECT_EQ(distance(forge::Pan{}, forge::N4{}, forge::N1{}), INF);
    EXPECT_EQ(distance(forge::Pan{}, forge::N4{}, forge::N2{}), 1);
    EXPECT_EQ(distance(forge::Pan{}, forge::N4{}, forge::N3{}), 2);
    EXPECT_EQ(distance(forge::Pan{}, forge::N4{}, forge::N4{}), 0);
}

// Tests for the path() function.
TEST(AlgorithmTest, Path) {
    // Empty
    EXPECT_TRUE((std::is_same<PathType<forge::Empty, forge::N1, forge::N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Empty, forge::N1, forge::N2>, List<>>::value));

    // Island
    EXPECT_TRUE((std::is_same<PathType<forge::Island, forge::N1, forge::N1>, List<forge::N1>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Island, forge::N1, forge::N2>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Island, forge::N2, forge::N1>, List<>>::value));

    // Loopback
    EXPECT_TRUE((std::is_same<PathType<forge::Loopback, forge::N1, forge::N1>, List<forge::N1>>::value));

    // Arrow
    EXPECT_TRUE((std::is_same<PathType<forge::Arrow, forge::N1, forge::N2>, List<forge::N1, forge::N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Arrow, forge::N2, forge::N1>, List<>>::value));

    // Bridge
    EXPECT_TRUE((std::is_same<PathType<forge::Bridge, forge::N1, forge::N2>, List<forge::N1, forge::N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Bridge, forge::N2, forge::N1>, List<forge::N2, forge::N1>>::value));

    // Pan
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N1, forge::N1>, List<forge::N1>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N1, forge::N2>, List<forge::N1, forge::N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N1, forge::N3>, List<forge::N1, forge::N2, forge::N3>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N1, forge::N4>, List<forge::N1, forge::N4>>::value));

    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N2, forge::N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N2, forge::N2>, List<forge::N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N2, forge::N3>, List<forge::N2, forge::N3>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N2, forge::N4>, List<>>::value));

    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N3, forge::N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N3, forge::N2>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N3, forge::N3>, List<forge::N3>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N3, forge::N4>, List<>>::value));

    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N4, forge::N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N4, forge::N2>, List<forge::N4, forge::N2>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N4, forge::N3>, List<forge::N4, forge::N2, forge::N3>>::value));
    EXPECT_TRUE((std::is_same<PathType<forge::Pan, forge::N4, forge::N4>, List<forge::N4>>::value));

    // Bow
    // EXPECT_TRUE((std::is_same<PathType<forge::Bow, forge::N5, forge::N6>, List<forge::N5, forge::N7, forge::N6>>::value));
}