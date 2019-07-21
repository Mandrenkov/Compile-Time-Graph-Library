#include <iostream>

#include <gtest/gtest.h>

#include "../h/graph.h"
#include "forge.h"

using namespace ctgl;
using namespace forge;

// Unit tests for the ctgl::graph::adjacent() function.
TEST(GraphTest, Adjacent) {
    // Empty
    EXPECT_EQ(adjacent(Empty{}, N1{}), List<>{});

    // Island
    EXPECT_EQ(adjacent(Island{}, N1{}), List<>{});
    EXPECT_EQ(adjacent(Island{}, N2{}), List<>{});

    // Loopback
    EXPECT_EQ(adjacent(Loopback{}, N1{}), List<N1>{});

    // Arrow
    EXPECT_EQ(adjacent(Arrow{}, N1{}), List<N2>{});
    EXPECT_EQ(adjacent(Arrow{}, N2{}), List<>{});

    // Bridge
    EXPECT_EQ(adjacent(Bridge{}, N1{}), List<N2>{});
    EXPECT_EQ(adjacent(Bridge{}, N2{}), List<N1>{});

    // Leap
    EXPECT_EQ(adjacent(Leap{}, N1{}), (List<N2, N3>{}));
    EXPECT_EQ(adjacent(Leap{}, N2{}), List<N3>{});
    EXPECT_EQ(adjacent(Leap{}, N3{}), List<>{});
}

// Unit tests for the ctgl::graph::connected() function.
TEST(GraphTest, Connected) {
    // Empty
    EXPECT_EQ(connected(Empty{}, N1{}), List<>{});

    // Island
    EXPECT_EQ(connected(Island{}, N1{}), List<N1>{});
    EXPECT_EQ(connected(Island{}, N2{}), List<>{});

    // Loopback
    EXPECT_EQ(connected(Loopback{}, N1{}), List<N1>{});

    // Pan
    EXPECT_EQ(connected(Pan{}, N1{}), (List<N4, N3, N2, N1>{}));
    EXPECT_EQ(connected(Pan{}, N2{}), (List<N3, N2>{}));
    EXPECT_EQ(connected(Pan{}, N3{}), List<N3>{});
    EXPECT_EQ(connected(Pan{}, N4{}), (List<N3, N2, N4>{}));

    // Triangle
    EXPECT_EQ(connected(Triangle{}, N1{}), (List<N3, N2, N1>{}));
    EXPECT_EQ(connected(Triangle{}, N2{}), (List<N1, N3, N2>{}));
    EXPECT_EQ(connected(Triangle{}, N3{}), (List<N2, N1, N3>{}));
}

// Unit tests for the ctgl::graph::outgoing() function.
TEST(GraphTest, Outgoing) {
    // Empty
    EXPECT_EQ(outgoing(Empty{}, N1{}), List<>{});

    // Island
    EXPECT_EQ(outgoing(Empty{}, N1{}), List<>{});
    EXPECT_EQ(outgoing(Empty{}, N2{}), List<>{});

    // Loopback
    EXPECT_EQ(outgoing(Loopback{}, N1{}), List<E11>{});

    // Arrow
    EXPECT_EQ(outgoing(Arrow{}, N1{}), List<E12>{});
    EXPECT_EQ(outgoing(Arrow{}, N2{}), List<>{});

    // Bridge
    EXPECT_EQ(outgoing(Bridge{}, N1{}), List<E12>{});
    EXPECT_EQ(outgoing(Bridge{}, N2{}), List<E21>{});

    // Leap
    EXPECT_EQ(outgoing(Leap{}, N1{}), (List<E12, E13>{}));
    EXPECT_EQ(outgoing(Leap{}, N2{}), List<E23>{});
    EXPECT_EQ(outgoing(Leap{}, N3{}), List<>{});
}