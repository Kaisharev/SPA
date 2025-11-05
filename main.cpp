#include <iostream>
#include <cstdlib>
#include "DateTime/date.hpp"
#include "Utils/utils.hpp"

/*
int main (){
    while (true) { 
        int option = 0;
        do {
            std::cout << "D N E V N I K"<<std::endl;
            std::cout << "Odaberite opcije: \n1. Unos novog entrya\n2. Brisanje poslednjeg unosa\n3. Prikaz 5 najprioritetnijih unosa\n4. Pregled dnevnika"<<std::endl;
            std::cout << "Unesite jednu od opcija: "<<std::endl;
            std::cin >> option;
            clear_screen();
        } while (option < 1 || option > 4);
    }
    

    
}*/

int main() {
    try {
        // Test 1: Parsiranje validnog datuma
        Date d1 = Date::ParseDate("04.11.2025");
        std::cout << "Datum 1: " << d1.GetDateAsString() << "\n";
        
        // Test 2: Različiti separatori
        Date d2 = Date::ParseDate("1/10/2025");
        Date d3 = Date::ParseDate("15-12-2024");
        std::cout << "Datum 2: " << d2.GetDateAsString() << "\n";
        std::cout << "Datum 3: " << d3.GetDateAsString() << "\n";
        
        // Test 3: Trenutni datum
        Date today = Date::Today();
        std::cout << "Danas: " << today.GetDateAsString() << "\n";
        
        // Test 4: Poređenje
        if (d1 > d3) {
            std::cout << d1.GetDateAsString() << " je noviji od " 
                      << d3.GetDateAsString() << "\n";
        }
        
        // Test 5: Getteri
        std::cout << "Dan: " << d1.GetDay() << ", "
                  << "Mesec: " << d1.GetMonth() << ", "
                  << "Godina: " << d1.GetYear() << "\n";
        
        // Test 6: Neispravan datum (bacit će exception)
        try {
            Date invalid = Date::ParseDate("32.13.2025");
        } catch (const std::invalid_argument& e) {
            std::cout << "Uhvaćena greška: " << e.what() << "\n";
        }
        
        // Test 7: Neispravan format
        try {
            Date badFormat = Date::ParseDate("04-Nov-2025");
        } catch (const std::invalid_argument& e) {
            std::cout << "Uhvaćena greška: " << e.what() << "\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "GREŠKA: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}