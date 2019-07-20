#pragma once

#include "list.h"

namespace ctgl {

    // Declarations
    // -------------------------------------------------------------------------

    namespace path {
        // Path represents a sequences of Edges.
        template <typename... Es>
        using Path = ctgl::List<Es...>;

        // Calculates the length of the given Path.
        template <typename... Es>
        constexpr int length(Path<Es...>) noexcept;

        // Finds the unique Nodes in the given Path.
        template <typename... Es>
        constexpr auto nodes(Path<Es...>) noexcept;

        // Drops all Edges prior to the given Node in the provided Path.
        template <typename T, typename... Es>
        constexpr auto drop(T, Path<Es...>) noexcept;

        template <typename T>
        constexpr auto drop(T, Path<>) noexcept;
    }

    // Definitions
    // -------------------------------------------------------------------------

    namespace path {
        template <typename E, typename... Es>
        constexpr int length(Path<E, Es...>) noexcept {
            return E::weight + length(Path<Es...>{});
        }

        template<>
        constexpr int length(Path<>) noexcept {
            return 0;
        }

        template <typename E, typename... Es>
        constexpr auto nodes(Path<E, Es...>) noexcept {
            return list::unique(List<typename E::Tail, typename E::Head>{} + nodes(Path<Es...>{}));
        }

        template<>
        constexpr auto nodes(Path<>) noexcept {
            return List<>{};
        }

        template <typename T, typename E, typename... Es>
        constexpr auto drop(T, Path<E, Es...>) noexcept {\
            constexpr bool match = std::is_same<T, typename E::Tail>::value;
            if constexpr (match) {
                return Path<E, Es...>{};
            } else {
                return drop(T{}, Path<Es...>{});
            }
        }

        template <typename T>
        constexpr auto drop(T, Path<>) noexcept {
            return Path<>{};
        }
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template <typename... Es>
    using Path = ctgl::path::Path<Es...>;

    // DNE represents an invalid Path (e.g., the path between two disconnected nodes).
    namespace { struct invalid{}; }
    constexpr auto DNE = Path<invalid>{};
}