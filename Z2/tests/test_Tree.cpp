#include <cassert>
#include <iostream>

#include "../include/tree/TreeBuilder.hpp"

void test_tree_structure () {
    std::vector<Edge> edges = {{0, 1, 1}, {0, 2, 1}, {0, 3, 1}, {1, 4, 1}};

    TreeBuilder builder;
    builder.SetRoot (0);
    builder.AddEdges (edges);
    auto tree = builder.Build ();

    assert (tree->GetRoot () == 0);
    assert (tree->GetNodeCount () == 5);
    assert (tree->IsRoot (0) == true);
    assert (tree->IsRoot (1) == false);

    std::cout << "[PASS] test_tree_structure\n";
}

void test_parent_child_relations () {
    std::vector<Edge> edges = {{0, 1, 1}, {1, 2, 1}};

    TreeBuilder builder;
    builder.SetRoot (0);
    builder.AddEdges (edges);
    auto tree = builder.Build ();

    assert (tree->GetParent (0) == -1);  // Root nema roditelja
    assert (tree->GetParent (1) == 0);
    assert (tree->GetParent (2) == 1);

    auto children_0 = tree->GetChildren (0);
    assert (children_0.size () == 1);
    assert (children_0[0] == 1);

    std::cout << "[PASS] test_parent_child_relations\n";
}

void test_depth () {
    std::vector<Edge> edges = {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}};

    TreeBuilder builder;
    builder.SetRoot (0);
    builder.AddEdges (edges);
    auto tree = builder.Build ();

    assert (tree->GetDepth (0) == 0);
    assert (tree->GetDepth (1) == 1);
    assert (tree->GetDepth (2) == 2);
    assert (tree->GetDepth (3) == 3);

    std::cout << "[PASS] test_depth\n";
}

void test_leaf_detection () {
    std::vector<Edge> edges = {{0, 1, 1}, {0, 2, 1}};

    TreeBuilder builder;
    builder.SetRoot (0);
    builder.AddEdges (edges);
    auto tree = builder.Build ();

    assert (tree->IsLeaf (0) == false);
    assert (tree->IsLeaf (1) == true);
    assert (tree->IsLeaf (2) == true);

    std::cout << "[PASS] test_leaf_detection\n";
}

int main () {
    std::cout << "=== Tree Tests ===\n";

    test_tree_structure ();
    test_parent_child_relations ();
    test_depth ();
    test_leaf_detection ();

    std::cout << "All Tree tests passed!\n";
    return 0;
}