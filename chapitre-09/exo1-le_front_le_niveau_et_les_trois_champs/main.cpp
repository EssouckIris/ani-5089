#include <cstdio>
#include <iostream>

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }
    int precedent = 0;
    int fronts = 0, niveaux = 0;
    for (int i = 1; i <= n; ++i) {
        int presse = 0, lie = 0;
        std::cin >> presse >> lie;
        const int actif = lie;
        const int courant = actif ? presse : 0;
        const int change = (courant != precedent) ? 1 : 0;
        if (courant == 1 && change == 1) ++fronts;
        if (courant == 1) ++niveaux;
        std::printf("%d %d %d %d\n", i, courant, change, actif);
        precedent = courant;
    }
    std::printf("FRONTS %d\n", fronts);
    std::printf("NIVEAUX %d\n", niveaux);
    return 0;
}