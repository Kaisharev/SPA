#include "../../include/algorithms/UnionFind.hpp"

UnionFind::UnionFind (int n) : parent (n), rank (n, 0) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int UnionFind::find (int x) {
    if (parent[x] != x) {
        parent[x] = find (parent[x]);
    }
    return parent[x];
}

bool UnionFind::unite (int x, int y) {
    int px = find (x), py = find (y);
    if (px == py) return false;

    if (rank[px] < rank[py]) std::swap (px, py);
    parent[py] = px;
    if (rank[px] == rank[py]) rank[px]++;
    return true;
}

bool UnionFind::isConnected (int x, int y) {
    return find (x) == find (y);
}