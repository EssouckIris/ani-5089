#include <iostream>
#include <string>

int main() {
    int p = 0;
    int f = 0;
    if (!(std::cin >> p >> f)) {
        std::cout << "PREMIER 0\n";
        return 0;
    }

    int compteur = 0;
    int premier = 0;

    for (int tour = 1; tour <= f; ++tour) {
        std::string action;
        std::cin >> action;

        if (action == "releve") {
            compteur = 0;
        } else {
            ++compteur;
        }

        // Morte dès que le compteur atteint P, et tant qu'on ne relève pas.
        bool morte = compteur >= p;
        if (morte && premier == 0) {
            premier = tour;
        }

        std::cout << compteur << " " << (morte ? "MORTE" : "VIVANTE") << "\n";
    }

    std::cout << "PREMIER " << premier << "\n";
    return 0;
}