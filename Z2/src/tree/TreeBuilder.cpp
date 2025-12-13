#include "../../include/tree/TreeBuilder.hpp"

void TreeBuilder::SetRoot(int root) {
    root_ = root;
}

void TreeBuilder::AddEdge(const Edge& edge) {
    edges_.push_back(edge);
}

void TreeBuilder::AddEdges(const std::vector<Edge>& edges) {
    edges_.insert(edges_.end(), edges.begin(), edges.end());
}

std::unique_ptr<ITree> TreeBuilder::Build() {
    return std::make_unique<Tree>(root_, edges_);
}

void TreeBuilder::Reset() {
    root_ = 0;
    edges_.clear();
}