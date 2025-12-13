#include "../../include/simulation/LoadCalculator.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

void LoadCalculator::Calculate (const ITree& tree, const std::vector<Sensor>& sensors) {
    edge_loads_.clear ();
    subtree_load_.clear ();
    subtreesensor_count_.clear ();
    own_load_.clear ();
    bottleneck_ = Bottleneck ();

    for (const auto& sensor : sensors) {
        if (tree.Contains (sensor.id)) {
            own_load_[sensor.id] = static_cast<double> (sensor.data_output);
        }
    }

    calculateDFS (tree, tree.GetRoot ());

    findBottleneck ();
}

void LoadCalculator::calculateDFS (const ITree& tree, int current) {
    double load = 0.0;
    int sensor_count = 0;

    auto it = own_load_.find (current);
    if (it != own_load_.end ()) {
        load = it->second;
        sensor_count = 1;
    }

    for (int child : tree.GetChildren (current)) {
        calculateDFS (tree, child);

        load += subtree_load_[child];
        sensor_count += subtreesensor_count_[child];
    }

    subtree_load_[current] = load;
    subtreesensor_count_[current] = sensor_count;

    int parent = tree.GetParent (current);
    if (parent != -1) {
        edge_loads_.emplace_back (current, parent, load, sensor_count);
    }
}

void LoadCalculator::findBottleneck () {
    if (edge_loads_.empty ()) {
        bottleneck_ = Bottleneck ();
        return;
    }

    auto maxIt = std::max_element (edge_loads_.begin (), edge_loads_.end (), [] (const EdgeLoad& a, const EdgeLoad& b) {
        return a.load < b.load;
    });

    bottleneck_ = Bottleneck (maxIt->child, maxIt->parent, maxIt->load, maxIt->sensor_count);
}

std::vector<EdgeLoad> LoadCalculator::GetEdgeLoads () const {
    return edge_loads_;
}

Bottleneck LoadCalculator::GetBottleneck () const {
    return bottleneck_;
}

double LoadCalculator::GetSubtreeLoad (int node) const {
    auto it = subtree_load_.find (node);
    return (it != subtree_load_.end ()) ? it->second : 0.0;
}

int LoadCalculator::GetSubtreesensor_count (int node) const {
    auto it = subtreesensor_count_.find (node);
    return (it != subtreesensor_count_.end ()) ? it->second : 0;
}

std::string LoadCalculator::FormatEdgeLoads () const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision (0);

    ss << "Opterecenja grana (KB/min):\n";
    for (const auto& edge : edge_loads_) {
        ss << edge.child << " -> " << edge.parent << " :  " << edge.load << " (Broj senzora:  " << edge.sensor_count << ")\n";
    }

    return ss.str ();
}

std::string LoadCalculator::FormatBottleneck () const {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision (0);

    if (!bottleneck_.valid) {
        ss << "Nema uskog grla (stablo prazno ili ima samo korijen).\n";
    } else {
        ss << "Najopterecenija grana:  " << bottleneck_.child << " -> " << bottleneck_.parent << " (load=" << bottleneck_.load
           << " KB/min, "
           << "senzora=" << bottleneck_.sensor_count << ")\n";
    }

    return ss.str ();
}