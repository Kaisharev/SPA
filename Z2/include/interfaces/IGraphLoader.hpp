#pragma once
#include <filesystem>
#include <string>
#include <vector>
class IGraphLoader {
    public:
        virtual std::vector<std::vector<int>> LoadAdjacencyMatrix (const std::filesystem::path& path) = 0;
        virtual ~IGraphLoader () {}
};