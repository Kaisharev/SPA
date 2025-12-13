#pragma once
#include <vector>

#include "../models/Edge.hpp"

class IGraph {
    public:
        virtual std::vector<Edge> GetAllEdges () const = 0;
        virtual void RemoveEdge (int u, int v) = 0;
        virtual void RestoreEdge (int u, int v, int weight) = 0;
        virtual ~IGraph () = default;
};