#pragma once
#include "../interfaces/IUnionFind.hpp"

class UnionFind : public IUnionFind {
        int find (int x) override;
        bool unite (int x, int y) override;
        bool isConnected (int x, int y) override;
};