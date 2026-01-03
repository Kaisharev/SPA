#pragma once
#include <string>
struct AirportStats {
        std::string airport_code;
        std::string airport_name;
        int flight_count;

        AirportStats () : airport_code ("N/A"), flight_count (0), airport_name ("N/A") {};
        AirportStats (const std::string& code, int count, std::string& name)
            : airport_code (code), airport_name (name), flight_count (count) {};
};