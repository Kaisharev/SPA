#include "../../include/simulation/FailureSimulator.hpp"

#include <algorithm>
#include <limits>
#include <sstream>

#include "../../include/interfaces/IGraph.hpp"
#include "../../include/interfaces/ITree.hpp"

FailureSimulator::FailureSimulator (std::shared_ptr<IShortestPathFinder> pathFinder) : path_finder_ (std::move (pathFinder)) {}

FailureSimulationResult FailureSimulator::SimulateFailure (IGraph& graph, const ITree& tree, int failedChild, int root) {
    FailureSimulationResult result;
    result.failed_edge_from = failedChild;
    result.failed_edge_to = tree.GetParent (failedChild);

    if (result.failed_edge_to == -1) {
        result.success = false;
        return result;
    }

    result.affected_nodes = GetSubtreeNodes (tree, failedChild);

    const auto& adjMatrix = graph.GetAdjMatrix ();
    int edgeWeight = adjMatrix[failedChild][result.failed_edge_to];

    graph.RemoveEdge (failedChild, result.failed_edge_to);

    for (int node : result.affected_nodes) {
        PathResult pathResult = path_finder_->FindPath (graph, root, node);

        if (!pathResult.path.empty ()) {
            std::reverse (pathResult.path.begin (), pathResult.path.end ());
        }

        result.backup_routes.push_back (pathResult);
    }

    graph.RestoreEdge (failedChild, result.failed_edge_to, edgeWeight);

    result.success = true;
    return result;
}

std::vector<int> FailureSimulator::GetSubtreeNodes (const ITree& tree, int subtreeRoot) {
    std::vector<int> nodes;
    collectSubtreeNodes (tree, subtreeRoot, nodes);
    return nodes;
}

void FailureSimulator::collectSubtreeNodes (const ITree& tree, int current, std::vector<int>& nodes) {
    nodes.push_back (current);

    for (int child : tree.GetChildren (current)) {
        collectSubtreeNodes (tree, child, nodes);
    }
}

std::string FailureSimulator::FormatSimulationResult (const FailureSimulationResult& result) const {
    std::ostringstream ss;

    ss << "[SIMULACIJA KVARA] Grana " << result.failed_edge_from << " -> " << result.failed_edge_to << " je nedostupna.\n";

    ss << "REZERVNE RUTE (u originalnom grafu, Dijkstra):\n";

    for (const auto& route : result.backup_routes) {
        ss << "Cvor:  " << route.node << "\n";

        if (route.is_reachable && !route.path.empty ()) {
            ss << "  REZERVNA RUTA: ";
            for (size_t i = 0; i < route.path.size (); ++i) {
                ss << route.path[i];
                if (i < route.path.size () - 1) ss << " -> ";
            }
            ss << "\n";
            ss << "  Udaljenost: " << route.distance << "\n";
        } else {
            ss << "  NEMA ALTERNATIVNE RUTE!\n";
        }
    }

    return ss.str ();
}