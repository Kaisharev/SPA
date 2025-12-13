#include <cassert>
#include <iostream>

#include "../include/algorithms/KruskalMST.hpp"

void test_simple_mst () {
    std::vector<std::vector<int>> matrix = {{0, 1, 3}, {1, 0, 2}, {3, 2, 0}};

    KruskalMST kruskal;
    kruskal.BuildMST (matrix);

    // MST treba imati 2 grane (n-1)
    assert (kruskal.GetMSTEdges ().size () == 2);

    // Minimalna težina:  1 + 2 = 3 (grane 0-1 i 1-2)
    assert (kruskal.GetTotalWeight () == 3);

    std::cout << "[PASS] test_simple_mst\n";
}

void test_linear_graph () {
    std::vector<std::vector<int>> matrix = {{0, 5, 0, 0}, {5, 0, 3, 0}, {0, 3, 0, 7}, {0, 0, 7, 0}};

    KruskalMST kruskal;
    kruskal.BuildMST (matrix);

    assert (kruskal.GetMSTEdges ().size () == 3);
    assert (kruskal.GetTotalWeight () == 15);

    std::cout << "[PASS] test_linear_graph\n";
}

void test_disconnected_graph () {
    // Dva odvojena čvora
    std::vector<std::vector<int>> matrix = {{0, 0}, {0, 0}};

    KruskalMST kruskal;
    kruskal.BuildMST (matrix);

    assert (kruskal.GetMSTEdges ().size () == 0);
    assert (kruskal.GetTotalWeight () == 0);

    std::cout << "[PASS] test_disconnected_graph\n";
}

int main () {
    std::cout << "=== KruskalMST Tests ===\n";

    test_simple_mst ();
    test_linear_graph ();
    test_disconnected_graph ();

    std::cout << "All KruskalMST tests passed!\n";
    return 0;
}