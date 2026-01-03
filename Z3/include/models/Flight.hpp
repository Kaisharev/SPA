#pragma once
#include <iostream>
#include <string>

struct Flight {
        std::string _departure_airport;
        std::string _departure_code;
        std::string _departure_city;
        std::string _departure_country;
        std::string _arrival_airport;
        std::string _arrival_code;
        std::string _arrival_city;
        std::string _arrival_country;
        std::string _airline;
        std::string _flight_number;
        double _duration;

        Flight ()
            : _departure_airport ()
            , _departure_code ()
            , _departure_city ()
            , _departure_country ()
            , _arrival_airport ()
            , _arrival_code ()
            , _arrival_city ()
            , _arrival_country ()
            , _airline ()
            , _flight_number ()
            , _duration (0.0) {}

        Flight (std::string departure_airport, std::string departure_code, std::string departure_city, std::string departure_country,
                std::string arrival_airport, std::string arrival_code, std::string arrival_city, std::string arrival_country,
                std::string airline, std::string flight_number, double duration)
            : _departure_airport (departure_airport)
            , _departure_code (departure_code)
            , _departure_city (departure_city)
            , _departure_country (departure_country)
            , _arrival_airport (arrival_airport)
            , _arrival_code (arrival_code)
            , _arrival_city (arrival_city)
            , _arrival_country (arrival_country)
            , _airline (airline)
            , _flight_number (flight_number)
            , _duration (duration) {}

        const std::string& GetDepartureAirport () const {
            return _departure_airport;
        }
        const std::string& GetDepartureCode () const {
            return _departure_code;
        }
        const std::string& GetDepartureCity () const {
            return _departure_city;
        }
        const std::string& GetDepartureCountry () const {
            return _departure_country;
        }
        const std::string& GetArrivalAirport () const {
            return _arrival_airport;
        }
        const std::string& GetArrivalCode () const {
            return _arrival_code;
        }
        const std::string& GetArrivalCity () const {
            return _arrival_city;
        }
        const std::string& GetArrivalCountry () const {
            return _arrival_country;
        }
        const std::string& GetAirline () const {
            return _airline;
        }
        const std::string& GetFlightNumber () const {
            return _flight_number;
        }
        double GetDuration () const {
            return _duration;
        }

        void SetDepartureAirport (const std::string& v) {
            _departure_airport = v;
        }
        void SetDepartureCode (const std::string& v) {
            _departure_code = v;
        }
        void SetDepartureCity (const std::string& v) {
            _departure_city = v;
        }
        void SetDepartureCountry (const std::string& v) {
            _departure_country = v;
        }
        void SetArrivalAirport (const std::string& v) {
            _arrival_airport = v;
        }
        void SetArrivalCode (const std::string& v) {
            _arrival_code = v;
        }
        void SetArrivalCity (const std::string& v) {
            _arrival_city = v;
        }
        void SetArrivalCountry (const std::string& v) {
            _arrival_country = v;
        }
        void SetAirline (const std::string& v) {
            _airline = v;
        }
        void SetFlightNumber (const std::string& v) {
            _flight_number = v;
        }
        void SetDuration (double d) {
            _duration = d;
        }

        void PrintFlight () {
            std::cout << "Let:  " << _flight_number << ": " << _departure_code << " -> " << _arrival_code << " (" << _duration << "h, "
                      << _airline << ")\n";
        }
};
