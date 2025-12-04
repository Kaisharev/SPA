#pragma once
#include <string>
#include <vector>
class IGraphLoader {
    public:
        virtual std::vector<std::vector<int>> LoadAdjancencyMatrix (const std::filesystem::path& location) = 0;
        virtual ~IGraphLoader () {}
};