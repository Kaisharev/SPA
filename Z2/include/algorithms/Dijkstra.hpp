#pragma once
#include "../interfaces/IGraph.hpp"
#include "../interfaces/IShortestPathFinder.hpp"

class Dijkstra : public IShortestPathFinder {
    public:
        Dijkstra () = default;

        dijkstra_result FindShortestPaths (const IGraph& graph, int source) override;

        std::vector<int> ReconstructPath (const dijkstra_result& result, int source, int target) override;

        PathResult FindPath (const IGraph& graph, int source, int target) override;
};