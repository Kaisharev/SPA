#include <cassert>
#include <iostream>

#include "../include/algorithms/unionfind.hpp"

void test_initial_state () {
    UnionFind uf (5);

    // Na početku svaki element je u svojoj komponenti
    assert (!uf.isConnected (0, 1));
    assert (!uf.isConnected (1, 2));
    assert (uf.isConnected (0, 0));  // Sam sa sobom

    std::cout << "[PASS] test_initial_state\n";
}

void test_unite_and_find () {
    UnionFind uf (5);

    uf.unite (0, 1);
    assert (uf.isConnected (0, 1));
    assert (!uf.isConnected (0, 2));

    uf.unite (1, 2);
    assert (uf.isConnected (0, 2));  // Tranzitivno:  0-1-2

    std::cout << "[PASS] test_unite_and_find\n";
}

void test_multiple_components () {
    UnionFind uf (6);

    // Komponenta 1: {0, 1, 2}
    uf.unite (0, 1);
    uf.unite (1, 2);

    // Komponenta 2: {3, 4}
    uf.unite (3, 4);

    // 5 ostaje sam

    assert (uf.isConnected (0, 2));
    assert (uf.isConnected (3, 4));
    assert (!uf.isConnected (0, 3));
    assert (!uf.isConnected (2, 5));

    std::cout << "[PASS] test_multiple_components\n";
}

int main () {
    std::cout << "=== UnionFind Tests ===\n";

    test_initial_state ();
    test_unite_and_find ();
    test_multiple_components ();

    std::cout << "All UnionFind tests passed!\n";
    return 0;
}