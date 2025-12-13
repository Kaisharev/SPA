#pragma once

#include <memory>
#include <vector>

#include "../interfaces/ITreeBuilder.hpp"
#include "../tree/Tree.hpp"

class TreeBuilder : public ITreeBuilder {
public:
    void SetRoot(int root) override;
    void AddEdge(const Edge& edge) override;
    void AddEdges(const std::vector<Edge>& edges) override;
    std::unique_ptr<ITree> Build() override;
    void Reset() override;

private:
    int root_ = 0;
    std::vector<Edge> edges_;
};