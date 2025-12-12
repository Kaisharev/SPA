#pragma once

#include <vector>

#include "../interfaces/IMSTBuilder.hpp"
#include "../models/Edge.hpp"
class KruskalMST : public IMSTBuilder {
    public:
        void BuildMST (const std::vector<std::vector<int>>& graph) override;
        std::vector<Edge> GetMSTEdges () const override;
        int GetTotalWeight () const override;

    private:
        std::vector<Edge> mst_edges_;
        int total_weight_ = 0;
};
