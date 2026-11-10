#include <cstdlib>
#include <iostream>
#include <string>

// Un anneau d'images avec son drapeau d'emprunt : les regles de l'anneau ordinaire.
struct Anneau {
    int suivant = 0;        // l'image que l'anneau designe
    bool emprunte = false;  // une image est-elle sortie ?
    int rendus = 0;         // rendus ACCEPTES seulement
};

int main() {
    int images = 0, n = 0;
    std::cin >> images >> n;

    Anneau gauche, droit;   // deux anneaux vraiment separes
    int desync = 0;         // le premier tour ou la difference a depasse 1

    for (int tour = 1; tour <= n; ++tour) {
        std::string oeil, commande;
        std::cin >> oeil >> commande;

        Anneau &a = (oeil == "G") ? gauche : droit;

        std::cout << tour << " " << oeil << " " << commande << " ";
        if (commande == "EMPRUNTE") {
            if (!a.emprunte) {
                a.emprunte = true;
                std::cout << a.suivant << "\n";
            } else {
                std::cout << "REFUSE\n";
            }
        } else {   // REND
            if (a.emprunte) {
                std::cout << a.suivant << "\n";
                a.emprunte = false;
                a.suivant = (a.suivant + 1) % images;   // l'anneau avance au RENDU
                ++a.rendus;                             // on ne compte que les rendus acceptes
            } else {
                std::cout << "REFUSE\n";
            }
        }

        const int difference = std::abs(gauche.rendus - droit.rendus);
        if (difference > 1 && desync == 0) desync = tour;   // "depasse" : strictement plus que 1
    }

    std::cout << "DECALAGE " << std::abs(gauche.rendus - droit.rendus) << "\n";
    std::cout << "DESYNC " << desync << "\n";
    return 0;
}