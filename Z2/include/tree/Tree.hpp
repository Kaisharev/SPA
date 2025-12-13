#pragma once

#include <queue>
#include <unordered_map>
#include <vector>

#include "../interfaces/ITree.hpp"

class Tree : public ITree {
    public:
        Tree (int root, const std::vector<Edge>& edges);

        int GetRoot () const override {
            return root_;
        }
        int GetNodeCount () const override {
            return nodeCount_;
        }
        std::vector<Edge> GetEdges () const override {
            return edges_;
        }
        int GetTotalWeight () const override {
            return totalWeight_;
        }

        std::vector<int> GetChildren (int node) const override;
        int GetParent (int node) const override;
        int GetDepth (int node) const override;

        bool IsRoot (int node) const override;
        bool IsLeaf (int node) const override;
        bool Contains (int node) const override;

    private:
        int root_;
        int nodeCount_;
        int totalWeight_;
        std::vector<Edge> edges_;
        std::unordered_map<int, std::vector<int>> children_;
        std::unordered_map<int, int> parent_;
        std::unordered_map<int, int> depth_;

        void BuildTree ();
};