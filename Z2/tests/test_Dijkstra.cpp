#include <cassert>
#include <iostream>
#include <memory>

#include "../include/algorithms/Dijkstra.hpp"
#include "../include/graph/Graph.hpp"

void test_simple_path () {
    // 0 --2-- 1 --3-- 2
    std::vector<std::vector<int>> matrix = {{0, 2, 0}, {2, 0, 3}, {0, 3, 0}};

    Graph graph (std::move (matrix));
    Dijkstra dijkstra;

    auto result = dijkstra.FindPath (graph, 0, 2);

    assert (result.is_reachable == true);
    assert (result.distance == 5);  // 2 + 3
    assert (result.path.size () == 3);
    assert (result.path[0] == 0);
    assert (result.path[1] == 1);
    assert (result.path[2] == 2);

    std::cout << "[PASS] test_simple_path\n";
}

void test_shortest_path_choice () {
    std::vector<std::vector<int>> matrix = {{0, 2, 6}, {2, 0, 5}, {6, 5, 0}};

    Graph graph (std::move (matrix));
    Dijkstra dijkstra;

    auto result = dijkstra.FindPath (graph, 0, 2);

    assert (result.distance == 6);  // Direktna grana, ne 2+5=7

    std::cout << "[PASS] test_shortest_path_choice\n";
}

void test_unreachable_node () {
    // 0 -- 1    2 (odvojen čvor)
    std::vector<std::vector<int>> matrix = {{0, 1, 0}, {1, 0, 0}, {0, 0, 0}};

    Graph graph (std::move (matrix));
    Dijkstra dijkstra;

    auto result = dijkstra.FindPath (graph, 0, 2);

    assert (result.is_reachable == false);

    std::cout << "[PASS] test_unreachable_node\n";
}

void test_same_source_target () {
    std::vector<std::vector<int>> matrix = {{0, 1}, {1, 0}};

    Graph graph (std::move (matrix));
    Dijkstra dijkstra;

    auto result = dijkstra.FindPath (graph, 0, 0);

    assert (result.is_reachable == true);
    assert (result.distance == 0);

    std::cout << "[PASS] test_same_source_target\n";
}

int main () {
    std::cout << "=== Dijkstra Tests ===\n";

    test_simple_path ();
    test_shortest_path_choice ();
    test_unreachable_node ();
    test_same_source_target ();

    std::cout << "All Dijkstra tests passed!\n";
    return 0;
}