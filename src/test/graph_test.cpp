#include <gtest/gtest.h>

#include "../h/graph.h"
#include "forge.h"

using namespace ctgl;


// Convenient Type Aliases
// -----------------------------------------------------------------------------
template <typename T, typename U>
using AdjacentType = decltype(ctgl::graph::adjacent(T{}, U{}));


// Unit Tests
// -----------------------------------------------------------------------------
// Tests for the adjacent() function.
TEST(GraphTest, Adjacent) {
    // Empty
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Empty, forge::N1>, List<>>::value));

    // Island
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Island, forge::N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Island, forge::N2>, List<>>::value));

    // Loopback
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Loopback, forge::N1>, List<forge::N1>>::value));

    // Arrow
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Arrow, forge::N1>, List<forge::N2>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Arrow, forge::N2>, List<>>::value));

    // Bridge
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Bridge, forge::N1>, List<forge::N2>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Bridge, forge::N2>, List<forge::N1>>::value));

    // Triangle
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Leap, forge::N1>, List<forge::N2, forge::N3>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Leap, forge::N2>, List<forge::N3>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Leap, forge::N3>, List<>>::value));
}