#pragma once
#include <string>
#include <vector>

#include "../models/Bottleneck.hpp"
#include "../models/EdgeLoad.hpp"
#include "../models/Sensor.hpp"
#include "ITree.hpp"

class ILoadCalculator {
    public:
        virtual ~ILoadCalculator () = default;

        virtual void Calculate (const ITree& tree, const std::vector<Sensor>& sensors) = 0;

        virtual std::vector<EdgeLoad> GetEdgeLoads () const = 0;

        virtual Bottleneck GetBottleneck () const = 0;

        virtual double GetSubtreeLoad (int node) const = 0;

        virtual int GetSubtreesensor_count (int node) const = 0;

        virtual std::string FormatEdgeLoads () const = 0;
        virtual std::string FormatBottleneck () const = 0;
};