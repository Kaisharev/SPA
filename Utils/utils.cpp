#include "utils.hpp"
void clear_screen () {

    #ifdef _WIN32
        std::system ("cls");
    #else
        std::system ("clear");
    #endif

}