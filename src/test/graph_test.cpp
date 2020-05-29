#include <iostream>

#include <gtest/gtest.h>

#include "../h/graph.h"
#include "forge.h"

using namespace ctgl;
using namespace forge;

// Unit tests for the ctgl::graph::getAdjacentNodes() function.
TEST(GraphTest, GetAdjacentNodes) {
    // Empty
    EXPECT_EQ(getAdjacentNodes(Empty{}, N1{}), List<>{});

    // Island
    EXPECT_EQ(getAdjacentNodes(Island{}, N1{}), List<>{});
    EXPECT_EQ(getAdjacentNodes(Island{}, N2{}), List<>{});

    // Loopback
    EXPECT_EQ(getAdjacentNodes(Loopback{}, N1{}), List<N1>{});

    // Arrow
    EXPECT_EQ(getAdjacentNodes(Arrow{}, N1{}), List<N2>{});
    EXPECT_EQ(getAdjacentNodes(Arrow{}, N2{}), List<>{});

    // Bridge
    EXPECT_EQ(getAdjacentNodes(Bridge{}, N1{}), List<N2>{});
    EXPECT_EQ(getAdjacentNodes(Bridge{}, N2{}), List<N1>{});

    // Leap
    EXPECT_EQ(getAdjacentNodes(Leap{}, N1{}), (List<N2, N3>{}));
    EXPECT_EQ(getAdjacentNodes(Leap{}, N2{}), List<N3>{});
    EXPECT_EQ(getAdjacentNodes(Leap{}, N3{}), List<>{});
}

// Unit tests for the ctgl::graph::getConnectedNodes() function.
TEST(GraphTest, GetConnectedNodes) {
    // Empty
    EXPECT_EQ(getConnectedNodes(Empty{}, N1{}), List<>{});

    // Island
    EXPECT_EQ(getConnectedNodes(Island{}, N1{}), List<N1>{});
    EXPECT_EQ(getConnectedNodes(Island{}, N2{}), List<>{});

    // Loopback
    EXPECT_EQ(getConnectedNodes(Loopback{}, N1{}), List<N1>{});

    // Pan
    EXPECT_EQ(getConnectedNodes(Pan{}, N1{}), (List<N4, N3, N2, N1>{}));
    EXPECT_EQ(getConnectedNodes(Pan{}, N2{}), (List<N3, N2>{}));
    EXPECT_EQ(getConnectedNodes(Pan{}, N3{}), List<N3>{});
    EXPECT_EQ(getConnectedNodes(Pan{}, N4{}), (List<N3, N2, N4>{}));

    // Triangle
    EXPECT_EQ(getConnectedNodes(Triangle{}, N1{}), (List<N3, N2, N1>{}));
    EXPECT_EQ(getConnectedNodes(Triangle{}, N2{}), (List<N1, N3, N2>{}));
    EXPECT_EQ(getConnectedNodes(Triangle{}, N3{}), (List<N2, N1, N3>{}));
}

// Unit tests for the ctgl::graph::getOutgoingEdges() function.
TEST(GraphTest, GetOutgoingEdges) {
    // Empty
    EXPECT_EQ(getOutgoingEdges(Empty{}, N1{}), List<>{});

    // Island
    EXPECT_EQ(getOutgoingEdges(Empty{}, N1{}), List<>{});
    EXPECT_EQ(getOutgoingEdges(Empty{}, N2{}), List<>{});

    // Loopback
    EXPECT_EQ(getOutgoingEdges(Loopback{}, N1{}), List<E11>{});

    // Arrow
    EXPECT_EQ(getOutgoingEdges(Arrow{}, N1{}), List<E12>{});
    EXPECT_EQ(getOutgoingEdges(Arrow{}, N2{}), List<>{});

    // Bridge
    EXPECT_EQ(getOutgoingEdges(Bridge{}, N1{}), List<E12>{});
    EXPECT_EQ(getOutgoingEdges(Bridge{}, N2{}), List<E21>{});

    // Leap
    EXPECT_EQ(getOutgoingEdges(Leap{}, N1{}), (List<E12, E13>{}));
    EXPECT_EQ(getOutgoingEdges(Leap{}, N2{}), List<E23>{});
    EXPECT_EQ(getOutgoingEdges(Leap{}, N3{}), List<>{});
}