#include "Diary/Diary.hpp"

int main () {
    Diary& diary = Diary::GetInstance ();

    while (true) {
        int option = 0;
        do {
            std::cout << "\n╔════════════════════════════════════╗\n";
            std::cout << "║        D N E V N I K              ║\n";
            std::cout << "╚════════════════════════════════════╝\n";
            std::cout << "1. Unos novog entrya\n";
            std::cout << "2. Brisanje posljednjeg unosa\n";
            std::cout << "3. Prikaz 5 najprioritetnijih unosa\n";
            std::cout << "4. Pregled dnevnika\n";
            std::cout << "0. Izlaz\n";
            std::cout << "────────────────────────────────────\n";
            std::cout << "Izaberite opciju: ";
            std::cin >> option;
            clear_screen ();
        } while (option < 0 || option > 4);

        try {
            switch (option) {
                case 1: {
                    // Unos novog entry-a
                    int priority;
                    std::string date_str, time_str, short_desc, full_text;

                    std::cout << "Prioritet (1-10): ";
                    std::cin >> priority;
                    std::cin.ignore ();

                    std::cout << "Datum (DD.MM.YYYY) ili Enter za danas: ";
                    std::getline (std::cin, date_str);

                    std::cout << "Vrijeme (HH:MM:SS) ili Enter za sada: ";
                    std::getline (std::cin, time_str);

                    std::cout << "Kratak opis: ";
                    std::getline (std::cin, short_desc);

                    std::cout << "Pun tekst (završite sa '.' u novom redu):\n";
                    std::string line;
                    while (std::getline (std::cin, line) && line != ".") {
                        full_text += line + "\n";
                    }

                    Date date = date_str.empty () ? Date::Today () : Date::ParseDate (date_str);
                    Time time = time_str.empty () ? Time::CurrentTime () : Time::ParseTime (time_str);

                    diary.AddEntry (priority, date, time, short_desc, full_text);
                    std::cout << "\n✓ Unos uspješno dodan!\n";
                    break;
                }

                case 2: {
                    diary.DeleteLastEntry ();
                    break;
                }

                case 3: {
                    diary.ShowTop5Priority ();
                    break;
                }

                case 4: {
                    // Pregled dnevnika
                    std::cout << "1. Svi unosi\n";
                    std::cout << "2. Po datumu\n";
                    std::cout << "3. Po opsegu datuma\n";
                    int sub_option;
                    std::cin >> sub_option;
                    std::cin.ignore ();

                    if (sub_option == 2) {
                        std::cout << "Unesite datum (DD.MM.YYYY): ";
                        std::string date_str;
                        std::getline (std::cin, date_str);
                        Date date = Date::ParseDate (date_str);
                        diary.ShowEntriesForDate (date);
                    } else if (sub_option == 3) {
                        std::cout << "Od datuma (DD.MM.YYYY): ";
                        std::string from_str;
                        std::getline (std::cin, from_str);
                        std::cout << "Do datuma (DD.MM.YYYY): ";
                        std::string to_str;
                        std::getline (std::cin, to_str);
                        Date from = Date::ParseDate (from_str);
                        Date to = Date::ParseDate (to_str);
                        diary.ShowEntriesByDateRange (from, to);
                    }
                    break;
                }

                case 0: {
                    std::cout << "Doviđenja!\n";
                    return 0;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "GREŠKA: " << e.what () << std::endl;
        }

        std::cout << "\nPritisnite Enter za nastavak...";
        std::cin.ignore ();
        std::cin.get ();
        clear_screen ();
    }
}