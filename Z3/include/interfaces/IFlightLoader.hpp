#pragma once
#include <filesystem>
#include <string>

#include "..\models\Flight.hpp"
#include "..\structures\Vector.hpp"
class IFlightLoader {
    public:
        virtual Vector<Flight> LoadCSV (const std::filesystem::path& filename) = 0;
        virtual Flight ParseLine (const std::string line) = 0;
        virtual ~IFlightLoader () = default;
};