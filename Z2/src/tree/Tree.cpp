#include "../../include/tree/Tree.hpp"

#include <queue>
#include <unordered_set>

Tree::Tree (int root, const std::vector<Edge>& edges) : root_ (root), edges_ (edges), totalWeight_ (0), nodeCount_ (0) {
    BuildTree ();
}

void Tree::BuildTree () {
    std::unordered_map<int, std::vector<std::pair<int, int>>> adj;
    std::unordered_set<int> nodes;

    for (const auto& e : edges_) {
        adj[e.from].push_back ({e.to, e.weight});
        adj[e.to].push_back ({e.from, e.weight});
        nodes.insert (e.from);
        nodes.insert (e.to);
        totalWeight_ += e.weight;
    }
    nodes.insert (root_);
    nodeCount_ = nodes.size ();

    std::queue<int> q;
    q.push (root_);
    parent_[root_] = -1;
    depth_[root_] = 0;

    while (!q.empty ()) {
        int curr = q.front ();
        q.pop ();

        for (auto& [neighbor, weight] : adj[curr]) {
            if (parent_.find (neighbor) == parent_.end ()) {
                parent_[neighbor] = curr;
                depth_[neighbor] = depth_[curr] + 1;
                children_[curr].push_back (neighbor);
                q.push (neighbor);
            }
        }
    }
}

std::vector<int> Tree::GetChildren (int node) const {
    auto it = children_.find (node);
    if (it != children_.end ()) {
        return it->second;
    }
    return {};
}

int Tree::GetParent (int node) const {
    auto it = parent_.find (node);
    if (it != parent_.end ()) {
        return it->second;
    }
    return -1;
}

int Tree::GetDepth (int node) const {
    auto it = depth_.find (node);
    if (it != depth_.end ()) {
        return it->second;
    }
    return -1;
}

bool Tree::IsRoot (int node) const {
    return node == root_;
}

bool Tree::IsLeaf (int node) const {
    auto it = children_.find (node);
    return it == children_.end () || it->second.empty ();
}

bool Tree::Contains (int node) const {
    return parent_.find (node) != parent_.end ();
}