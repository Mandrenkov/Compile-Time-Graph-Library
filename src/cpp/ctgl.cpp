#include <iostream>

#include "../h/ctgl.h"

int main() {
    std::cout << "Running the CTGL examples...\n\n";

    {
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
        constexpr int dist = ctgl::algorithm::findDistance(graph{}, n1{}, n3{});
        std::cout << "The distance between Node 1 and Node 3 is " << dist << ".\n";
    } {
        // Example 2
        // -------------------------------------------------------------------------
        // Create Nodes with IDs 1, 2, 3, and 4.
        using n1 = ctgl::Node<1>;
        using n2 = ctgl::Node<2>;
        using n3 = ctgl::Node<3>;
        using n4 = ctgl::Node<4>;
        using nodes = ctgl::List<n1, n2, n3, n4>;

        // Create Edges that form multiple circuits across the Nodes.
        //             .----------1----------v
        // (1) --1--> (2) --2--> (3) --1--> (4) --.
        // ^ ^---------3---------' ^---4-----'    |
        // '----------------3---------------------'
        using e12 = ctgl::Edge<n1, n2, 1>;
        using e23 = ctgl::Edge<n2, n3, 2>;
        using e24 = ctgl::Edge<n2, n4, 1>;
        using e31 = ctgl::Edge<n3, n1, 3>;
        using e34 = ctgl::Edge<n3, n4, 1>;
        using e41 = ctgl::Edge<n4, n1, 3>;
        using e43 = ctgl::Edge<n4, n1, 4>;
        using edges = ctgl::List<e12, e23, e24, e31, e34, e41, e43>;

        // Compose the Nodes and Edges to form a Graph.
        using graph = ctgl::Graph<nodes, edges>;

        // Find the length of the solution to the TSP (i.e., 1 + 2 + 1 + 3 = 7).
        constexpr auto route = ctgl::algorithm::findShortestRoute(graph{}, n1{}, nodes{});
        constexpr int length = ctgl::path::length(route);
        std::cout << "The solution to the TSP has length " << length << ".\n";
    }

    std::cout << "\nDone.\n";
}
