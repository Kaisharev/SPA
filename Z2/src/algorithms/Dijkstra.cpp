#include "../../include/algorithms/Dijkstra.hpp"

#include <algorithm>
#include <limits>
#include <queue>

dijkstra_result Dijkstra::FindShortestPaths (const IGraph& graph, int source) {
    int n = graph.GetNodeCount ();

    dijkstra_result result (n);
    result.distances[source] = 0;

    using PII = std::pair<int, int>;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
    pq.push ({0, source});

    while (!pq.empty ()) {
        auto [dist, u] = pq.top ();
        pq.pop ();

        if (dist > result.distances[u]) continue;

        const auto& adjMatrix = graph.GetAdjMatrix ();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0) {
                int new_distance = result.distances[u] + adjMatrix[u][v];
                if (new_distance < result.distances[v]) {
                    result.distances[v] = new_distance;
                    result.previous[v] = u;
                    pq.push ({new_distance, v});
                }
            }
        }
    }

    return result;
}

std::vector<int> Dijkstra::ReconstructPath (const dijkstra_result& result, int source, int target) {
    std::vector<int> path;
    const int INF = std::numeric_limits<int>::max ();

    if (result.distances[target] == INF) {
        return path;
    }

    for (int at = target; at != -1; at = result.previous[at]) {
        path.push_back (at);
    }

    std::reverse (path.begin (), path.end ());

    if (path.empty () || path[0] != source) {
        return {};
    }

    return path;
}

PathResult Dijkstra::FindPath (const IGraph& graph, int source, int target) {
    auto dijkstra_result = FindShortestPaths (graph, source);
    auto path = ReconstructPath (dijkstra_result, source, target);

    return PathResult (target, path, dijkstra_result.distances[target]);
}