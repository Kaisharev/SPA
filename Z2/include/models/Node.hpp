#pragma once
#include <vector>

struct Node {
        int parent;
        std::vector<int> children;
        double subtree_load;
        int subtree_size;
};