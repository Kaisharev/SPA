#ifdef _WIN32
#    include <windows.h>
#endif

#include <iostream>

#include "../include/loaders/GraphLoader.hpp"

int main () {
#ifdef _WIN32
    SetConsoleOutputCP (CP_UTF8);
    SetConsoleCP (CP_UTF8);
#endif

    std::filesystem::path location = L"../../data/test1";
    GraphLoader loader;

    try {
        auto matrix = loader.LoadAdjancencyMatrix (location);
        std::cout << "Loaded matrix with " << matrix.size () << " rows" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what () << std::endl;
        return 1;
    }

    return 0;
}