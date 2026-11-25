#include <cstdio>
#include "actions.h"

int main() {
    // Deux actions liees (touches A et B), une troisieme liee a rien.
    EtatAction saisir, tirer, libre;

    std::printf("image | saisir c ch a | tirer c ch a | libre c ch a\n");
    for (int image = 1; image <= 6; ++image) {
        const bool toucheA = (image >= 2 && image <= 4);   // tenue de l'image 2 a 4
        const bool toucheB = (image == 5);                  // un seul appui
        const bool toucheC = (image >= 2 && image <= 4);    // pressee, mais liee a rien

        Mettre(saisir, toucheA, true);
        Mettre(tirer,  toucheB, true);
        Mettre(libre,  toucheC, false);

        std::printf("%5d | %8d %d %d | %7d %d %d | %7d %d %d\n", image,
                    saisir.courant, saisir.change, saisir.actif,
                    tirer.courant,  tirer.change,  tirer.actif,
                    libre.courant,  libre.change,  libre.actif);
    }
    return 0;
}