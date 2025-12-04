#pragma once
#include <vector>

struct BackupRoute {
        int nodeId_;
        std::vector<int> path_;
        int distance_;
};