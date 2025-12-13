#pragma once
#include <sstream>

#include "../interfaces/IReportGenerator.hpp"
#include "../interfaces/ITree.hpp"

class ReportGenerator : public IReportGenerator {
    public:
        ReportGenerator () = default;

        void SetMSTInfo (int totalWeight, int root, int nodeCount) override;
        void SetHierarchy (const ITree* tree) override;
        void SetEdgeLoads (const std::vector<EdgeLoad>& edgeLoads, const Bottleneck& bottleneck) override;
        void SetFailureSimulation (const FailureSimulationResult& simResult) override;
        void SetInputFiles (const std::filesystem::path& graphFile, const std::filesystem::path& sensorsFile, int matrix_rows,
                            int sensor_count) override;

        std::string GenerateReport () const override;
        void PrintToConsole () const override;
        void SaveToFile (const std::filesystem::path& filePath) const override;

    private:
        int mstWeight_ = 0;
        int root_ = 0;
        int node_count_ = 0;
        std::string hierarchy_string_;
        std::vector<EdgeLoad> edge_loads_;
        Bottleneck bottleneck_;
        FailureSimulationResult simulation_results_;
        bool hasSimulation_ = false;

        std::filesystem::path graph_file;
        std::filesystem::path sensors_file;
        int matrix_rows_ = 0;
        int sensor_count_ = 0;

        std::string formatHeader () const;
        std::string formatInputInfo () const;
        std::string formatMSTInfo () const;
        std::string formatHierarchy () const;
        std::string formatEdgeLoads () const;
        std::string formatBottleneck () const;
        std::string formatFailureSimulation () const;
        std::string formatSeparator (char c = '-') const;

        void buildHierarchyString (const ITree* tree, int node, const std::string& prefix, bool isLast, std::ostringstream& ss) const;
};