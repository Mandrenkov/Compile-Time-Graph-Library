#pragma once

#include "utility.h"

#include <iostream>
#include <typeinfo>

namespace ctgl {

    // Declarations
    // -------------------------------------------------------------------------

    namespace list {
        // List represents a list of types.
        template <typename... Ts>
        struct List {};

        // Returns the size of the given List.
        template <typename... Ts>
        constexpr int size(List<Ts...>) noexcept;

        // Reports whether the given List is empty.
        template <typename... Ts>
        constexpr bool empty(List<Ts...>) noexcept;

        // Removes all occurrences of the given element from the provided List.
        template <typename T, typename... Ts>
        constexpr auto remove(T, List<Ts...>) noexcept;

        // Returns the element at the front of the given List.
        template <typename T, typename... Ts>
        constexpr auto front(List<T, Ts...>) noexcept;

        // Reports whether the given element exists in the provided List.
        template <typename T, typename... Ts>
        constexpr bool contains(T, List<Ts...>) noexcept;

        // Removes all duplicate elements from the given List.
        template <typename T, typename... Ts>
        constexpr auto unique(List<T, Ts...>) noexcept;

        // Reports whether the given Lists are the same.
        template <typename... Ts>
        constexpr bool operator==(List<Ts...>, List<Ts...>) noexcept;

        // Adds an element to the front of a List.
        template <typename T, typename... Ts>
        constexpr auto operator+(T, List<Ts...>) noexcept;

        // Adds an element to the back of a List.
        template <typename... Ts, typename T>
        constexpr auto operator+(List<Ts...>, T) noexcept;

        // Concatenates two Lists together.
        template <typename... Ts, typename... Us>
        constexpr auto operator+(List<Ts...>, List<Us...>) noexcept;

        // Adds the given element to each List in the provided List of Lists.
        template <typename T, typename... Ts>
        constexpr auto operator*(T, List<Ts...>) noexcept;
    }

    // -------------------------------------------------------------------------

    namespace list {
        template <typename... Ts>
        constexpr int size(List<Ts...>) noexcept {
            return sizeof...(Ts);
        }

        template <typename... Ts>
        constexpr bool empty(List<Ts...>) noexcept {
            return sizeof...(Ts) == 0;
        }

        template <typename T, typename F, typename... Ts>
        constexpr auto remove(T, List<F, Ts...>) noexcept {
            return F{} + remove(T{}, List<Ts...>{});
        }

        template <typename T, typename... Ts>
        constexpr auto remove(T, List<T, Ts...>) noexcept {
            return remove(T{}, List<Ts...>{});
        }

        template <typename T>
        constexpr auto remove(T, List<>) noexcept {
            return List<>{};
        }

        template <typename T, typename... Ts>
        constexpr auto front(List<T, Ts...>) noexcept {
            return T{};
        }

        template <typename T, typename... Ts>
        constexpr bool contains(T, List<T, Ts...>) noexcept {
            return true;
        }

        template <typename T, typename F, typename... Ts>
        constexpr bool contains(T, List<F, Ts...>) noexcept {
            return contains(T{}, List<Ts...>{});
        }

        template <typename T>
        constexpr bool contains(T, List<>) noexcept {
            return false;
        }

        template <typename T, typename... Ts>
        constexpr auto unique(List<T, Ts...>) noexcept {
            constexpr bool found = contains(T{}, List<Ts...>{});
            if constexpr (found) {
                return unique(List<Ts...>{});
            } else {
                return T{} + unique(List<Ts...>{});
            }
        }

        constexpr auto unique(List<>) noexcept {
            return List<>{};
        }

        template <typename... Ts>
        constexpr bool operator==(List<Ts...>, List<Ts...>) noexcept {
            return true;
        }

        template <typename... Ts, typename... Us>
        constexpr bool operator==(List<Ts...>, List<Us...>) noexcept {
            return false;
        }

        template <typename T, typename... Ts>
        constexpr auto operator+(T, List<Ts...>) noexcept {
            return List<T>{} + List<Ts...>{};
        }

        template <typename... Ts, typename T>
        constexpr auto operator+(List<Ts...>, T) noexcept {
            return List<Ts...>{} + List<T>{};
        }

        template <typename... Ts, typename... Us>
        constexpr auto operator+(List<Ts...>, List<Us...>) noexcept {
            return List<Ts..., Us...>{};
        }

        template <typename T>
        constexpr auto operator*(T, List<>) noexcept {
            return List<>{};
        }

        template <typename T, typename... Us, typename... Ts>
        constexpr auto operator*(T, List<List<Us...>, Ts...>) noexcept {
            constexpr auto head = List<List<T, Us...>>{};
            constexpr auto tail = T{} * List<Ts...>{};
            return head + tail;
        }

        // Streams the names of the types that compose the given List to the provided output stream.
        template <typename T, typename... Ts, typename = std::enable_if_t<sizeof... (Ts) != 0>>
        inline std::ostream& operator<<(std::ostream& out, const List<T, Ts...>& list) noexcept {
            return out << typeid(T).name() << ' ' << List<Ts...>{};
        }

        template <typename T>
        inline std::ostream& operator<<(std::ostream& out, const List<T>& list) noexcept {
            return out << typeid(T).name();
        }

        inline std::ostream& operator<<(std::ostream& out, const List<>& list) noexcept {
            return out;
        }
    }

    // Convenient Type Definitions
    // -------------------------------------------------------------------------
    template<typename... Ts>
    using List = ctgl::list::List<Ts...>;
}