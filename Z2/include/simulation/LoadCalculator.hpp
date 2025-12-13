#pragma once
#include <unordered_map>
#include <vector>

#include "../interfaces/ILoadCalculator.hpp"
#include "../interfaces/ITree.hpp"

class LoadCalculator : public ILoadCalculator {
    public:
        LoadCalculator () = default;

        void Calculate (const ITree& tree, const std::vector<Sensor>& sensors) override;

        std::vector<EdgeLoad> GetEdgeLoads () const override;
        Bottleneck GetBottleneck () const override;
        double GetSubtreeLoad (int node) const override;
        int GetSubtreesensor_count (int node) const override;

        std::string FormatEdgeLoads () const override;
        std::string FormatBottleneck () const override;

    private:
        std::vector<EdgeLoad> edge_loads_;
        Bottleneck bottleneck_;

        std::unordered_map<int, double> subtree_load_;
        std::unordered_map<int, int> subtreesensor_count_;
        std::unordered_map<int, double> own_load_;  // Zamalo nisam mapu krstio kao eigen_load_ kao omaž sopstvenim vrijednostima :)

        void calculateDFS (const ITree& tree, int current);
        void findBottleneck ();
};