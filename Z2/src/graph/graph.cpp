#include "../../include/graph/Graph.hpp"
Graph::Graph (std::vector<std::vector<int>>&& matrix) {
    const size_t n = matrix.size ();
    for (const auto& row : matrix) {
        if (row.size () != n) {
            throw std::invalid_argument ("Matrica mora biti kvadratna");
        }
    }
    adjMatrix_ = std::move (matrix);
    RecomputeEdgeCount ();
}

Graph::Graph (int numNodes) : adjMatrix_ (numNodes, std::vector<int> (numNodes, 0)), edgeCount_ (0) {}

void Graph::RecomputeEdgeCount () {
    int n = static_cast<int> (adjMatrix_.size ());
    edgeCount_ = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix_[i][j] > 0) edgeCount_++;
        }
    }
}
bool Graph::IsValidNode (int node) const noexcept {
    return node >= 0 && node < static_cast<int> (adjMatrix_.size ());
}

std::vector<Edge> Graph::GetAllEdges () const {
    std::vector<Edge> edges;
    int n = static_cast<int> (adjMatrix_.size ());

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix_[i][j] > 0) {
                edges.push_back ({i, j, adjMatrix_[i][j]});
            }
        }
    }
    return edges;
}

void Graph::RemoveEdge (int u, int v) {
    if (!IsValidNode (u) || !IsValidNode (v)) throw std::out_of_range ("Grana nije u opsegu!");
    if (adjMatrix_[u][v] > 0) {
        adjMatrix_[u][v] = 0;
        adjMatrix_[v][u] = 0;
        RecomputeEdgeCount ();
    }
}

void Graph::RestoreEdge (int u, int v, int weight) {
    if (!IsValidNode (u) || !IsValidNode (v)) throw std::out_of_range ("Grana nije u opsegu!");
    if (weight <= 0) return;
    if (adjMatrix_[u][v] == 0) {
        adjMatrix_[u][v] = weight;
        adjMatrix_[v][u] = weight;
        RecomputeEdgeCount ();
    }
}