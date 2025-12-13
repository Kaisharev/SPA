#pragma once

#include <memory>
#include <vector>

#include "../models/Edge.hpp"
#include "ITree.hpp"

class ITreeBuilder {
    public:
        virtual ~ITreeBuilder () = default;

        virtual void SetRoot (int root) = 0;
        virtual void AddEdge (const Edge& edge) = 0;
        virtual void AddEdges (const std::vector<Edge>& edges) = 0;

        virtual std::unique_ptr<ITree> Build () = 0;

        virtual void Reset () = 0;
};