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

// Unit tests for the ctgl::graph::hasCycle() functions.
TEST(GraphTest, HasCycle) {
    // Cyclic
    EXPECT_TRUE(hasCycle(Loopback{}));
    EXPECT_TRUE(hasCycle(Bridge{}));
    EXPECT_TRUE(hasCycle(Triangle{}));
    EXPECT_TRUE(hasCycle(Dipper{}));

    // Acyclic
    EXPECT_FALSE(hasCycle(Empty{}));
    EXPECT_FALSE(hasCycle(Island{}));
    EXPECT_FALSE(hasCycle(Arrow{}));
    EXPECT_FALSE(hasCycle(Leap{}));
    EXPECT_FALSE(hasCycle(Pan{}));
}

// Unit tests for the ctgl::graph::hasNegativeCycle() functions.
TEST(GraphTest, HasNegativeCycle) {
    // Negative Cyclic
    EXPECT_TRUE(hasNegativeCycle(Alone{}));
    EXPECT_TRUE(hasNegativeCycle(Debate{}));
    EXPECT_TRUE(hasNegativeCycle(Spiral{}));
    EXPECT_TRUE(hasNegativeCycle(Hole{}));
    EXPECT_TRUE(hasNegativeCycle(Magnet{}));

    // Negative Acyclic
    EXPECT_FALSE(hasNegativeCycle(Empty{}));
    EXPECT_FALSE(hasNegativeCycle(Island{}));
    EXPECT_FALSE(hasNegativeCycle(Loopback{}));
    EXPECT_FALSE(hasNegativeCycle(Arrow{}));
    EXPECT_FALSE(hasNegativeCycle(Bridge{}));
    EXPECT_FALSE(hasNegativeCycle(Leap{}));
    EXPECT_FALSE(hasNegativeCycle(Triangle{}));
    EXPECT_FALSE(hasNegativeCycle(Pan{}));
    EXPECT_FALSE(hasNegativeCycle(Dipper{}));
}

// Unit tests for the ctgl::graph::isConnected() functions.
TEST(GraphTest, IsConnected) {
    // Empty
    EXPECT_TRUE(isConnected(Empty{}));
    EXPECT_FALSE(isConnected(Empty{}, N1{}, N1{}));
    EXPECT_FALSE(isConnected(Empty{}, N1{}, N2{}));

    // Island
    EXPECT_TRUE(isConnected(Island{}));
    EXPECT_TRUE(isConnected(Island{}, N1{}, N1{}));
    EXPECT_FALSE(isConnected(Island{}, N1{}, N2{}));
    EXPECT_FALSE(isConnected(Island{}, N2{}, N1{}));

    // Loopback
    EXPECT_TRUE(isConnected(Loopback{}));
    EXPECT_TRUE(isConnected(Loopback{}, N1{}, N1{}));
    EXPECT_FALSE(isConnected(Loopback{}, N1{}, N2{}));

    // Arrow
    EXPECT_FALSE(isConnected(Arrow{}));
    EXPECT_TRUE(isConnected(Arrow{}, N1{}, N2{}));
    EXPECT_FALSE(isConnected(Arrow{}, N2{}, N1{}));

    // Bridge
    EXPECT_TRUE(isConnected(Bridge{}));
    EXPECT_TRUE(isConnected(Bridge{}, N1{}, N2{}));
    EXPECT_TRUE(isConnected(Bridge{}, N2{}, N1{}));

    // Leap
    EXPECT_FALSE(isConnected(Leap{}));
    EXPECT_TRUE(isConnected(Leap{}, N1{}, N2{}));
    EXPECT_TRUE(isConnected(Leap{}, N1{}, N3{}));
    EXPECT_TRUE(isConnected(Leap{}, N2{}, N3{}));
    EXPECT_FALSE(isConnected(Leap{}, N2{}, N1{}));
    EXPECT_FALSE(isConnected(Leap{}, N3{}, N1{}));
    EXPECT_FALSE(isConnected(Leap{}, N3{}, N2{}));

    // Triangle
    EXPECT_TRUE(isConnected(Triangle{}));
    EXPECT_TRUE(isConnected(Triangle{}, N1{}, N2{}));
    EXPECT_TRUE(isConnected(Triangle{}, N1{}, N3{}));
    EXPECT_TRUE(isConnected(Triangle{}, N2{}, N1{}));
    EXPECT_TRUE(isConnected(Triangle{}, N2{}, N3{}));
    EXPECT_TRUE(isConnected(Triangle{}, N3{}, N1{}));
    EXPECT_TRUE(isConnected(Triangle{}, N3{}, N2{}));

    // Pan
    EXPECT_FALSE(isConnected(Pan{}));
    EXPECT_TRUE(isConnected(Pan{}, N1{}, N2{}));
    EXPECT_TRUE(isConnected(Pan{}, N1{}, N3{}));
    EXPECT_TRUE(isConnected(Pan{}, N1{}, N4{}));
    EXPECT_TRUE(isConnected(Pan{}, N2{}, N3{}));
    EXPECT_TRUE(isConnected(Pan{}, N4{}, N2{}));
    EXPECT_TRUE(isConnected(Pan{}, N4{}, N4{}));
    EXPECT_FALSE(isConnected(Pan{}, N2{}, N1{}));
    EXPECT_FALSE(isConnected(Pan{}, N2{}, N4{}));
    EXPECT_FALSE(isConnected(Pan{}, N3{}, N1{}));
    EXPECT_FALSE(isConnected(Pan{}, N3{}, N2{}));
    EXPECT_FALSE(isConnected(Pan{}, N3{}, N4{}));
    EXPECT_FALSE(isConnected(Pan{}, N4{}, N1{}));

    // Dipper
    EXPECT_FALSE(isConnected(Dipper{}));
    EXPECT_TRUE(isConnected(Dipper{}, N1{}, N2{}));
    EXPECT_TRUE(isConnected(Dipper{}, N1{}, N3{}));
    EXPECT_TRUE(isConnected(Dipper{}, N2{}, N1{}));
    EXPECT_TRUE(isConnected(Dipper{}, N2{}, N3{}));
    EXPECT_TRUE(isConnected(Dipper{}, N3{}, N1{}));
    EXPECT_TRUE(isConnected(Dipper{}, N3{}, N2{}));
    EXPECT_TRUE(isConnected(Dipper{}, N4{}, N1{}));
    EXPECT_TRUE(isConnected(Dipper{}, N4{}, N2{}));
    EXPECT_TRUE(isConnected(Dipper{}, N4{}, N3{}));
    EXPECT_FALSE(isConnected(Dipper{}, N1{}, N4{}));
    EXPECT_FALSE(isConnected(Dipper{}, N2{}, N4{}));
    EXPECT_FALSE(isConnected(Dipper{}, N3{}, N4{}));
}