#include "../../include/algorithms/KruskalMST.hpp"

#include <algorithm>

#include "../../include/algorithms/UnionFind.hpp"

void KruskalMST::BuildMST (const std::vector<std::vector<int>>& graph) {
    int n = graph.size ();
    std::vector<Edge> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != 0) {
                edges.push_back ({i, j, graph[i][j]});
            }
        }
    }

    std::sort (edges.begin (), edges.end (), [] (const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    UnionFind uf (n);
    mst_edges_.clear ();
    total_weight_ = 0;

    for (const auto& e : edges) {
        if (uf.unite (e.to, e.from)) {
            mst_edges_.push_back (e);
            total_weight_ += e.weight;
            if (mst_edges_.size () == n - 1) break;
        }
    }
}