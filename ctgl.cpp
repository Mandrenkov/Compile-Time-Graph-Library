#include <iostream>

#include "ctgl.h"

int main() {
    std::cout << "Running the Compile Time Graph Library...\n";

    using namespace ctgl;

    // Sanity Check
    // -------------------------------------------------------------------------

    // Graph: A --> B --> C
    //              `--> D
    using D = Node<4>;
    using C = Node<3>;
    using B = Node<2, C, D>;
    using A = Node<1, B>;

    // Test: A --> B --> C
    using S = A;
    using T = C;
    constexpr int distance = dfs(S{}, T{});
    static_assert(distance == 2, "Failed the sanity check.");

    std::cout << "The distance from Node " << S::id << " to " << T::id << " is " << distance << ".\n";
}