#pragma once

#include <limits>

// CTGL Constants
// -----------------------------------------------------------------------------
namespace ctgl {
    // INF represents an invalid distance (e.g., the distance between two disconnected nodes).
    constexpr int INF = std::numeric_limits<int>::max();
}

// CTGL Global Types
// -----------------------------------------------------------------------------
namespace ctgl {
    namespace detail {
        // An ADL instance must be passed as the first argument to each function
        // to ensure that ADL can be used to resolve recursive return types.
        struct ADL {};

        // Type that does not compile if |T| is different from |U|.
        template <typename T, typename U>
        using enable_if_same_t = std::enable_if_t<std::is_same_v<T, U>>;

        // Type that does not compile if |T| is the same as |U|.
        template <typename T, typename U>
        using enable_if_diff_t = std::enable_if_t<!std::is_same_v<T, U>>;
    }
}