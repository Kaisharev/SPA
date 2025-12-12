#include "../../include/graph/Graph.hpp"
Graph::Graph (std::vector<std::vector<int>>&& matrix) {
    const size_t n = matrix.size ();
    for (const auto& row : matrix) {
        if (row.size () != n) {
            throw std::invalid_argument ("Matrica mora biti kvadratna");
        }
    }
    this->adjMatrix_ = std::move (matrix);
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
bool Graph::IsValidNode (int node) const {
    return node >= 0 && node < static_cast<int> (this->adjMatrix_.size ());
}
void Graph::DFS (int node, std::vector<bool>& visited) const {
    visited[node] = true;
    for (int i = 0; i < static_cast<int> (this->adjMatrix_.size ()); i++) {
        if (this->adjMatrix_[node][i] > 0 && !visited[i]) {
            DFS (i, visited);
        }
    }
}

std::vector<Edge> Graph::GetAllEdges () const {
    std::vector<Edge> edges;
    int n = static_cast<int> (adjMatrix_.size ());
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (this->adjMatrix_[i][j] > 0) {
                edges.push_back ({i, j, this->adjMatrix_[i][j]});
            }
        }
    }
    return edges;
}

void Graph::RemoveEdge (int u, int v) {
    if (u >= static_cast<int> (this->adjMatrix_.size ()) || v >= static_cast<int> (this->adjMatrix_.size ()))
        throw std::out_of_range ("Data grana nije u opsegu!");
    this->adjMatrix_[u][v] = 0;
    this->edgeCount_--;
}

void Graph::RestoreEdge (int u, int v, int weight) {
    if (u >= static_cast<int> (this->adjMatrix_.size ()) || v >= static_cast<int> (this->adjMatrix_.size ()))
        throw std::out_of_range ("Data grana nije u opsegu!");
    this->adjMatrix_[u][v] = weight;
    this->edgeCount_++;
}