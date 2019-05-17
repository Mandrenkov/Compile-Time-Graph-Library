#include <iostream>

#include "../h/ctgl.h"

int main() {
    std::cout << "Running the CTGL examples...\n\n";

    // Example 1
    // -------------------------------------------------------------------------
    // Create Nodes with IDs 1, 2, and 3.
    using n1 = ctgl::Node<1>;
    using n2 = ctgl::Node<2>;
    using n3 = ctgl::Node<3>;
    using nodes = ctgl::List<n1, n2, n3>;

    // Create Edges that connect some of the Nodes.
    // (1) --4--> (2) --4--> (3)
    //  `----------9----------^
    using e12 = ctgl::Edge<n1, n2, 4>;
    using e13 = ctgl::Edge<n1, n3, 9>;
    using e23 = ctgl::Edge<n2, n3, 4>;
    using edges = ctgl::List<e12, e13, e23>;

    // Compose the Nodes and Edges to form a Graph.
    using graph = ctgl::Graph<nodes, edges>;

    // Find the distance between Node 1 and Node 3 (i.e., 8).
    constexpr int dist = ctgl::distance(graph{}, n1{}, n3{});
    std::cout << "The distance between Node 1 and Node 3 is " << dist << ".\n";

    std::cout << "\nDone.\n";
}
