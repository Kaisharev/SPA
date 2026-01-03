#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "..\include\Managers\AirportManager.hpp"
#include "..\include\loaders\FlightLoader.hpp"
#include "..\include\structures\BTree.hpp"
#include "..\include\structures\Vector.hpp"
#ifdef _WIN32
#    include <windows.h>
#else
#    include <clocale>

#endif
std::filesystem::path FindDataFolder () {
    Vector<std::filesystem::path> possiblePaths = {"./data", "../data", "../../data", "../../../data"};

    for (const auto& path : possiblePaths) {
        if (std::filesystem::exists (path) && std::filesystem::is_directory (path)) {
            return std::filesystem::absolute (path);
        }
    }

    throw std::runtime_error ("Data folder nije pronađen!");
}

static void ClearStdin () {
    std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
}

int main (int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP (CP_UTF8);
    SetConsoleCP (CP_UTF8);
#else
    std::setlocale (LC_ALL, "en_US.UTF-8");
#endif

    try {
        if (argc < 3) {
            std::cerr << "Greška: Obavezno proslijediti test folder i vrijednost t kao argv.\n";
            std::cerr << "Upotreba: " << argv[0] << " <test_folder> <t>\n";
            return 1;
        }

        std::string test_folder_name = argv[1];
        int t_val = 3;
        try {
            t_val = std::stoi (argv[2]);
            if (t_val < 3) {
                std::cerr << "Greška: t mora biti >= 3.\n";
                return 1;
            }
        } catch (...) {
            std::cerr << "Greška: Nevažeći t.\n";
            return 1;
        }

        std::filesystem::path dataFolder = FindDataFolder ();

        FlightLoader loader;
        Vector<Flight> flights;
        AirportManager manager;
        std::unique_ptr<BTree> tree;
        bool flights_loaded = false;
        std::string airport_code;

        std::cout << "Uneseni testni folder: " << test_folder_name << "\n";
        std::filesystem::path csvFile = dataFolder / test_folder_name / "flights.csv";
        if (!std::filesystem::exists (csvFile)) {
            std::cerr << "Greška: Datoteka ne postoji: " << csvFile << "\n";
            return 1;
        }

        flights = loader.LoadCSV (csvFile);
        flights_loaded = true;
        std::cout << "Učitano " << flights.GetSize () << " letova iz " << csvFile << "\n";
        if (flights.GetSize () > 0) {
            std::cout << "Prvi let: ";
            flights[0].PrintFlight ();
        }

        tree = std::make_unique<BTree> (t_val);
        for (int i = 0; i < flights.GetSize (); ++i) {
            tree->Insert (flights[i]);
        }
        std::cout << "B-stablo kreirano sa t=" << t_val << "\n";

        while (true) {
            std::cout << "\n=== Glavni meni ===\n";
            std::cout << "1) Prikaz stabla (hierarhijski)\n";
            std::cout << "2) Pretraga opsega (min max)\n";
            std::cout << "3) Prikaži top K aerodroma\n";
            std::cout << "4) Prikaži letove po IATA kodu\n";
            std::cout << "5) Brisanje leta po broju\n";

            std::cout << "0) Izlaz\n";
            std::cout << "Izaberite opciju: ";

            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear ();
                ClearStdin ();
                std::cout << "Nevažeći unos.\n";
                continue;
            }

            if (choice == 0) {
                std::cout << "Izlaz.\n";
                break;
            }

            switch (choice) {
                case 1: {
                    if (!tree) {
                        std::cout << "Stablo nije kreirano.\n";
                        break;
                    }
                    std::cout << "\n=== Prikaz stabla ===\n";
                    tree->PrintHierarchical ();
                    break;
                }
                case 2: {
                    if (!tree) {
                        std::cout << "Stablo nije kreirano.\n";
                        break;
                    }
                    std::cout << "Unesite min i max (odvojene razmakom): ";
                    int minv, maxv;
                    if (!(std::cin >> minv >> maxv)) {
                        std::cin.clear ();
                        ClearStdin ();
                        std::cout << "Nevažeći unos.\n";
                        break;
                    }
                    std::cout << "Rezultati pretrage opsega [" << minv << ", " << maxv << "]:\n";
                    tree->SearchRange (minv, maxv);
                    break;
                }
                case 3: {
                    if (!tree) {
                        std::cout << "Stablo nije kreirano.\n";
                        break;
                    }
                    std::cout << "Unesite K: ";
                    int k;
                    if (!(std::cin >> k) || k <= 0) {
                        std::cin.clear ();
                        ClearStdin ();
                        std::cout << "Nevažeći K.\n";
                        break;
                    }
                    manager.ShowTopK (*tree, k);
                    break;
                }
                case 4: {
                    if (!tree) {
                        std::cout << "Stablo nije kreirano.\n";
                        break;
                    }
                    std::cout << "Unesite IATA kod aerodroma (npr. MEX, JFK, LHR): ";
                    std::cin >> airport_code;
                    for (auto& c : airport_code) c = toupper (c);
                    manager.ShowFlightsForAirport (*tree, airport_code);
                    break;
                }
                case 5: {
                    std::string flight_number;
                    std::cout << "Unesite broj leta koji želite da obrišete (npr. EM8650): ";
                    std::cin >> flight_number;
                    tree->DeleteFlight (flight_number);
                    break;
                }
                default:
                    std::cout << "Nepoznata opcija.\n";
                    break;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Greška: " << e.what () << std::endl;
        return 1;
    }

    return 0;
}
