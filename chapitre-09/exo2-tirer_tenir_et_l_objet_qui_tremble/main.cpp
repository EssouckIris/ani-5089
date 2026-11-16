#include <cstdio>
#include <iostream>

int main() {
    int n = 0;
    std::cin >> n;
    int precedent = 0;
    int fronts = 0, niveaux = 0;
    for (int i = 0; i < n; ++i) {
        int etat = 0;
        std::cin >> etat;
        if (etat == 1 && precedent == 0) ++fronts;
        if (etat == 1) ++niveaux;
        precedent = etat;
    }
    std::printf("BALLES FRONT %d\n", fronts);
    std::printf("BALLES NIVEAU %d\n", niveaux);
    std::printf("TENU NIVEAU %d\n", niveaux);
    std::printf("TENU FRONT %d\n", fronts);
    return 0;
}