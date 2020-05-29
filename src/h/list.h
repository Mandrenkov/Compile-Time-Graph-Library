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

        // Generates a List of all the permutations of the given List.
        template <typename... Ts>
        constexpr auto permutations(List<Ts...>) noexcept;

        // Reports whether the given Lists are the same.
        template <typename... Ts>
        constexpr bool operator==(List<Ts...>, List<Ts...>) noexcept;

        // Prepends the given element to the provided List.
        template <typename T, typename... Ts>
        constexpr auto operator+(T, List<Ts...>) noexcept;

        // Appends the given element to the provided List.
        template <typename... Ts, typename T>
        constexpr auto operator+(List<Ts...>, T) noexcept;

        // Concatenates two Lists together.
        template <typename... Ts, typename... Us>
        constexpr auto operator+(List<Ts...>, List<Us...>) noexcept;

        // Prepends the given element to each List in the provided List of Lists.
        template <typename T, typename... Ts>
        constexpr auto operator*(T, List<Ts...>) noexcept;

        // Appends the given element to each List in the provided List of Lists.
        template <typename... Ts, typename T>
        constexpr auto operator*(List<Ts...>, T) noexcept;

        // Takes the Cartesian product of the given Lists of Lists.
        template <typename... Ts, typename... Us>
        constexpr auto operator*(List<Ts...>, List<Us...>) noexcept;
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

        template<typename... Ts>
        constexpr auto permutations(List<Ts...>) noexcept {
            return permutations(List<>{}, List<Ts...>{});
        }

        template<typename T>
        constexpr auto permutations(List<T>) noexcept {
            return List<List<T>>{};
        }
        
        template<typename... Ls, typename R, typename... Rs>
        constexpr auto permutations(List<Ls...>, List<R, Rs...>) noexcept {
            constexpr auto center = R{} * permutations(List<Ls..., Rs...>{});
            constexpr auto suffix = permutations(List<Ls..., R>{}, List<Rs...>{});
            return center + suffix;
        }

        template<typename... Ls>
        constexpr auto permutations(List<Ls...>, List<>) noexcept {
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

        template <typename T, typename... Ts>
        constexpr auto operator*(T, List<Ts...>) noexcept {
            return List<List<T>>{} * List<Ts...>{};
        }

        template <typename... Ts, typename T>
        constexpr auto operator*(List<Ts...>, T) noexcept {
            return List<Ts...>{} * List<List<T>>{};
        }

        template <typename... T>
        constexpr auto distribute(List<T...>, List<>) noexcept {
            return List<>{};
        }

        template <typename... T, typename... U, typename... Us>
        constexpr auto distribute(List<T...>, List<List<U...>, Us...>) noexcept {
            constexpr auto head = List<List<T..., U...>>{};
            constexpr auto tail = distribute(List<T...>{}, List<Us...>{});
            return head + tail;
        }

        template <typename... Us>
        constexpr auto operator*(List<>, List<Us...>) noexcept {
            return List<>{};
        }
        
        template <typename... T, typename... Ts, typename... Us>
        constexpr auto operator*(List<List<T...>, Ts...>, List<Us...>) noexcept {
            constexpr auto head = distribute(List<T...>{}, List<Us...>{});
            constexpr auto tail = List<Ts...>{} * List<Us...>{};
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