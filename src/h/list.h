#pragma once

#include <iostream>
#include <typeinfo>

namespace ctgl {

    // Declarations
    // -------------------------------------------------------------------------

    namespace list {
        // List represents a list of types.
        template <typename... Ts>
        struct List {};

        // Compile-Time Functions
        // ---------------------------------------------------------------------

        // Returns the size of the given List.
        template <typename... Ts>
        constexpr int size(List<Ts...>);

        // Reports whether the given List is empty.
        template <typename... Ts>
        constexpr bool empty(List<Ts...>);

        // Links the given Lists in their provided order.
        template <typename... Ts, typename... Us>
        constexpr auto link(List<Ts...>, List<Us...>);

        // Pushes the given element to the front of the provided List.
        template <typename T, typename... Ts>
        constexpr auto push(T, List<Ts...>);

        // Removes all occurrences of the given element from the provided List.
        template <typename T, typename F, typename... Ts>
        constexpr auto remove(T, List<F, Ts...>);

        // Returns the element at the front of the given List.
        template <typename T, typename... Ts>
        constexpr auto front(List<T, Ts...>);

        // Reports whether the given element exists in the provided List.
        template <typename T, typename F, typename... Ts>
        constexpr bool contains(T, List<F, Ts...>);

        // Removes all duplicate elements from the given List.
        template <typename T, typename... Ts>
        constexpr auto unique(List<T, Ts...>);

        // Reports whether the given Lists are the same.
        template <typename... Ts>
        constexpr bool operator==(List<Ts...>, List<Ts...>);

        // Adds an element to the front of a List.
        template <typename T, typename... Ts>
        constexpr auto operator+(T, List<Ts...>);

        // Adds an element to the back of a List.
        template <typename... Ts, typename T>
        constexpr auto operator+(List<Ts...>, T);

        // Concatanates two Lists together.
        template <typename... Ts, typename... Us>
        constexpr auto operator+(List<Ts...>, List<Us...>);
    }

    // Definitions
    // -------------------------------------------------------------------------

    namespace list {
        // Compile-Time Functions
        // ---------------------------------------------------------------------

        template <typename... Ts>
        constexpr int size(List<Ts...>) {
            return sizeof...(Ts);
        }

        template <typename... Ts>
        constexpr bool empty(List<Ts...>) {
            return sizeof...(Ts) == 0;
        }

        template <typename... Ts, typename... Us>
        constexpr auto link(List<Ts...>, List<Us...>) {
            return List<Ts..., Us...>{};
        }

        template <typename T, typename... Ts>
        constexpr auto push(T, List<Ts...>) {
            return List<T, Ts...>{};
        }

        template <typename T, typename... Ts>
        constexpr auto pop(List<T, Ts...>) {
            return List<Ts...>{};
        }

        template <typename T, typename F, typename... Ts>
        constexpr auto remove(T, List<F, Ts...>) {
            return push(F{}, remove(T{}, List<Ts...>{}));
        }

        template <typename T, typename... Ts>
        constexpr auto remove(T, List<T, Ts...>) {
            return remove(T{}, List<Ts...>{});
        }

        template <typename T>
        constexpr auto remove(T, List<>) {
            return List<>{};
        }

        template <typename T, typename... Ts>
        constexpr auto front(List<T, Ts...>) {
            return T{};
        }

        template <typename T, typename F, typename... Ts>
        constexpr bool contains(T, List<F, Ts...>) {
            return contains(T{}, List<Ts...>{});
        }

        template <typename T, typename... Ts>
        constexpr bool contains(T, List<T, Ts...>) {
            return true;
        }

        template <typename T>
        constexpr bool contains(T, List<>) {
            return false;
        }

        template <typename T, typename... Ts>
        constexpr auto unique(List<T, Ts...>) {
            constexpr bool found = contains(T{}, List<Ts...>{});
            if constexpr (found) {
                return unique(List<Ts...>{});
            } else {
                return decltype(push(T{}, unique(List<Ts...>{}))){};
            }
        }

        constexpr auto unique(List<>) {
            return List<>{};
        }

        template <typename... Ts>
        constexpr bool operator==(List<Ts...>, List<Ts...>) {
            return true;
        }

        template <typename... Ts, typename... Us>
        constexpr bool operator==(List<Ts...>, List<Us...>) {
            return false;
        }

        template <typename T, typename... Ts>
        constexpr auto operator+(T, List<Ts...>) {
            return List<T>{} + List<Ts...>{};
        }

        template <typename... Ts, typename T>
        constexpr auto operator+(List<Ts...>, T) {
            return List<Ts...>{} + List<T>{};
        }

        template <typename... Ts, typename... Us>
        constexpr auto operator+(List<Ts...>, List<Us...>) {
            return List<Ts..., Us...>{};
        }

        // Run-Time Functions
        // ---------------------------------------------------------------------

        // Streams the names of the types that compose the given List to the provided output stream.
        template <typename T, typename... Ts, typename = std::enable_if_t<sizeof... (Ts) != 0>>
        inline std::ostream& operator<<(std::ostream& out, const List<T, Ts...>& list) {
            return out << typeid(T).name() << ' ' << List<Ts...>{};
        }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& out, const List<T>& list) {
            return out << typeid(T).name();
        }

        inline std::ostream& operator<<(std::ostream& out, const List<>& list) {
            return out;
        }
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template<typename... Ts>
    using List = ctgl::list::List<Ts...>;
}