#include <iostream>

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        std::cout << "LISIBLE 0\n";
        return 0;
    }

    int lisibles = 0;

    for (int i = 0; i < n; ++i) {
        long long largeur = 0;
        long long hauteur = 0;
        long long echelle = 0;
        long long champ = 0;
        std::cin >> largeur >> hauteur >> echelle >> champ;

        // Taille réelle : division entière, comme demandé.
        long long largeurReelle = largeur * echelle / 100;
        long long hauteurReelle = hauteur * echelle / 100;

        // Pixels par degré, arrondi au plus proche, en entiers.
        long long parDegre = 0;
        if (champ > 0) {
            parDegre = (largeurReelle + champ / 2) / champ;
        }

        if (parDegre >= 15) {
            ++lisibles;
        }

        std::cout << largeurReelle << " " << hauteurReelle << " "
                  << parDegre << "\n";
    }

    std::cout << "LISIBLE " << lisibles << "\n";
    return 0;
}