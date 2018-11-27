#include <sstream>
#include <string>
#include <type_traits>

#include <gtest/gtest.h>

#include "list.h"


using namespace ctgl;

// size() Unit Tests
// -----------------------------------------------------------------------------
TEST(ListTest, SizeEmpty) {
    EXPECT_EQ(size(List<>{}), 0);
}

TEST(ListTest, SizeSingle) {
    EXPECT_EQ(size(List<int>{}), 1);
}

TEST(ListTest, SizeMultiple) {
    EXPECT_EQ(size(List<int, float, double>{}), 3);
}

TEST(ListTest, SizeDuplicate) {
    EXPECT_EQ(size(List<int, int>{}), 2);
}

// empty() Unit Tests
// -----------------------------------------------------------------------------
TEST(ListTest, EmptyVacant) {
    EXPECT_TRUE(empty(List<>{}));
}

TEST(ListTest, EmptyOccupied) {
    EXPECT_FALSE(empty(List<int>{}));
    EXPECT_FALSE(empty(List<int, bool>{}));
}

// link() Unit Tests
// -----------------------------------------------------------------------------
template <typename T, typename U>
using LinkType = decltype(link(T{}, U{}));

TEST(ListTest, LinkEmpty) {
    EXPECT_TRUE((std::is_same<LinkType<List<>, List<>>, List<>>::value));
}

TEST(ListTest, LinkSingle) {
    EXPECT_TRUE((std::is_same<LinkType<List<>, List<int>>, List<int>>::value));
    EXPECT_TRUE((std::is_same<LinkType<List<int>, List<>>, List<int>>::value));
}

TEST(ListTest, LinkBoth) {
    EXPECT_TRUE((std::is_same<LinkType<List<int>, List<int>>, List<int, int>>::value));
    EXPECT_TRUE((std::is_same<LinkType<List<int>, List<float>>, List<int, float>>::value));
    EXPECT_TRUE((std::is_same<LinkType<List<int, bool>, List<float, double>>, List<int, bool, float, double>>::value));
}

// push() Unit Tests
// -----------------------------------------------------------------------------
template <typename T, typename U>
using PushType = decltype(push(T{}, U{}));

TEST(ListTest, PushEmpty) {
    EXPECT_TRUE((std::is_same<PushType<int, List<>>, List<int>>::value));
}

TEST(ListTest, PushSingle) {
    EXPECT_TRUE((std::is_same<PushType<int, List<bool>>, List<int, bool>>::value));
}

TEST(ListTest, PushMultiple) {
   EXPECT_TRUE((std::is_same<PushType<int, List<float, double>>, List<int, float, double>>::value));
}

// pop() Unit Tests
// -----------------------------------------------------------------------------
template <typename T>
using PopType = decltype(pop(T{}));

TEST(ListTest, PopSingle) {
    EXPECT_TRUE((std::is_same<PopType<List<int>>, List<>>::value));
}

TEST(ListTest, PopMultiple) {
    EXPECT_TRUE((std::is_same<PopType<List<int, float, double>>, List<float, double>>::value));
}

// remove() Unit Tests
// -----------------------------------------------------------------------------
template <typename T, typename U>
using RemoveType = decltype(remove(T{}, U{}));

TEST(ListTest, RemoveEmpty) {
    EXPECT_TRUE((std::is_same<RemoveType<int, List<>>, List<>>::value));
}

TEST(ListTest, RemoveSingle) {
    EXPECT_TRUE((std::is_same<RemoveType<int, List<int>>, List<>>::value));
    EXPECT_TRUE((std::is_same<RemoveType<bool, List<int>>, List<int>>::value));
}

TEST(ListTest, RemoveMultiple) {
    EXPECT_TRUE((std::is_same<RemoveType<int, List<int, int>>, List<>>::value));
    EXPECT_TRUE((std::is_same<RemoveType<int, List<int, float, int>>, List<float>>::value));
    EXPECT_TRUE((std::is_same<RemoveType<int, List<float, double>>, List<float, double>>::value));
}

// front() Unit Tests
// -----------------------------------------------------------------------------
template <typename T>
using FrontType = decltype(front(T{}));

TEST(ListTest, FrontSingle) {
    EXPECT_TRUE((std::is_same<FrontType<List<int>>, int>::value));
}

TEST(ListTest, FrontMultiple) {
    EXPECT_TRUE((std::is_same<FrontType<List<int, float, double>>, int>::value));
}

// contains() Unit Tests
// -----------------------------------------------------------------------------
TEST(ListTest, ContainsEmpty) {
    EXPECT_FALSE(contains(int{}, List<>{}));
}

TEST(ListTest, ContainsFound) {
    EXPECT_TRUE(contains(int{}, List<int>{}));
    EXPECT_TRUE(contains(bool{}, List<int, bool>{}));
}

TEST(ListTest, ContainsNotFound) {
    EXPECT_FALSE(contains(int{}, List<float>{}));
    EXPECT_FALSE(contains(bool{}, List<int, float, double>{}));
}

// operator==() Unit Tests
// -----------------------------------------------------------------------------
TEST(ListTest, EqualEmpty) {
    EXPECT_TRUE(List<>{} == List<>{});
}

TEST(ListTest, EqualSingle) {
    EXPECT_TRUE(List<int>{}  == List<int>{});
    EXPECT_FALSE(List<int>{} == List<>{});
    EXPECT_FALSE(List<>{}    == List<int>{});
    EXPECT_FALSE(List<int>{} == List<bool>{});
}

TEST(ListTest, EqualMultiple) {
    EXPECT_TRUE((List<int, bool>{})          == (List<int, bool>{}));
    EXPECT_TRUE((List<int, float, double>{}) == (List<int, float, double>{}));
    EXPECT_FALSE((List<int, bool>{})         == (List<>{}));
    EXPECT_FALSE((List<>{})                  == (List<int, bool>{}));
    EXPECT_FALSE((List<int, bool>{})         == (List<int>{}));
    EXPECT_FALSE((List<int, bool>{})         == (List<bool>{}));
    EXPECT_FALSE((List<int, bool>{})         == (List<bool, int>{}));
}

// Output Stream Unit Tests
// -----------------------------------------------------------------------------
TEST(ListTest, OutputStreamEmpty) {
    std::ostringstream stream;
    stream << List<>{};
    const std::string have = stream.str();
    const std::string want = "";
    EXPECT_EQ(want, have);
}

TEST(ListTest, OutputStreamSingle) {
    std::ostringstream stream;
    stream << List<int>{};
    const std::string have = stream.str();
    const std::string want = typeid(int).name();
    EXPECT_EQ(want, have);
}

TEST(ListTest, OutputStreamMultiple) {
    std::ostringstream stream;
    stream << List<int, float>{};
    const std::string have = stream.str();
    const std::string i_name = typeid(int).name();
    const std::string f_name = typeid(float).name();
    const std::string want = i_name + " " + f_name;
    EXPECT_EQ(want, have);
}