#ifdef _WIN32
#    include <windows.h>
#endif

#include <filesystem>
#include <iostream>
#include <memory>

#include "../include/algorithms/Dijkstra.hpp"
#include "../include/algorithms/KruskalMST.hpp"
#include "../include/graph/Graph.hpp"
#include "../include/loaders/GraphLoader.hpp"
#include "../include/loaders/SensorLoader.hpp"
#include "../include/reports/ReportGenerator.hpp"
#include "../include/simulation/FailureSimulator.hpp"
#include "../include/simulation/LoadCalculator.hpp"
#include "../include/tree/Tree.hpp"
#include "../include/tree/TreeBuilder.hpp"

std::filesystem::path FindDataFolder () {
    std::vector<std::filesystem::path> possiblePaths = {"./data", "../data", "../../data", "../../../data"};

    for (const auto& path : possiblePaths) {
        if (std::filesystem::exists (path) && std::filesystem::is_directory (path)) {
            return std::filesystem::absolute (path);
        }
    }

    throw std::runtime_error ("Data folder not found!");
}

int main (int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP (CP_UTF8);
    SetConsoleCP (CP_UTF8);
#endif

    if (argc < 3) {
        std::cerr << "Kako pozvati: " << argv[0] << " <test_folder_name> <root_node>" << std::endl;
        std::cerr << "Primjer: " << argv[0] << " test1 0" << std::endl;
        return 1;
    }

    try {
        std::filesystem::path dataFolder = FindDataFolder ();
        std::filesystem::path graphFile = dataFolder / argv[1] / "graph.txt";
        std::filesystem::path sensorsFile = dataFolder / argv[1] / "sensors.csv";

        std::time_t now = std::time (nullptr);
        char time_buffer[64];
        char filename_buffer[64];
        std::strftime (time_buffer, sizeof (time_buffer), "%d. %m.%Y.  %H:%M:%S", std::localtime (&now));
        std::strftime (filename_buffer, sizeof (filename_buffer), "%d_%m_%Y__%H_%M_%S", std::localtime (&now));
        std::string export_fille_name = "izvjestaj_" + std::string (filename_buffer) + ".txt";
        std::filesystem::path reportFile = dataFolder / argv[1] / export_fille_name;

        int rootNode = std::atoi (argv[2]);

        GraphLoader loader;
        SensorLoader sensorLoader;

        auto matrix = loader.LoadAdjacencyMatrix (graphFile);
        auto sensors = sensorLoader.LoadSensors (sensorsFile);

        KruskalMST kruskal;
        kruskal.BuildMST (matrix);
        std::vector<Edge> mstEdges = kruskal.GetMSTEdges ();
        int mstWeight = kruskal.GetTotalWeight ();

        TreeBuilder builder;
        builder.SetRoot (rootNode);
        builder.AddEdges (mstEdges);
        auto tree = builder.Build ();

        LoadCalculator loadCalc;
        loadCalc.Calculate (*tree, sensors);

        auto edgeLoads = loadCalc.GetEdgeLoads ();
        auto bottleneck = loadCalc.GetBottleneck ();

        FailureSimulationResult simResult;

        if (bottleneck.valid) {
            Graph graph (std::move (matrix));
            auto dijkstra = std::make_shared<Dijkstra> ();
            FailureSimulator failureSim (dijkstra);

            simResult = failureSim.SimulateFailure (graph, *tree, bottleneck.child, tree->GetRoot ());
        }

        ReportGenerator report;

        report.SetInputFiles (graphFile, sensorsFile, static_cast<int> (matrix.size ()), static_cast<int> (sensors.size ()));

        report.SetMSTInfo (mstWeight, tree->GetRoot (), tree->GetNodeCount ());

        report.SetHierarchy (tree.get ());

        report.SetEdgeLoads (edgeLoads, bottleneck);

        if (simResult.success) {
            report.SetFailureSimulation (simResult);
        }

        report.PrintToConsole ();

        report.SaveToFile (reportFile);

    } catch (const std::exception& e) {
        std::cerr << "Greška: " << e.what () << std::endl;
        return 1;
    }

    return 0;
}