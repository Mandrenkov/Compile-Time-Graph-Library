#pragma once

#include "list.h"

namespace ctgl {

    // Declarations
    // -------------------------------------------------------------------------

    namespace path {
        // Path represents a sequences of Edges.
        template <typename... Es>
        using Path = ctgl::List<Es...>;

        // DNE represents an invalid Path (e.g., the path between two disconnected nodes).
        namespace { struct invalid{}; }
        constexpr auto DNE = Path<invalid>{};

        // Calculates the length of the given Path.
        template <typename... Es>
        constexpr int length(Path<Es...>) noexcept;

        // Finds the unique Nodes in the given Path.
        template <typename... Es>
        constexpr auto nodes(Path<Es...>) noexcept;

        // Drops all Edges prior to the given Node in the provided Path.
        template <typename T, typename... Es>
        constexpr auto dropPrefix(T, Path<Es...>) noexcept;

        template <typename T>
        constexpr auto dropPrefix(T, Path<>) noexcept;

        // Chooses the "shorter" of the given Paths using the following tabular expression:
        // +--------------------------------------------------+     +----+
        // | p1 == DNE                                        | --> | p2 |
        // +-----------+--------------------------------------+     +----+
        // | p1 != DNE | p2 == DNE                            | --> | p1 |
        // |           +-----------+--------------------------+     +----+
        // |           | p2 != DNE | length(p1) <  length(p2) | --> | p1 |
        // |           |           +--------------------------+     +----+
        // |           |           | length(p1) >= length(p2) | --> | p2 |
        // +-----------------------+--------------------------+     +----+
        template <typename... Ts, typename... Us>
        constexpr auto shortest(Path<Ts...> p1, Path<Us...> p2) noexcept;
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
        constexpr auto dropPrefix(T, Path<E, Es...>) noexcept {\
            constexpr bool match = std::is_same<T, typename E::Tail>::value;
            if constexpr (match) {
                return Path<E, Es...>{};
            } else {
                return dropPrefix(T{}, Path<Es...>{});
            }
        }

        template <typename T>
        constexpr auto dropPrefix(T, Path<>) noexcept {
            return Path<>{};
        }

        template <typename... Ts, typename... Us>
        constexpr auto shortest(Path<Ts...> p1, Path<Us...> p2) noexcept {
            if constexpr (p1 == DNE) {
                return p2;
            } else if constexpr (p2 == DNE) {
                return p1;
            } else if constexpr (length(p1) < length(p2)) {
                return p1;
            } else {
                return p2;
            }
        }
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template <typename... Es>
    using Path = ctgl::path::Path<Es...>;
}