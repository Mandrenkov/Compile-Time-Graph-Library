#pragma once

#include <limits>

// Constants
// -----------------------------------------------------------------------------
namespace ctgl {
    // INF represents an invalid distance (e.g., the distance between two disconnected nodes).
    constexpr int INF = std::numeric_limits<int>::max();
}

// Types
// -----------------------------------------------------------------------------
namespace ctgl {
    namespace util {
        // Type that only compiles if |T| is the same as |U|.
        template <typename T, typename U>
        using enable_if_same_t = std::enable_if_t<std::is_same_v<T, U>>;

        // Type that only compiles if |T| is different from |U|.
        template <typename T, typename U>
        using enable_if_diff_t = std::enable_if_t<!std::is_same_v<T, U>>;
    }
}