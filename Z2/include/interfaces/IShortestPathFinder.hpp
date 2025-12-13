#pragma once
#include <vector>

#include "../models/DijkstraResult.hpp"
#include "../models/PathResult.hpp"
#include "IGraph.hpp"

class IShortestPathFinder {
    public:
        virtual ~IShortestPathFinder () = default;

        virtual dijkstra_result FindShortestPaths (const IGraph& graph, int source) = 0;

        virtual std::vector<int> ReconstructPath (const dijkstra_result& result, int source, int target) = 0;

        virtual PathResult FindPath (const IGraph& graph, int source, int target) = 0;
};