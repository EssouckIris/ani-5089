#include <iostream>
#include <string>

int main() {
    int vol = 0, n = 0;
    std::cin >> vol >> n;

    int enVol = 0;      // images soumises dont la carte n'a pas fini
    int bloque = 0;     // le PREMIER tour ou la boucle a du attendre, 0 sinon

    for (int tour = 1; tour <= n; ++tour) {
        std::string commande;
        std::cin >> commande;

        bool attend = false;
        if (commande == "SOUMET") {
            if (enVol >= vol) {
                attend = true;          // maximum atteint : on attend, le compte ne bouge pas
            } else {
                ++enVol;
            }
        } else if (commande == "FINI") {
            if (enVol > 0) --enVol;     // un FINI de trop ne descend pas sous zero
        }

        if (attend && bloque == 0) bloque = tour;   // on retient le premier blocage seulement

        std::cout << tour << " " << commande << " " << enVol << " "
                  << (attend ? "ATTEND" : "PASSE") << "\n";
    }
    std::cout << "BLOQUE " << bloque << "\n";
    return 0;
}