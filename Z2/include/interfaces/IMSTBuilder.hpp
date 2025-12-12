#pragma once
#include <vector>

#include "../models/Edge.hpp"

class IMSTBuilder {
    public:
        virtual void BuildMST (const std::vector<std::vector<int>>& graph) = 0;
        virtual std::vector<Edge> GetMSTEdges () const = 0;
        virtual int GetTotalWeight () const = 0;
        virtual ~IMSTBuilder () {}
};