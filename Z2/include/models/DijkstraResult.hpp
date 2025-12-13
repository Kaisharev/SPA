#pragma once
#include <numeric>
#include <vector>
struct dijkstra_result {
        std::vector<int> distances;
        std::vector<int> previous;

        dijkstra_result () = default;
        dijkstra_result (int n) : distances (n, std::numeric_limits<int>::max ()), previous (n, -1) {}
};