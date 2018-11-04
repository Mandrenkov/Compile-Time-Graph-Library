#include <iostream>

#include "ctgl.h"

int main() {
    std::cout << "Running the Compile Time Graph Library...\n\n";

    using namespace ctgl;

    // Sanity Checks (Future Unit Tests)
    // -------------------------------------------------------------------------

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