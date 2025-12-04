#include "utils.hpp"

void clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void signalHandler(int signum)
{
    std::cout << "\n\nPrekid programa (Ctrl+C)...\n";   
    std::cout << "Čuvam podatke...\n";

    Diary &diary = Diary::GetInstance();
    diary.~Diary();
    std::cout << "Doviđenja!\n";
    exit(signum);
}

const int MAX_ENTRIES = 5;