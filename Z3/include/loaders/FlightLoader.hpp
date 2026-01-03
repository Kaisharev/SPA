#pragma once
#include <string>

#include "..\interfaces\IFlightLoader.hpp"
#include "..\models\Flight.hpp"
class FlightLoader : IFlightLoader {
    public:
        Vector<Flight> LoadCSV (const std::filesystem::path& filename) override;
        Flight ParseLine (const std::string line) override;

    private:
        Flight* array;
        static double StringToDouble (const std::string& string);
        static Flight* ResizeFlightArray (Flight* flights);
};