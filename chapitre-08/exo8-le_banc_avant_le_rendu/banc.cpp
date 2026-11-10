#include "chaine.h"
#include <cstdio>

int main() {
    Chaine chaine;
    if (!Chaine::Creer(3, chaine)) {
        std::printf("creation d'un anneau de 3 : REFUSEE\n");
        return 1;
    }
    std::printf("creation d'un anneau de 3 : OK\n");

    // Six tours sur un anneau de trois : l'anneau doit boucler (0 1 2 0 1 2).
    for (int tour = 1; tour <= 6; ++tour) {
        int emprunte = -1, rendu = -1;
        const bool e = chaine.Emprunter(emprunte);
        const bool r = chaine.Rendre(rendu);
        std::printf("tour %d : emprunte %d, rendu %d (%s, %s)\n", tour, emprunte, rendu,
                    e ? "OK" : "REFUSE", r ? "OK" : "REFUSE");
    }

    // Les trois refus.
    int index = -1;

    chaine.Emprunter(index);                       // une image est maintenant sortie
    const bool deuxFois = chaine.Emprunter(index); // emprunter deux fois
    std::printf("emprunter deux fois : %s\n", deuxFois ? "ACCEPTE (faute)" : "REFUSE");
    chaine.Rendre(index);                          // on rend, plus rien n'est emprunte

    const bool sansEmprunt = chaine.Rendre(index); // rendre sans avoir emprunte
    std::printf("rendre sans avoir emprunte : %s\n", sansEmprunt ? "ACCEPTE (faute)" : "REFUSE");

    Chaine trop;
    const bool tropGrande = Chaine::Creer(Chaine::kMaxImages + 1, trop);   // plus grande que le maximum
    std::printf("creer une chaine de %d (maximum %d) : %s\n", Chaine::kMaxImages + 1,
                Chaine::kMaxImages, tropGrande ? "ACCEPTEE (faute)" : "REFUSEE");
    return 0;
}