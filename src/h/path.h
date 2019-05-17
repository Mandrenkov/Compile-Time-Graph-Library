#pragma once

#include "graph.h"
#include "list.h"

namespace ctgl {
    namespace path {
        // Path represents a sequences of Edges.
        template <typename... Es>
        using Path = ctgl::List<Es...>;

        // Compile-Time Functions
        // -------------------------------------------------------------------------

        // [Template Specialization] No Edges remain in the Path.
        constexpr int length(Path<>) {
            return 0;
        }

        // Returns the length of the given Path.
        template <typename F, typename T, int W, typename... Es>
        constexpr int length(Path<Edge<F, T, W>, Es...>) {
            return W + length(Path<Es...>{});
        }


        // [Template Specialization] No Edges remain in the Path.
        constexpr auto nodes(Path<>) {
            return List<>{};
        }

        // Returns a List of unique Nodes in the given Path.
        template <typename F, typename T, int W, typename... Es>
        constexpr auto nodes(Path<Edge<F, T, W>, Es...>) {
            return decltype(list::unique(list::link(List<F, T>{}, nodes(Path<Es...>{})))){};
        }
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template <typename... Es>
    using Path = ctgl::path::Path<Es...>;
}