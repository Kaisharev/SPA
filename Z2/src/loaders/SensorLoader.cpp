
#include "../../include/loaders/SensorLoader.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <sstream>

std::vector<Sensor> SensorLoader::LoadSensors (const std::filesystem::path& path) {
    std::filesystem::path file_path = path;
    if (!std::filesystem::exists (file_path)) {
        throw std::runtime_error ("Fajl ne postoji: " + file_path.string ());
    }
    std::ifstream entry_input (file_path);
    if (!entry_input.is_open ()) {
        throw std::runtime_error ("Ne mogu otvoriti fajl: " + file_path.string ());
    }
    std::vector<Sensor> sensors;
    std::string line;
    std::getline (entry_input, line);  // Preskakanje prve linije CSV fajla
    while (std::getline (entry_input, line)) {
        sensors.push_back (LoadSensorFromLine (line));
    }

    return sensors;
}

Sensor SensorLoader::LoadSensorFromLine (const std::string& line) {
    int id = -1, criticality = -1, data_output = -1;
    std::string sensor_type = "N/A";

    int index = 0;
    auto split_view = std::views::split (line, ',');
    std::string entry_text;

    try {
        for (const auto subrange : split_view) {
            std::string sub_string (subrange.begin (), subrange.end ());

            size_t start = sub_string.find_first_not_of (" \t\n\r");
            size_t end = sub_string.find_last_not_of (" \t\n\r");
            if (start != std::string::npos && end != std::string::npos) {
                sub_string = sub_string.substr (start, end - start + 1);
            }

            switch (index) {
                case 0:
                    id = std::stoi (sub_string);
                    break;
                case 1:
                    sensor_type = sub_string;
                    break;
                case 2:
                    criticality = std::stoi (sub_string);
                    break;
                case 3:
                    data_output = std::stoi (sub_string);
                    break;
            }
            index++;
        }

    } catch (std::exception& e) {
        std::cerr << "Neispravan format: " << e.what () << std::endl;
        return Sensor{};
    }

    return Sensor (id, sensor_type, criticality, data_output);
}
