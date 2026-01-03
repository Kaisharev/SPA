#include "../../include/reports/ReportGenerator.hpp"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

void ReportGenerator::SetMSTInfo (int totalWeight, int root, int nodeCount) {
    mstWeight_ = totalWeight;
    root_ = root;
    node_count_ = nodeCount;
}

void ReportGenerator::SetHierarchy (const ITree* tree) {
    std::ostringstream ss;
    buildHierarchyString (tree, tree->GetRoot (), "", true, ss);
    hierarchy_string_ = ss.str ();
}

void ReportGenerator::buildHierarchyString (const ITree* tree, int node, const std::string& prefix, bool isLast,
                                            std::ostringstream& ss) const {
    ss << prefix;
    ss << (isLast ? "└── " : "├── ");
    ss << node << " (dubina=" << tree->GetDepth (node) << ")";

    if (tree->IsRoot (node)) {
        ss << " [korijen]";
    }
    if (tree->IsLeaf (node)) {
        ss << " [listić]";
    }
    ss << "\n";

    auto children = tree->GetChildren (node);
    for (size_t i = 0; i < children.size (); i++) {
        bool lastChild = (i == children.size () - 1);
        buildHierarchyString (tree, children[i], prefix + (isLast ? "    " : "│   "), lastChild, ss);
    }
}

void ReportGenerator::SetEdgeLoads (const std::vector<EdgeLoad>& edgeLoads, const Bottleneck& bottleneck) {
    edge_loads_ = edgeLoads;
    bottleneck_ = bottleneck;
}

void ReportGenerator::SetFailureSimulation (const FailureSimulationResult& simResult) {
    simulation_results_ = simResult;
    hasSimulation_ = simResult.success;
}

void ReportGenerator::SetInputFiles (const std::filesystem::path& graphFile, const std::filesystem::path& sensorsFile, int matrix_rows,
                                     int sensor_count) {
    graph_file = graphFile;
    sensors_file = sensorsFile;
    matrix_rows_ = matrix_rows;
    sensor_count_ = sensor_count;
}

std::string ReportGenerator::formatSeparator (char c) const {
    return std::string (80, c) + "\n";
}

std::string ReportGenerator::formatHeader () const {
    std::ostringstream ss;
    ss << formatSeparator ('=');
    ss << "               STRUKTURE PODATAKA I ALGORITMI - PRIMJER IZVRŠENJA PROGRAMA                      \n";
    ss << formatSeparator ('=');

    std::time_t now = std::time (nullptr);
    char timeBuffer[64];
    std::strftime (timeBuffer, sizeof (timeBuffer), "%d. %m.%Y.  %H:%M:%S", std::localtime (&now));
    ss << "Datum generisanja izvještaja: " << timeBuffer << "\n\n";

    return ss.str ();
}

std::string ReportGenerator::formatInputInfo () const {
    std::ostringstream ss;
    ss << "ULAZNI PODACI:\n";
    ss << formatSeparator ('-');
    ss << "Graf fajl:      " << graph_file.string () << "\n";
    ss << "Senzori fajl:  " << sensors_file.string () << "\n";
    // ss << "Matrica:       " << matrix_rows_ << " x " << matrix_rows_ << "\n";
    // iz nekog razloga samo ispisuje 0x0...
    ss << "Broj senzora:  " << sensor_count_ << "\n\n";
    return ss.str ();
}

std::string ReportGenerator::formatMSTInfo () const {
    std::ostringstream ss;
    ss << "MINIMALNO RAZAPINJUĆE STABLO (MST):\n";
    ss << formatSeparator ('-');
    ss << "Korijen (centrala):  " << root_ << "\n";
    ss << "Broj čvorova:        " << node_count_ << "\n";
    ss << "Ukupna težina MST:   " << mstWeight_ << "\n\n";
    return ss.str ();
}

std::string ReportGenerator::formatHierarchy () const {
    std::ostringstream ss;
    ss << "HIJERARHIJA STABLA:\n";
    ss << formatSeparator ('-');
    ss << hierarchy_string_;
    ss << "\n";
    return ss.str ();
}

std::string ReportGenerator::formatEdgeLoads () const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision (0);

    ss << "OPTEREĆENJA GRANA (KB/min):\n";
    ss << formatSeparator ('-');

    auto sorted_loads = edge_loads_;
    std::sort (sorted_loads.begin (), sorted_loads.end (), [] (const EdgeLoad& a, const EdgeLoad& b) {
        return a.load > b.load;
    });

    ss << std::left << std::setw (15) << "Grana" << std::right << std::setw (15) << "Opterećenje" << std::setw (15) << "Br. senzora"
       << "\n";
    ss << std::string (45, '-') << "\n";

    for (const auto& edge : sorted_loads) {
        std::ostringstream edgeStr;
        edgeStr << edge.child << " -> " << edge.parent;
        ss << std::left << std::setw (15) << edgeStr.str () << std::right << std::setw (12) << edge.load << " KB" << std::setw (12)
           << edge.sensor_count << "\n";
    }
    ss << "\n";

    return ss.str ();
}

std::string ReportGenerator::formatBottleneck () const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision (0);

    ss << "USKO GRLO:\n";
    ss << formatSeparator ('-');

    if (bottleneck_.valid) {
        ss << "Najopterećenija grana: " << bottleneck_.child << " -> " << bottleneck_.parent << "\n";
        ss << "Opterećenje:           " << bottleneck_.load << " KB/min\n";
        ss << "Broj senzora:          " << bottleneck_.sensor_count << "\n";
    } else {
        ss << "Nema uskog grla (stablo prazno ili ima samo korijen).\n";
    }
    ss << "\n";

    return ss.str ();
}

std::string ReportGenerator::formatFailureSimulation () const {
    if (!hasSimulation_) {
        return "";
    }

    std::ostringstream ss;

    ss << "SIMULACIJA KVARA GRANE:\n";
    ss << formatSeparator ('-');
    ss << "Simuliran kvar grane: " << simulation_results_.failed_edge_from << " -> " << simulation_results_.failed_edge_to << "\n";
    ss << "Pogođeni čvorovi:     " << simulation_results_.affected_nodes.size () << "\n\n";

    ss << "REZERVNE RUTE (Dijkstrin algoritam po originalnom grafu):\n";
    ss << std::string (45, '-') << "\n";

    for (const auto& route : simulation_results_.backup_routes) {
        ss << "Čvor " << route.node << ":\n";

        if (route.is_reachable && !route.path.empty ()) {
            ss << "  Ruta:      ";
            for (size_t i = 0; i < route.path.size (); ++i) {
                ss << route.path[i];
                if (i < route.path.size () - 1) ss << " -> ";
            }
            ss << "\n";
            ss << "  Distanca: " << route.distance << "\n";
        } else {
            ss << "  NEMA ALTERNATIVNE RUTE!\n";
        }
        ss << "\n";
    }

    return ss.str ();
}

std::string ReportGenerator::GenerateReport () const {
    std::ostringstream ss;

    ss << formatHeader ();
    ss << formatInputInfo ();
    ss << formatMSTInfo ();
    ss << formatHierarchy ();
    ss << formatEdgeLoads ();
    ss << formatBottleneck ();
    ss << formatFailureSimulation ();
    ss << formatSeparator ('=');
    ss << "                              KRAJ IZVJEŠTAJA                                   \n";
    ss << formatSeparator ('=');

    return ss.str ();
}

void ReportGenerator::PrintToConsole () const {
    std::cout << GenerateReport ();
}

void ReportGenerator::SaveToFile (const std::filesystem::path& filePath) const {
    std::ofstream output_file (filePath);

    if (!output_file.is_open ()) {
        throw std::runtime_error ("Ne mogu otvoriti fajl:  " + filePath.string ());
    }

    output_file << GenerateReport ();
    output_file.close ();

    std::cout << "\n✓ Izvještaj sačuvan: " << filePath << "\n";
}