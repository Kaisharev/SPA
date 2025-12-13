#pragma once
#include <limits>
#include <string>
#include <vector>

struct PathResult {
        int node;
        std::vector<int> path;
        int distance;
        bool is_reachable;

        PathResult () : node (-1), distance (std::numeric_limits<int>::max ()), is_reachable (false) {}

        PathResult (int n, const std::vector<int>& p, int d)
            : node (n), path (p), distance (d), is_reachable (d != std::numeric_limits<int>::max ()) {}
};
