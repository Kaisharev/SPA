#pragma once
#include <filesystem>
#include <string>
#include <vector>

#include "../interfaces/ILoadCalculator.hpp"
#include "../models/FailureSimulatorResults.hpp"
#include "../models/PathResult.hpp"
#include "ITree.hpp"

class IReportGenerator {
    public:
        virtual ~IReportGenerator () = default;

        virtual void SetMSTInfo (int totalWeight, int root, int nodeCount) = 0;

        virtual void SetHierarchy (const ITree* tree) = 0;

        virtual void SetEdgeLoads (const std::vector<EdgeLoad>& edgeLoads, const Bottleneck& bottleneck) = 0;

        virtual void SetFailureSimulation (const FailureSimulationResult& simResult) = 0;

        virtual void SetInputFiles (const std::filesystem::path& graphFile, const std::filesystem::path& sensorsFile, int matrix_rows,
                                    int sensor_count) = 0;

        virtual std::string GenerateReport () const = 0;

        virtual void PrintToConsole () const = 0;

        virtual void SaveToFile (const std::filesystem::path& filePath) const = 0;
};

