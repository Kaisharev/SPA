#pragma once
#include <memory>

#include "../interfaces/IFailureSimulator.hpp"
#include "../interfaces/IShortestPathFinder.hpp"

class FailureSimulator : public IFailureSimulator {
    public:
        explicit FailureSimulator (std::shared_ptr<IShortestPathFinder> pathFinder);

        FailureSimulationResult SimulateFailure (IGraph& graph, const ITree& tree, int failedChild, int root) override;

        std::vector<int> GetSubtreeNodes (const ITree& tree, int subtreeRoot) override;

        std::string FormatSimulationResult (const FailureSimulationResult& result) const override;

    private:
        std::shared_ptr<IShortestPathFinder> path_finder_;
        void collectSubtreeNodes (const ITree& tree, int current, std::vector<int>& nodes);
};