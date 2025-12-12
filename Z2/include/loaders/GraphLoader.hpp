#pragma once

#include "../interfaces/IGraphLoader.hpp"

class GraphLoader : public IGraphLoader {
    public:
        GraphLoader () = default;
        ~GraphLoader () override = default;
        std::vector<std::vector<int>> LoadAdjacencyMatrix (const std::filesystem::path& path) override;
};