#include <gtest/gtest.h>

#include "../h/graph.h"
#include "forge.h"

#include <iostream>

using namespace ctgl;


// Convenient Type Aliases
// -----------------------------------------------------------------------------
template <typename G, typename N>
using AdjacentType = decltype(graph::adjacent(G{}, N{}));

template <typename G, typename N>
using ConnectedType = decltype(graph::connected(G{}, N{}));

template <typename G, typename N>
using OutgoingType = decltype(graph::outgoing(G{}, N{}));

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

    // Leap
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Leap, forge::N1>, List<forge::N2, forge::N3>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Leap, forge::N2>, List<forge::N3>>::value));
    EXPECT_TRUE((std::is_same<AdjacentType<forge::Leap, forge::N3>, List<>>::value));
}

// Tests for the connected() function.
TEST(GraphTest, Connected) {
    // Empty
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Empty, forge::N1>, List<>>::value));

    // Island
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Island, forge::N1>, List<forge::N1>>::value));
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Island, forge::N2>, List<>>::value));

    // Loopback
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Loopback, forge::N1>, List<forge::N1>>::value));

    // Pan
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Pan, forge::N1>, List<forge::N4, forge::N3, forge::N2, forge::N1>>::value));
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Pan, forge::N2>, List<forge::N3, forge::N2>>::value));
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Pan, forge::N3>, List<forge::N3>>::value));
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Pan, forge::N4>, List<forge::N3, forge::N2, forge::N4>>::value));

    // Triangle
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Triangle, forge::N1>, List<forge::N3, forge::N2, forge::N1>>::value));
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Triangle, forge::N2>, List<forge::N1, forge::N3, forge::N2>>::value));
    EXPECT_TRUE((std::is_same<ConnectedType<forge::Triangle, forge::N3>, List<forge::N2, forge::N1, forge::N3>>::value));
}

// Tests for the outgoing() function.
TEST(GraphTest, Outgoing) {
    // Empty
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Empty, forge::N1>, List<>>::value));

    // Island
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Empty, forge::N1>, List<>>::value));
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Empty, forge::N2>, List<>>::value));

    // Loopback
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Loopback, forge::N1>, List<forge::E11>>::value));

    // Arrow
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Arrow, forge::N1>, List<forge::E12>>::value));
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Arrow, forge::N2>, List<>>::value));

    // Bridge
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Bridge, forge::N1>, List<forge::E12>>::value));
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Bridge, forge::N2>, List<forge::E21>>::value));

    // Leap
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Leap, forge::N1>, List<forge::E12, forge::E13>>::value));
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Leap, forge::N2>, List<forge::E23>>::value));
    EXPECT_TRUE((std::is_same<OutgoingType<forge::Leap, forge::N3>, List<>>::value));
}