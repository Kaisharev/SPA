#include "../../include/loaders/GraphLoader.hpp"

std::vector<std::vector<int>> LoadAdjancencyMatrix (const std::filesystem::path& location) {
    std::filesystem::path file_path = location / "graph.txt";
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
            std::copy (row.begin (), row.end (), std::ostream_iterator<int> (std::cout, " "));
            std::cout << std::endl;
        }
    }

    entry_input.close ();
    return matrix;
}