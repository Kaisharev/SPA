#pragma once
#include <vector>

struct Node {
        int parent_;
        std::vector<int> children_;
        double subtree_load_;
        int subtree_size_;
};