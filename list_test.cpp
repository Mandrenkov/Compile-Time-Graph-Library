#include <sstream>
#include <string>
#include <type_traits>

#include <gtest/gtest.h>

#include "list.h"


using namespace ctgl;

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

// append() Unit Tests
// -----------------------------------------------------------------------------
template <typename T, typename U>
using AppendType = decltype(append(T{}, U{}));

TEST(ListTest, AppendEmpty) {
    EXPECT_TRUE((std::is_same<AppendType<int, List<>>, List<int>>::value));
}

TEST(ListTest, AppendSingle) {
    EXPECT_TRUE((std::is_same<AppendType<int, List<bool>>, List<bool, int>>::value));
}

TEST(ListTest, AppendMultiple) {
   EXPECT_TRUE((std::is_same<AppendType<int, List<float, double>>, List<float, double, int>>::value));
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