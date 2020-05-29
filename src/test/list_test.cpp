#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "../h/list.h"

using namespace ctgl;

// Unit tests for the ctgl::list::size() function.
TEST(ListTest, Size) {
    // Empty
    EXPECT_EQ(list::size(List<>{}), 0);

    // Not Empty
    EXPECT_EQ(list::size(List<int>{}), 1);
    EXPECT_EQ(list::size(List<int, int>{}), 2);
    EXPECT_EQ(list::size(List<int, float, double>{}), 3);
}

// Unit tests for the ctgl::list::empty() function.
TEST(ListTest, Empty) {
    // Empty
    EXPECT_TRUE(empty(List<>{}));

    // Not Empty
    EXPECT_FALSE(empty(List<int>{}));
    EXPECT_FALSE(empty(List<int, bool>{}));
}

// Unit tests for the ctgl::list::remove() function.
TEST(ListTest, Remove) {
    // Empty
    EXPECT_EQ(remove(int{}, List<>{}), List<>{});

    // Single
    EXPECT_EQ(remove(int{}, List<int>{}), List<>{});
    EXPECT_EQ(remove(bool{}, List<int>{}), List<int>{});

    // Multiple
    EXPECT_EQ(remove(int{}, List<int, int>{}), List<>{});
    EXPECT_EQ(remove(int{}, List<int, float, int>{}), List<float>{});
    EXPECT_EQ(remove(int{}, List<float, double>{}), (List<float, double>{}));
}

// Unit tests for the ctgl::list::front() function.
TEST(ListTest, Front) {
    EXPECT_EQ(front(List<int>{}), int{});
    EXPECT_EQ(front(List<int, float, double>{}), int{});
}

// Unit tests for the ctgl::list::contains() function.
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

// Unit tests for the ctgl::list::unique() function.
TEST(ListTest, Unique) {
    // Empty
    EXPECT_EQ(unique(List<>{}), List<>{});

    // Identity
    EXPECT_EQ(unique(List<int>{}), List<int>{});
    EXPECT_EQ(unique(List<int, double>{}), (List<int, double>{}));

    // Duplicates
    EXPECT_EQ(unique(List<int, int>{}), List<int>{});
    EXPECT_EQ(unique(List<int, bool, int>{}), (List<bool, int>{}));
    EXPECT_EQ(unique(List<bool, int, bool, int>{}), (List<bool, int>{}));
}

// Unit tests for the ctgl::list::permutations() function.
TEST(ListTest, Permutations) {
    // Empty
    EXPECT_EQ(permutations(List<>{}), List<>{});

    // Not Empty
    EXPECT_EQ(permutations(List<int>{}), List<List<int>>{});
    EXPECT_EQ(permutations(List<int, bool>{}), (List<List<int, bool>, List<bool, int>>{}));
    EXPECT_EQ(permutations(List<int, bool, long>{}), (List<List<int, bool, long>,
                                                           List<int, long, bool>,
                                                           List<bool, int, long>,
                                                           List<bool, long, int>,
                                                           List<long, int, bool>,
                                                           List<long, bool, int>>{}));
}

// Unit tests for the ctgl::list::== operator.
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

// Unit tests for the ctgl::list::+ operator.
TEST(ListTest, Plus) {
    // Empty
    EXPECT_EQ(List<>{} + List<>{}, List<>{});

    // Single
    EXPECT_EQ(int{} + List<>{}, List<int>{});
    EXPECT_EQ(List<>{} + int{}, List<int>{});

    // Multiple
    EXPECT_EQ(int{} + List<int>{}, (List<int, int>{}));
    EXPECT_EQ(int{} + List<bool>{}, (List<int, bool>{}));
    EXPECT_EQ(List<int>{} + bool{}, (List<int, bool>{}));
    EXPECT_EQ(List<int>{} + List<bool>{}, (List<int, bool>{}));
}

// Unit tests for the ctgl::list::* operator.
TEST(ListTest, Star) {
    // Empty
    EXPECT_EQ(int{} * List<>{}, List<>{});
    EXPECT_EQ(List<>{} * int{}, List<>{});
    EXPECT_EQ(List<>{} * List<>{}, List<>{});

    // Single
    EXPECT_EQ(int{} * List<List<bool>>{}, (List<List<int, bool>>{}));
    EXPECT_EQ(List<List<bool>>{} * int{}, (List<List<bool, int>>{}));
    EXPECT_EQ(List<List<int>>{} * List<List<bool>>{}, (List<List<int, bool>>{}));

    // Multiple
    EXPECT_EQ(int{} * (List<List<float, double>>{}), (List<List<int, float, double>>{}));
    EXPECT_EQ(int{} * (List<List<bool>, List<long>>{}), (List<List<int, bool>, List<int, long>>{}));
    EXPECT_EQ((List<List<float, double>>{}) * int{}, (List<List<float, double, int>>{}));
    EXPECT_EQ((List<List<bool>, List<long>>{}) * int{}, (List<List<bool, int>, List<long, int>>{}));
    EXPECT_EQ((List<List<bool>, List<long>>{}) * (List<List<int>, List<char>>{}), (List<List<bool, int>,
                                                                                        List<bool, char>,
                                                                                        List<long, int>,
                                                                                        List<long, char>>{}));
}

// Unit tests for the ctgl::list::<< operator.
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