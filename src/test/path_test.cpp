#include <gtest/gtest.h>

#include "../h/path.h"
#include "forge.h"

using namespace ctgl;


// Convenient Type Aliases
// -----------------------------------------------------------------------------
template <typename... Es>
using NodesType = decltype(path::nodes(Path<Es...>{}));

template <typename T, typename P>
using DropType = decltype(path::drop(T{}, P{}));


// Unit Tests
// -----------------------------------------------------------------------------
// Tests for the length() function.
TEST(PathTest, Length) {
    // Empty
    EXPECT_EQ(path::length(Path<>{}), 0);

    // Single
    EXPECT_EQ(path::length(Path<forge::E11>{}), 1);
    EXPECT_EQ(path::length(Path<forge::E12>{}), 2);

    // Multiple
    EXPECT_EQ(path::length(Path<forge::E11, forge::E11>{}), 2);
    EXPECT_EQ(path::length(Path<forge::E11, forge::E12>{}), 3);
    EXPECT_EQ(path::length(Path<forge::E12, forge::E11>{}), 3);
    EXPECT_EQ(path::length(Path<forge::E11, forge::E21, forge::E31, forge::E41>{}), 10);
}

// Tests for the nodes() function.
TEST(PathTest, Nodes) {
    // Empty
    EXPECT_TRUE((std::is_same<NodesType<>, List<>>::value));

    // Single
    EXPECT_TRUE((std::is_same<NodesType<forge::E11>, List<forge::N1>>::value));
    EXPECT_TRUE((std::is_same<NodesType<forge::E11, forge::E11>, List<forge::N1>>::value));

    // Multiple
    EXPECT_TRUE((std::is_same<NodesType<forge::E12>, List<forge::N1, forge::N2>>::value));
    EXPECT_TRUE((std::is_same<NodesType<forge::E21>, List<forge::N2, forge::N1>>::value));
    EXPECT_TRUE((std::is_same<NodesType<forge::E12, forge::E23>, List<forge::N1, forge::N2, forge::N3>>::value));
}

// Tests for the drop() function.
TEST(PathTest, Drop) {
    // Empty
    EXPECT_TRUE((std::is_same<DropType<forge::N1, Path<>>, Path<>>::value));

    // Single
    EXPECT_TRUE((std::is_same<DropType<forge::N1, Path<forge::E23>>, Path<>>::value));
    EXPECT_TRUE((std::is_same<DropType<forge::N2, Path<forge::E23>>, Path<forge::E23>>::value));
    EXPECT_TRUE((std::is_same<DropType<forge::N3, Path<forge::E23>>, Path<>>::value));

    // Multiple
    EXPECT_TRUE((std::is_same<DropType<forge::N1, Path<forge::E23, forge::E34>>, Path<>>::value));
    EXPECT_TRUE((std::is_same<DropType<forge::N2, Path<forge::E12, forge::E23>>, Path<forge::E23>>::value));
    EXPECT_TRUE((std::is_same<DropType<forge::N3, Path<forge::E34, forge::E41>>, Path<forge::E34, forge::E41>>::value));
    EXPECT_TRUE((std::is_same<DropType<forge::N4, Path<forge::E34, forge::E41, forge::E23>>, Path<forge::E41, forge::E23>>::value));
}