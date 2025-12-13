#pragma once
#include <vector>

#include "PathResult.hpp"

struct FailureSimulationResult {
        int failed_edge_from;
        int failed_edge_to;
        std::vector<int> affected_nodes;
        std::vector<PathResult> backup_routes;
        bool success;

        FailureSimulationResult () : failed_edge_from (-1), failed_edge_to (-1), success (false) {}
};