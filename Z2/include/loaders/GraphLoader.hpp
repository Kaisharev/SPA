#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "../interfaces/IGraphLoader.hpp"

class GraphLoader : public IGraphLoader {
    public:
        GraphLoader () = default;
        ~GraphLoader () override = default;
        std::vector<std::vector<int>> LoadAdjancencyMatrix (const std::filesystem::path& location);
};