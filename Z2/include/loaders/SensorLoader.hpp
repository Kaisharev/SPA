#pragma once
#include <filesystem>
#include <string>
#include <vector>

#include "../interfaces/ISensorLoader.hpp"
class SensorLoader : public ISensorLoader {
        SensorLoader () = default;
        ~SensorLoader () = default;
        std::vector<Sensor> LoadSensors (const std::filesystem::path& path) override;

    private:
        Sensor LoadSensorFromLine (const std::string& line);
        Sensor ValidateSensor (const Sensor& sensor);
};