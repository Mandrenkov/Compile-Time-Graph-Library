#include <gtest/gtest.h>

#include "../h/path.h"
#include "forge.h"

using namespace ctgl;
using namespace forge;

// Unit tests for the ctgl::path::length() function.
TEST(PathTest, Length) {
    // Empty
    EXPECT_EQ(path::length(Path<>{}), 0);

    // Single
    EXPECT_EQ(path::length(Path<E11>{}), 1);
    EXPECT_EQ(path::length(Path<E12>{}), 2);

    // Multiple
    EXPECT_EQ(path::length(Path<E11, E11>{}), 2);
    EXPECT_EQ(path::length(Path<E11, E12>{}), 3);
    EXPECT_EQ(path::length(Path<E12, E11>{}), 3);
    EXPECT_EQ(path::length(Path<E11, E21, E31, E41>{}), 10);
}

// Unit tests for the ctgl::path::nodes() function.
TEST(PathTest, Nodes) {
    // Empty
    EXPECT_EQ(path::nodes(Path<>{}), List<>{});

    // Single
    EXPECT_EQ(path::nodes(Path<E11>{}), List<N1>{});
    EXPECT_EQ(path::nodes(Path<E11, E11>{}), List<N1>{});

    // Multiple
    EXPECT_EQ(path::nodes(Path<E12>{}), (List<N1, N2>{}));
    EXPECT_EQ(path::nodes(Path<E21>{}), (List<N2, N1>{}));
    EXPECT_EQ(path::nodes(Path<E12, E23>{}), (List<N1, N2, N3>{}));
}

// Unit tests for the ctgl::path::dropPrefix() function.
TEST(PathTest, DropPrefix) {
    // Empty
    EXPECT_EQ(path::dropPrefix(N1{}, Path<>{}), Path<>{});

    // Single
    EXPECT_EQ(path::dropPrefix(N1{}, Path<E23>{}), Path<>{});
    EXPECT_EQ(path::dropPrefix(N2{}, Path<E23>{}), Path<E23>{});
    EXPECT_EQ(path::dropPrefix(N3{}, Path<E23>{}), Path<>{});

    // Multiple
    EXPECT_EQ(path::dropPrefix(N1{}, Path<E23, E34>{}), Path<>{});
    EXPECT_EQ(path::dropPrefix(N2{}, Path<E12, E23>{}), Path<E23>{});
    EXPECT_EQ(path::dropPrefix(N3{}, Path<E34, E41>{}), (Path<E34, E41>{}));
    EXPECT_EQ(path::dropPrefix(N4{}, Path<E34, E41, E23>{}), (Path<E41, E23>{}));
}