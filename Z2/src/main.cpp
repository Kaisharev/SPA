#ifdef _WIN32
#    include <windows.h>
#endif

#include <iostream>
#include <filesystem>

#include "../include/algorithms/KruskalMST.hpp"
#include "../include/loaders/GraphLoader.hpp"
#include "../include/loaders/SensorLoader.hpp"
#include "../include/tree/Tree.hpp"
#include "../include/tree/TreeBuilder.hpp"
std::filesystem::path FindDataFolder () {
    std::vector<std::filesystem::path> possiblePaths = {
        "./data",        // ako se pokreće iz root projekta
        "../data",       // ako se pokreće iz build/
        "../../data",    // ako se pokreće iz build/Debug/
        "../../../data"  // ako se pokreće iz build/Debug/x64/
    };

    for (const auto& path : possiblePaths) {
        if (std::filesystem::exists (path) && std::filesystem::is_directory (path)) {
            return std::filesystem::absolute (path);
        }
    }

    throw std::runtime_error ("Data folder not found!");
}

void PrintTreeVisual (const ITree* tree, int node, const std::string& prefix = "", bool isLast = true) {
    std::cout << prefix;
    std::cout << (isLast ? "└── " : "├── ");
    std::cout << node << " (dubina=" << tree->GetDepth (node) << ")";

    if (tree->IsRoot (node)) {
        std::cout << " [korjen]";
    }
    if (tree->IsLeaf (node)) {
        std::cout << " [listić]";
    }
    std::cout << std::endl;

    auto children = tree->GetChildren (node);
    for (size_t i = 0; i < children.size (); i++) {
        bool last_child = (i == children.size () - 1);
        PrintTreeVisual (tree, children[i], prefix + (isLast ? "    " : "│   "), last_child);
    }
}
int main (int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP (CP_UTF8);
    SetConsoleCP (CP_UTF8);
#endif
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <test_folder_name>" << std::endl;
        return 1;
    }

    try {
        std::filesystem::path dataFolder = FindDataFolder ();
        std::filesystem::path location = dataFolder / argv[1] / "graph.txt";
        std::filesystem::path locationS = dataFolder / argv[1] / "sensors.csv";

        std::cout << "Using data folder: " << dataFolder << std::endl;
        std::cout << "Graph file: " << location << std::endl;
        std::cout << "Sensors file: " << locationS << std::endl;

        GraphLoader loader;
        SensorLoader sensorLoader;
        KruskalMST kruskal;

        auto matrix = loader.LoadAdjacencyMatrix (location);
        auto sensor = sensorLoader.LoadSensors (locationS);

        std::cout << "Loaded matrix with " << matrix.size () << " rows" << std::endl;
        std::cout << "Loaded sensors with " << sensor.size () << " rows" << std::endl;
        kruskal.BuildMST (matrix);
        std::vector<Edge> mst_edges = kruskal.GetMSTEdges ();
        std::cout << "Total weight " << kruskal.GetTotalWeight () << " weight" << std::endl;
        for (int i = 0; i < mst_edges.size (); i++) {
            std::cout << mst_edges[i].from << "->" << mst_edges[i].to << ":" << mst_edges[i].weight << std::endl;
        }
        for (int i = 0; i < sensor.size (); i++) {
            std::cout << sensor[i].id << ":" << sensor[i].sensor_type << " " << sensor[i].criticality << " " << sensor[i].data_output
                      << std::endl;
        }

        TreeBuilder builder;
        builder.SetRoot (std::atoi (argv[2]));
        builder.AddEdges (kruskal.GetMSTEdges ());
        auto tree = builder.Build ();

        std::cout << "Root: " << tree->GetRoot () << std::endl;
        std::cout << "Node count: " << tree->GetNodeCount () << std::endl;
        std::cout << "Total weight: " << tree->GetTotalWeight () << std::endl;

        PrintTreeVisual (tree.get (), tree->GetRoot ());

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what () << std::endl;
        return 1;
    }

    return 0;
}