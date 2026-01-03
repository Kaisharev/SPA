#include "../../include/loaders/FlightLoader.hpp"

#include <fstream>
#include <ranges>
#include <sstream>

Vector<Flight> FlightLoader::LoadCSV (const std::filesystem::path& filename) {
    Vector<Flight> flights;
    std::filesystem::path file_path = filename;
    std::ifstream entry_input (file_path);
    if (!entry_input.is_open ()) {
        throw std::runtime_error ("Ne mogu otvoriti fajl: " + file_path.string ());
    }
    std::string line;
    std::getline (entry_input, line);  // Preskače prvu linije CSV fajla

    while (std::getline (entry_input, line)) {
        flights.PushBack (ParseLine (line));
    }
    return flights;
}

Flight FlightLoader::ParseLine (const std::string line) {
    int index = 0;
    auto split_view = std::views::split (line, ',');

    std::string entry_text;
    std::string departure_airport;
    std::string departure_code;
    std::string departure_city;
    std::string departure_country;
    std::string arrival_airport;
    std::string arrival_code;
    std::string arrival_city;
    std::string arrival_country;
    std::string airline;
    std::string flight_number;
    double duration = 0.0;
    try {
        for (const auto subrange : split_view) {
            std::string sub_string;
            if (!subrange.empty ()) {
                sub_string.assign (subrange.begin (), subrange.end ());
            }

            auto start = sub_string.find_first_not_of (" \t\n\r");
            auto end = sub_string.find_last_not_of (" \t\n\r");
            if (start != std::string::npos && end != std::string::npos) {
                sub_string = sub_string.substr (start, end - start + 1);
            }

            switch (index) {
                case 0:
                    departure_airport = sub_string;
                    break;
                case 1:
                    arrival_airport = sub_string;
                    break;
                case 2:
                    departure_code = sub_string;
                    break;
                case 3:
                    arrival_code = sub_string;
                    break;
                case 4:
                    departure_city = sub_string;
                    break;
                case 5:
                    arrival_city = sub_string;
                    break;
                case 6:
                    departure_country = sub_string;
                    break;
                case 7:
                    arrival_country = sub_string;
                    break;
                case 8:
                    airline = sub_string;
                    break;
                case 9:
                    flight_number = sub_string;
                    break;
                case 10:
                    duration = std::stod (sub_string);
                    break;
            }
            index++;
        }
    } catch (std::exception& e) {
        std::cerr << "Neispravan format: " << e.what () << std::endl;
        return Flight{};
    }
    return Flight (departure_airport, departure_code, departure_city, departure_country, arrival_airport, arrival_code, arrival_city,
                   arrival_country, airline, flight_number, duration);
}