#pragma once
#include <string>

#include "..\models\AirportStats.hpp"
#include "..\structures\BTree.hpp"
#include "..\structures\Vector.hpp"

class IAirportManager {
    public:
        virtual void UpdateAirportCount (Vector<AirportStats>& stats, Flight& flight) = 0;
        virtual void Sort (Vector<AirportStats>& airline_stats) = 0;
        virtual void ShowTopK (BTree& tree, int k) = 0;
        virtual void ShowFlightsForAirport(BTree& btree, std::string airportCode) = 0;
};