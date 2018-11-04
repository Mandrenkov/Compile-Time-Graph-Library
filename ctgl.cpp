#include <iostream>

#include "ctgl.h"

int main() {
    std::cout << "Running the Compile Time Graph Library...\n\n";

    using namespace ctgl;

    // Sanity Checks (Future Unit Tests)
    // -------------------------------------------------------------------------

    // Displaying a List.
    std::cout << "Display: List<> = [" << List<>{} << "].\n";
    std::cout << "Display: List<i> = [" << List<int>{} << "].\n";
    std::cout << "Display: List<i, f> = [" << List<int, float>{} << "].\n";
    std::cout << '\n';

    // Concatenating two Lists.
    std::cout << "Concat: List<> + List<> = [" << decltype(concat(List<>{}, List<>{})){} << "].\n";
    std::cout << "Concat: List<i> + List<> = [" << decltype(concat(List<int>{}, List<>{})){} << "].\n";
    std::cout << "Concat: List<i> + List<i> = [" << decltype(concat(List<>{}, List<int>{})){} << "].\n";
    std::cout << "Concat: List<i, f> = [" << decltype(concat(List<int>{}, List<float>{})){} << "].\n";
    std::cout << '\n';

    // Pushing types to a List.
    std::cout << "Push: i + List<> = [" << decltype(push(int{}, List<>{})){} << "].\n";
    std::cout << "Push: i + List<f> = [" << decltype(push(int{}, List<float>{})){} << "].\n";
    std::cout << "Push: i + List<f, d> = [" << decltype(push(int{}, List<float, double>{})){} << "].\n";
    std::cout << '\n';

    // Popping types from a List.
    std::cout << "Pop: List<i> - i = [" << decltype(pop(List<int>{})){} << "].\n";
    std::cout << "Pop: List<i, f> - i = [" << decltype(pop(List<int, float>{})){} << "].\n";
    std::cout << "Pop: List<i, f, d> - i = [" << decltype(pop(List<int, float, double>{})){} << "].\n";
    std::cout << '\n';

    // Querying the front of a List.
    std::cout << "Front: List<i> = " << typeid(decltype(front(List<int>{}))).name() << ".\n";
    std::cout << "Front: List<i, f> = " << typeid(decltype(front(List<int, float>{}))).name() << ".\n";
    std::cout << "Front: List<i, f, d> = " << typeid(decltype(front(List<int, float, double>{}))).name() << ".\n";
    std::cout << '\n';

    // Querying the content of a List.
    std::cout << "Contains: i in List<> = " << contains(int{}, List<>{}) << ".\n";
    std::cout << "Contains: i in List<i> = " << contains(int{}, List<int>{}) << ".\n";
    std::cout << "Contains: f in List<i> = " << contains(float{}, List<int>{}) << ".\n";
    std::cout << "Contains: f in List<i, f> = " << contains(float{}, List<int, float>{}) << ".\n";
    std::cout << '\n';

    // Graph: A --> B --> C
    //              `--> D
    // using D = Node<4>;
    // using C = Node<3>;
    // using B = Node<2>;
    // using A = Node<1>;

    // using E1 = Edge<B, C>;
    // using E2 = Edge<B, D>;
    // using E3 = Edge<A, B>;

    // using G = Graph<List<A, B, C, D>, List<E1, E2, E3>>;

    // // Test: A --> B --> C
    // using S = A;
    // using T = C;
    // constexpr int distance = dfs(G{}, S{}, T{});
    // static_assert(distance == 2, "Failed the sanity check.");

    // std::cout << "The distance from Node " << S::id << " to " << T::id << " is " << distance << ".\n";

    std::cout << "Done.\n";
}