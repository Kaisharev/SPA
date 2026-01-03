#include "..\..\include\Managers\AirportManager.hpp"

#include <cstdlib>
#ifdef _WIN32
#    include <windows.h>

#    include <thread>

void ShowMessageBoxThread (std::wstring title, std::wstring message) {
    MessageBoxW (NULL, message.c_str (), title.c_str (), MB_OK | MB_ICONINFORMATION | MB_TOPMOST | MB_SETFOREGROUND);
}
#else
#    include <clocale>
#endif

void AirportManager::QSort (Vector<AirportStats>& stats, int low, int high) {
    if (low < high) {
        int pivot = stats[high].flight_count;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (stats[j].flight_count >= pivot) {
                i++;
                AirportStats temp = stats[i];
                stats[i] = stats[j];
                stats[j] = temp;
            }
        }
        AirportStats temp = stats[i + 1];
        stats[i + 1] = stats[high];
        stats[high] = temp;

        int pi = i + 1;

        QSort (stats, low, pi - 1);
        QSort (stats, pi + 1, high);
    }
}

void AirportManager::Sort (Vector<AirportStats>& airport_stats) {
    if (airport_stats.GetSize () > 1) {
        QSort (airport_stats, 0, airport_stats.GetSize () - 1);
    }
}

void AirportManager::UpdateAirportCount (Vector<AirportStats>& stats, Flight& flight) {
    UpdateSingleCode (stats, flight.GetDepartureCode (), flight.GetDepartureAirport ());

    UpdateSingleCode (stats, flight.GetArrivalCode (), flight.GetArrivalAirport ());
}

void AirportManager::UpdateSingleCode (Vector<AirportStats>& stats, std::string airport_code, std::string name) {
    for (int i = 0; i < stats.GetSize (); i++) {
        if (stats[i].airport_code == airport_code) {
            stats[i].flight_count++;
            return;
        }
    }
    stats.PushBack (AirportStats (airport_code, 1, name));
}

void AirportManager::ShowTopK (BTree& tree, int k) {
    Vector<Flight> allFlights;

    allFlights = tree.GetAllFlights ();

    Vector<AirportStats> stats;

    for (int i = 0; i < allFlights.GetSize (); i++) {
        UpdateSingleCode (stats, allFlights[i].GetDepartureCode (), allFlights[i].GetDepartureAirport ());
        UpdateSingleCode (stats, allFlights[i].GetArrivalCode (), allFlights[i].GetArrivalAirport ());
    }

    Sort (stats);

    int n = stats.GetSize ();
    if (k > n) k = n;
    bool found_easter_egg = false;
    std::cout << "\n--- TOP " << k << " AERODROMA SA NAJVISE LETOVA ---\n";
    for (int i = 0; i < k; i++) {
        std::cout << i + 1 << ". " << stats[i].airport_code << " - " << stats[i].airport_name << " - " << stats[i].flight_count
                  << " letova\n";
        if (stats[i].airport_name == "Aerodrom u Čitluku") found_easter_egg = true;
    }

    std::cout << "\n--- TOP " << k << " AERODROMA SA NAJMANJE LETOVA ---\n";
    for (int i = 0; i < k; i++) {
        std::cout << i + 1 << ". " << stats[n - 1 - i].airport_code << " - " << stats[n - 1 - i].airport_name << " - "
                  << stats[n - 1 - i].flight_count << " letova\n";
    }

    if (found_easter_egg) {
        std::cout << "\n🎉 Easter egg aktiviran!\n";
        std::cout << "[DEBUG] Prikazujem alert...\n";  // <-- DODAJ

        ShowAlert ("Easter Egg",
                   "Čestitam! Pošto je u CSVu koji ste odabrali aerodrom sa najviše letova famozni Aerodrom u Čitluku - ovim "
                   "putem ste nastambali na mali easter egg! \n Sada će Vam moj divni program otvoriti web pretraživač i pustiti "
                   "jednu divnu pjesmu!\n Uživajte! ");

        std::cout << "[DEBUG] Alert prikazan, otvaram URL...\n";  // <-- DODAJ

        OpenURL ("https://www.youtube.com/watch?v=WY30Db6HFfU&list=RDWY30Db6HFfU&start_radio=1");

        std::cout << "[DEBUG] URL otvoren.\n";  // <-- DODAJ
    }
}

void AirportManager::OpenURL (const std::string& url) {
#ifdef _WIN32
    ShellExecuteA (NULL, "open", url.c_str (), NULL, NULL, SW_SHOWNORMAL);
#elif __APPLE__

    std::string command = "open \"" + url + "\"";
    system (command.c_str ());
#else
    std::string command = "xdg-open \"" + url + "\" 2>/dev/null";
    system (command.c_str ());
#endif
}
// ...existing code...
void AirportManager::ShowAlert (const std::string& title, const std::string& message) {
#ifdef _WIN32
    AllowSetForegroundWindow (ASFW_ANY);  // Dozvoli bilo kojem procesu

    int titleLen = MultiByteToWideChar (CP_UTF8, 0, title.c_str (), -1, NULL, 0);
    int messageLen = MultiByteToWideChar (CP_UTF8, 0, message.c_str (), -1, NULL, 0);

    wchar_t* wTitle = new wchar_t[titleLen];
    wchar_t* wMessage = new wchar_t[messageLen];

    MultiByteToWideChar (CP_UTF8, 0, title.c_str (), -1, wTitle, titleLen);
    MultiByteToWideChar (CP_UTF8, 0, message.c_str (), -1, wMessage, messageLen);

    // Attach thread input (spoji sa foreground thread-om)
    HWND foregroundWindow = GetForegroundWindow ();
    DWORD foregroundThreadId = GetWindowThreadProcessId (foregroundWindow, NULL);
    DWORD currentThreadId = GetCurrentThreadId ();

    bool attached = false;
    if (foregroundThreadId != currentThreadId) {
        attached = AttachThreadInput (currentThreadId, foregroundThreadId, TRUE);
    }

    // Prikaži MessageBox
    MessageBoxW (NULL, wMessage, wTitle, MB_OK | MB_ICONINFORMATION | MB_TOPMOST | MB_SETFOREGROUND);

    // Detach thread input
    if (attached) {
        AttachThreadInput (currentThreadId, foregroundThreadId, FALSE);
    }

    delete[] wTitle;
    delete[] wMessage;
#elif __APPLE__
    std::string escapedMessage = message;
    std::string escapedTitle = title;

    size_t pos = 0;
    while ((pos = escapedMessage.find ("\"", pos)) != std::string::npos) {
        escapedMessage.replace (pos, 1, "\\\"");
        pos += 2;
    }
    pos = 0;
    while ((pos = escapedTitle.find ("\"", pos)) != std::string::npos) {
        escapedTitle.replace (pos, 1, "\\\"");
        pos += 2;
    }

    std::string command = "osascript -e 'display dialog \"" + escapedMessage + "\" with title \"" + escapedTitle +
                          "\" buttons {\"OK\"} default button 1'";
    system (command.c_str ());

#else
    std::string escapedMessage = message;
    std::string escapedTitle = title;

    size_t pos = 0;
    while ((pos = escapedMessage.find ("&", pos)) != std::string::npos) {
        escapedMessage.replace (pos, 1, "&amp;");
        pos += 5;
    }
    pos = 0;
    while ((pos = escapedMessage.find ("<", pos)) != std::string::npos) {
        escapedMessage.replace (pos, 1, "&lt;");
        pos += 4;
    }
    pos = 0;
    while ((pos = escapedMessage.find (">", pos)) != std::string::npos) {
        escapedMessage.replace (pos, 1, "&gt;");
        pos += 4;
    }

    std::string command = "zenity --info --title=\"" + escapedTitle + "\" --text=\"" + escapedMessage + "\" --width=400 2>/dev/null";
    int result = system (command.c_str ());

    if (result != 0) {
        command = "notify-send -u critical \"" + escapedTitle + "\" \"" + escapedMessage + "\" 2>/dev/null";
        result = system (command.c_str ());

        if (result != 0) {
            std::cout << "\n=== " << title << " ===\n" << message << "\n";
        }
    }
#endif
}
// ...existing code...
void AirportManager::ShowFlightsForAirport (BTree& tree, std::string airport_code) {
    Vector<Flight> allFlights;
    allFlights = tree.GetAllFlights ();

    Vector<Flight> departures;
    Vector<Flight> arrivals;

    for (int i = allFlights.GetSize () - 1; i >= 0; i--) {
        if (allFlights[i].GetDepartureCode () == airport_code) {
            departures.PushBack (allFlights[i]);
        }
        if (allFlights[i].GetArrivalCode () == airport_code) {
            arrivals.PushBack (allFlights[i]);
        }
    }

    std::cout << "\n--- ODLASCI SA AERODROMA " << airport_code << " ---\n";
    if (departures.IsEmpty ()) {
        std::cout << "Nema registrovanih odlazaka.\n";
    } else {
        for (int i = 0; i < departures.GetSize (); i++) {
            departures[i].PrintFlight ();
        }
    }

    std::cout << "\n--- DOLASCI NA AERODROM " << airport_code << "\n";
    if (arrivals.IsEmpty ()) {
        std::cout << "Nema registrovanih dolazaka.\n";
    } else {
        for (int i = 0; i < arrivals.GetSize (); i++) {
            arrivals[i].PrintFlight ();
        }
    }
}