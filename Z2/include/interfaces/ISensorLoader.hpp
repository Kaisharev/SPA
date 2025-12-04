#pragma once
#include <filesystem>
#include <vector>

#include "../models/Sensor.hpp"
class ISensorLoader {
    public:
        virtual std::vector<Sensor> LoadSensors (const std::filesystem::path& path) = 0;
        virtual ~ISensorLoader () {}
};