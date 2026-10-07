#include <iostream>
#include <string>
#include <vector>

int main() {
    int c = 0;
    if (!(std::cin >> c)) {
        return 0;
    }

    std::vector<long long> echelle(c);
    std::vector<long long> seuil(c);
    for (int i = 0; i < c; ++i) {
        std::string nom;
        std::cin >> nom >> echelle[i] >> seuil[i];
    }

    int t = 0;
    std::cin >> t;

    for (int tour = 0; tour < t; ++tour) {
        long long axe = 0;
        for (int i = 0; i < c; ++i) {
            long long brut = 0;
            std::cin >> brut;

            // L'échelle s'applique avant le seuil.
            long long contribution = brut * echelle[i] / 1000;
            long long absolue = contribution < 0 ? -contribution : contribution;

            // Ignorée seulement si strictement inférieure au seuil.
            if (absolue >= seuil[i]) {
                axe += contribution;
            }
        }
        std::cout << axe << "\n";
    }

    return 0;
}