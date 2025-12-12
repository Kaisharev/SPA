#pragma once
#include <stdexcept>

#include "../interfaces/IGraph.hpp"
class Graph : public IGraph {
    public:
        Graph () = default;
        explicit Graph (std::vector<std::vector<int>>&& matrix);
        Graph::Graph (int numNodes) : adjMatrix_ (numNodes, std::vector<int> (numNodes, 0)), edgeCount_ (0) {}

        const std::vector<std::vector<int>>& GetAdjMatrix () const {
            return adjMatrix_;
        }
        std::vector<std::vector<int>>& GetAdjMatrix () {
            return adjMatrix_;
        }
        int GetNodeCount () const {
            return adjMatrix_.size ();
        }
        std::vector<Edge> GetAllEdges () const override;
        void RemoveEdge (int u, int v) override;
        void RestoreEdge (int u, int v, int weight) override;

    private:
        std::vector<std::vector<int>> adjMatrix_;
        int edgeCount_ = 0;
        bool IsValidNode (int node) const noexcept;
        void DFS (int node, std::vector<bool>& visited) const;
        void RecomputeEdgeCount ();
};