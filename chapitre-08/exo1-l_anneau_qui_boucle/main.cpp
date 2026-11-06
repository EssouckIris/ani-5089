#include <iostream>
#include <string>

int main() {
    int images = 0, n = 0;
    std::cin >> images >> n;

    int suivant = 0;          // l'image que l'anneau designe
    bool emprunte = false;    // une image est-elle sortie ?
    int prets = 0;            // emprunts acceptes

    for (int tour = 1; tour <= n; ++tour) {
        std::string commande;
        std::cin >> commande;

        if (commande == "EMPRUNTE") {
            if (!emprunte) {
                emprunte = true;
                ++prets;
                std::cout << tour << " EMPRUNTE " << suivant << "\n";
            } else {
                std::cout << tour << " EMPRUNTE REFUSE\n";
            }
        } else if (commande == "REND") {
            if (emprunte) {
                std::cout << tour << " REND " << suivant << "\n";
                emprunte = false;
                suivant = (suivant + 1) % images;   // l'anneau avance au RENDU
            } else {
                std::cout << tour << " REND REFUSE\n";
            }
        }
    }
    std::cout << "PRETS " << prets << "\n";
    return 0;
}