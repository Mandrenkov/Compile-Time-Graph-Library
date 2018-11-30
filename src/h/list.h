#pragma once

#include <iostream>
#include <typeinfo>

namespace ctgl {
    // List represents the list of types specified by |Ts|.
    template <typename... Ts>
    struct List {};


    // Compile-Time Functions
    // -------------------------------------------------------------------------

    // Returns the size of the given List.
    template <typename... Ts>
    constexpr int size(List<Ts...>) { return sizeof...(Ts); }

    // Returns true if the given List is empty.
    template <typename... Ts>
    constexpr bool empty(List<Ts...>) { return sizeof...(Ts) == 0; }

    // Returns a new List that is the concatenation of the given Lists.
    template <typename... Ts, typename... Us>
    constexpr auto link(List<Ts...>, List<Us...>) -> List<Ts..., Us...>;

    // Returns a new List that is constructed by pushing |T| to the front of the given List.
    template <typename T, typename... Ts>
    constexpr auto push(T, List<Ts...>) -> List<T, Ts...>;

    // Returns a new List that is constructed by popping the type at the front of the given List.
    template <typename T, typename... Ts>
    constexpr auto pop(List<T, Ts...>) -> List<Ts...>;

    // Returns a new List that is constructed by removing all occurrences of type |T| from the given List.
    template <typename T, typename F, typename... Ts>
    constexpr auto remove(T, List<F, Ts...>) -> decltype(push(F{}, remove(T{}, List<Ts...>{})));

    template <typename T, typename... Ts>
    constexpr auto remove(T, List<T, Ts...>) -> decltype(remove(T{}, List<Ts...>{}));

    template <typename T>
    constexpr auto remove(T, List<>) -> List<>;

    // Returns the type at the front of the given List.
    template <typename T, typename... Ts>
    constexpr auto front(List<T, Ts...>) -> T;

    // Returns true if the given List contains the provided type.
    template <typename T, typename F, typename... Ts>
    constexpr bool contains(T, List<F, Ts...>) { return contains(T{}, List<Ts...>{}); }

    template <typename T, typename... Ts>
    constexpr bool contains(T, List<T, Ts...>) { return true; }

    template <typename T>
    constexpr bool contains(T, List<>) { return false; }

    // Returns true if the given Lists are the same.
    template <typename T, typename... Ts, typename U, typename... Us>
    constexpr bool operator==(List<T, Ts...>, List<U, Us...>) { return false; }

    template <typename T, typename... Ts, typename... Us>
    constexpr bool operator==(List<T, Ts...>, List<T, Us...>) { return List<Ts...>{} == List<Us...>{}; }

    template <typename T, typename... Ts>
    constexpr bool operator==(List<T, Ts...>, List<>) { return false; }

    template <typename U, typename... Us>
    constexpr bool operator==(List<>, List<U, Us...>) { return false; }

    constexpr bool operator==(List<>, List<>) { return true; }


    // Run-Time Functions
    // -------------------------------------------------------------------------

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