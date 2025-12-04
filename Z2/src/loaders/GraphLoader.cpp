#include "../../include/loaders/GraphLoader.hpp"
#include <fstream>
#include <sstream>

std::vector<std::vector<int>> GraphLoader::LoadAdjacencyMatrix (const std::filesystem::path& path) {
    std::filesystem::path file_path = path / "graph.txt";
    if (!std::filesystem::exists (file_path)) {
        throw std::runtime_error ("Fajl ne postoji: " + file_path.string ());
    }
    std::ifstream entry_input (file_path);
    if (!entry_input.is_open ()) {
        throw std::runtime_error ("Ne mogu otvoriti fajl: " + file_path.string ());
    }
    std::string line;
    std::vector<std::vector<int>> matrix;

    while (std::getline (entry_input, line)) {
        std::vector<int> row;
        std::stringstream ss (line);
        int value;
        while (ss >> value) {
            row.push_back (value);
        }
        if (!row.empty ()) {
            matrix.push_back (row);
        }
    }

    entry_input.close ();
    return matrix;
}