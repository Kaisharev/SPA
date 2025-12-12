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
void Graph::RecomputeEdgeCount () {
    int adj_matrix_size = adjMatrix_.size ();

    for (int i = 0; i < adj_matrix_size; i++) {
        for (int j = 0; j < adj_matrix_size; j++) {
            if (adjMatrix_[i][j] > 0) edgeCount_++;
        }
    }
}
bool Graph::IsValidNode (int node) const {
    return node >= 0 && node < static_cast<int> (adjMatrix_.size ());
}
void Graph::DFS (int node, std::vector<bool>& visited) const {
    visited[node] = true;
    for (int i = 0; i < static_cast<int> (adjMatrix_.size ()); i++) {
        if (adjMatrix_[node][i] > 0 && !visited[i]) {
            DFS (i, visited);
        }
    }
}

std::vector<Edge> Graph::GetAllEdges () const {
    std::vector<Edge> edges;
    for (int i = 0; i < static_cast<int> (adjMatrix_.size ()); i++) {
        for (int j = 0; j < static_cast<int> (adjMatrix_[i].size ()); j++) {
            if (adjMatrix_[i][j] > 0) {
                edges.push_back ({i, j, adjMatrix_[i][j]});
            }
        }
    }
    return edges;
}

void Graph::RemoveEdge (int u, int v) {
    if (u >= static_cast<int> (adjMatrix_.size ()) || v >= static_cast<int> (adjMatrix_.size ()))
        throw std::out_of_range ("Data grana nije u opsegu!");
    adjMatrix_[u][v] = 0;
    edgeCount_--;
}

void Graph::RestoreEdge (int u, int v, int weight) {
    if (u >= static_cast<int> (adjMatrix_.size ()) || v >= static_cast<int> (adjMatrix_.size ()))
        throw std::out_of_range ("Data grana nije u opsegu!");
    adjMatrix_[u][v] = weight;
    edgeCount_++;
}