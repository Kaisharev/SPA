#pragma once
#include <vector>

#include "../interfaces/IUnionFind.hpp"
class UnionFind : public IUnionFind {
    private:
        std::vector<int> parent;
        std::vector<int> rank;

    public:
        UnionFind (int n);
        int find (int x) override;
        bool unite (int x, int y) override;
        bool isConnected (int x, int y) override;
};