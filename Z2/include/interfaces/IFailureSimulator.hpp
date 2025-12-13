#pragma once
#include <string>
#include <vector>

#include "../models/FailureSimulatorResults.hpp"
#include "IGraph.hpp"
#include "ITree.hpp"

class IFailureSimulator {
    public:
        virtual ~IFailureSimulator () = default;

        virtual FailureSimulationResult SimulateFailure (IGraph& graph, const ITree& tree, int failedChild, int root) = 0;

        virtual std::vector<int> GetSubtreeNodes (const ITree& tree, int subtreeRoot) = 0;

        virtual std::string FormatSimulationResult (const FailureSimulationResult& result) const = 0;
};