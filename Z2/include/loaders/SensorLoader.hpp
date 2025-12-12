#pragma once

#include <string>

#include "../interfaces/ISensorLoader.hpp"
class SensorLoader : public ISensorLoader {
    public:
        SensorLoader () = default;
        ~SensorLoader () = default;
        std::vector<Sensor> LoadSensors (const std::filesystem::path& path) override;

    private:
        Sensor LoadSensorFromLine (const std::string& line);
        Sensor ValidateSensor (const Sensor& sensor);
};