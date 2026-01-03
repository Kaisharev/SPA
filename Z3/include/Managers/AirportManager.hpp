#pragma once
#include "..\interfaces\IAirportManager.hpp"
class AirportManager : IAirportManager {
    public:
        void UpdateAirportCount (Vector<AirportStats>& stats, Flight& flight) override;
        void Sort (Vector<AirportStats>& airline_stats) override;
        void ShowTopK (BTree& tree, int k) override;
        void ShowFlightsForAirport(BTree& btree, std::string airportCode) override;
    private:
        void QSort (Vector<AirportStats>& airline_stats, int low, int high);
        void UpdateSingleCode (Vector<AirportStats>& stats, std::string code, std::string name);
        void OpenURL (const std::string& url);
        void ShowAlert (const std::string& title, const std::string& message);
};