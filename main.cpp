#include <iostream>
#include <cstdlib>

void clear_screen () {

    #ifdef _WIN32
        std::system ("cls");
    #else
        std::system  ("clear");
    #endif

}


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
    

    
}