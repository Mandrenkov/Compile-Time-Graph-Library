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
        constexpr int length(Path<Es...>) noexcept ;

        // Finds the unique Nodes in the given Path.
        template <typename... Es>
        constexpr auto nodes(Path<Es...>) noexcept ;
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
            return list::unique(List<typename E::From, typename E::To>{} + nodes(Path<Es...>{}));
        }

        template<>
        constexpr auto nodes(Path<>) noexcept {
            return List<>{};
        }
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template <typename... Es>
    using Path = ctgl::path::Path<Es...>;
}