#pragma once

#include <vector>

#include "../models/Edge.hpp"

class ITree {
    public:
        virtual ~ITree () = default;

        virtual int GetRoot () const = 0;
        virtual int GetNodeCount () const = 0;
        virtual std::vector<Edge> GetEdges () const = 0;
        virtual int GetTotalWeight () const = 0;

        virtual std::vector<int> GetChildren (int node) const = 0;
        virtual int GetParent (int node) const = 0;
        virtual int GetDepth (int node) const = 0;

        virtual bool IsRoot (int node) const = 0;
        virtual bool IsLeaf (int node) const = 0;
        virtual bool Contains (int node) const = 0;
};