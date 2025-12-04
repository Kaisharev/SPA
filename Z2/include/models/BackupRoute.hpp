#pragma once
#include <vector>

struct BackupRoute {
        int nodeId;
        std::vector<int> path;
        int distance;
};