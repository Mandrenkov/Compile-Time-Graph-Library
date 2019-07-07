#include <sstream>
#include <string>
#include <type_traits>

#include <gtest/gtest.h>

#include "../h/list.h"


using namespace ctgl;


// Convenient Type Aliases
// -----------------------------------------------------------------------------
template <typename T, typename U>
using LinkType = decltype(link(T{}, U{}));

template <typename T, typename U>
using PushType = decltype(push(T{}, U{}));

template <typename T>
using PopType = decltype(pop(T{}));

template <typename T, typename U>
using RemoveType = decltype(remove(T{}, U{}));

template <typename T>
using FrontType = decltype(front(T{}));

template <typename T>
using UniqueType = decltype(unique(T{}));


// Unit Tests
// -----------------------------------------------------------------------------
// Tests for the size() function.
TEST(ListTest, Size) {
    EXPECT_EQ(size(List<>{}), 0);
    EXPECT_EQ(size(List<int>{}), 1);
    EXPECT_EQ(size(List<int, float, double>{}), 3);
    EXPECT_EQ(size(List<int, int>{}), 2);
}

// Tests for the empty() function.
TEST(ListTest, Empty) {
    EXPECT_TRUE(empty(List<>{}));
    EXPECT_FALSE(empty(List<int>{}));
    EXPECT_FALSE(empty(List<int, bool>{}));
}

// Tests for the link() function.
TEST(ListTest, Link) {
    // Empty
    EXPECT_TRUE((std::is_same<LinkType<List<>, List<>>, List<>>::value));

    // Single
    EXPECT_TRUE((std::is_same<LinkType<List<>, List<int>>, List<int>>::value));
    EXPECT_TRUE((std::is_same<LinkType<List<int>, List<>>, List<int>>::value));

    // Multiple
    EXPECT_TRUE((std::is_same<LinkType<List<int>, List<int>>, List<int, int>>::value));
    EXPECT_TRUE((std::is_same<LinkType<List<int>, List<float>>, List<int, float>>::value));
    EXPECT_TRUE((std::is_same<LinkType<List<int, bool>, List<float, double>>, List<int, bool, float, double>>::value));
}

// Tests for the push() function.
TEST(ListTest, Push) {
    EXPECT_TRUE((std::is_same<PushType<int, List<>>, List<int>>::value));
    EXPECT_TRUE((std::is_same<PushType<int, List<bool>>, List<int, bool>>::value));
    EXPECT_TRUE((std::is_same<PushType<int, List<float, double>>, List<int, float, double>>::value));
}

// Tests for the remove() function.
TEST(ListTest, Remove) {
    // Empty
    EXPECT_TRUE((std::is_same<RemoveType<int, List<>>, List<>>::value));

    // Single
    EXPECT_TRUE((std::is_same<RemoveType<int, List<int>>, List<>>::value));
    EXPECT_TRUE((std::is_same<RemoveType<bool, List<int>>, List<int>>::value));

    // Multiple
    EXPECT_TRUE((std::is_same<RemoveType<int, List<int, int>>, List<>>::value));
    EXPECT_TRUE((std::is_same<RemoveType<int, List<int, float, int>>, List<float>>::value));
    EXPECT_TRUE((std::is_same<RemoveType<int, List<float, double>>, List<float, double>>::value));
}

// Tests for the front() function.
TEST(ListTest, Front) {
    EXPECT_TRUE((std::is_same<FrontType<List<int>>, int>::value));
    EXPECT_TRUE((std::is_same<FrontType<List<int, float, double>>, int>::value));
}

// Tests for the contains() function.
TEST(ListTest, Contains) {
    // Empty
    EXPECT_FALSE(contains(int{}, List<>{}));

    // Found
    EXPECT_TRUE(contains(int{}, List<int>{}));
    EXPECT_TRUE(contains(bool{}, List<int, bool>{}));

    // Not Found
    EXPECT_FALSE(contains(int{}, List<float>{}));
    EXPECT_FALSE(contains(bool{}, List<int, float, double>{}));
}

// Tests for the unique() function.
TEST(ListTest, Unique) {
    // Empty
    EXPECT_TRUE((std::is_same<UniqueType<List<>>, List<>>::value));

    // Identity
    EXPECT_TRUE((std::is_same<UniqueType<List<int>>, List<int>>::value));
    EXPECT_TRUE((std::is_same<UniqueType<List<int, double>>, List<int, double>>::value));

    // Duplicates
    EXPECT_TRUE((std::is_same<UniqueType<List<int, int>>, List<int>>::value));
    EXPECT_TRUE((std::is_same<UniqueType<List<int, bool, int>>, List<bool, int>>::value));
    EXPECT_TRUE((std::is_same<UniqueType<List<bool, int, bool, int>>, List<bool, int>>::value));
}

// Tests for the "==" operator.
TEST(ListTest, Equals) {
    // Empty
    EXPECT_TRUE(List<>{} == List<>{});

    // Single
    EXPECT_TRUE(List<int>{}  == List<int>{});
    EXPECT_FALSE(List<int>{} == List<>{});
    EXPECT_FALSE(List<>{}    == List<int>{});
    EXPECT_FALSE(List<int>{} == List<bool>{});

    // Multiple
    EXPECT_TRUE((List<int, bool>{}) == (List<int, bool>{}));
    EXPECT_TRUE((List<int, float, double>{}) == (List<int, float, double>{}));
    EXPECT_FALSE((List<int, bool>{}) == (List<>{}));
    EXPECT_FALSE((List<>{}) == (List<int, bool>{}));
    EXPECT_FALSE((List<int, bool>{}) == (List<int>{}));
    EXPECT_FALSE((List<int, bool>{}) == (List<bool>{}));
    EXPECT_FALSE((List<int, bool>{}) == (List<bool, int>{}));
}

// Tests for the "+" operator.
TEST(ListTest, Plus) {
    // Empty
    EXPECT_TRUE(List<>{} + List<>{} == List<>{});

    // Single
    EXPECT_TRUE(int{} + List<>{} == List<int>{});
    EXPECT_TRUE(List<>{} + int{} == List<int>{});

    // Multiple
    EXPECT_TRUE((int{} + List<int>{} == List<int, int>{}));
    EXPECT_TRUE((int{} + List<bool>{} == List<int, bool>{}));
    EXPECT_TRUE((List<int>{} + bool{} == List<int, bool>{}));
    EXPECT_TRUE((List<int>{} + List<bool>{} == List<int, bool>{}));
}

// Tests for the "<<" operator.
TEST(ListTest, OutputStream) {
    {   // Empty
        std::ostringstream stream;
        stream << List<>{};
        const std::string have = stream.str();
        const std::string want = "";
        EXPECT_EQ(want, have);
    }

    {   // Single
        std::ostringstream stream;
        stream << List<int>{};
        const std::string have = stream.str();
        const std::string want = typeid(int).name();
        EXPECT_EQ(want, have);
    }

    {   // Multiple
        std::ostringstream stream;
        stream << List<int, float>{};
        const std::string have = stream.str();
        const std::string i_name = typeid(int).name();
        const std::string f_name = typeid(float).name();
        const std::string want = i_name + " " + f_name;
        EXPECT_EQ(want, have);
    }
}