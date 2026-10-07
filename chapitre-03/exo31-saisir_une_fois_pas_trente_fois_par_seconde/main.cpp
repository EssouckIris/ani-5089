#include <iostream>
#include <string>

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        std::cout << "SANS_GARDE 0\n";
        return 0;
    }

    int sansGarde = 0;
    for (int i = 0; i < n; ++i) {
        std::string evenement;
        std::cin >> evenement;

        if (evenement == "enfonce") {
            std::cout << "SAISIR\n";
            ++sansGarde;
        } else if (evenement == "relache") {
            std::cout << "LACHER\n";
        } else {
            // "repete" : une répétition n'est pas un nouvel enfoncement
            std::cout << "RIEN\n";
            if (evenement == "repete") {
                ++sansGarde;
            }
        }
    }

    std::cout << "SANS_GARDE " << sansGarde << "\n";
    return 0;
}