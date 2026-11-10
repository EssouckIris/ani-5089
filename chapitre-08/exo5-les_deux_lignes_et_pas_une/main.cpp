#include <iostream>
#include <string>

int main() {
    long long largeur = 0, hauteur = 0;
    int n = 0;
    std::cin >> largeur >> hauteur >> n;

    int bloquantes = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        int cible = 0, taille = 0;
        long long lc = 0, hc = 0;
        std::cin >> nom >> cible >> taille >> lc >> hc;

        long long l = largeur, h = hauteur;   // la taille sur laquelle la passe s'execute VRAIMENT
        const char *verdict;

        if (cible == 0) {
            // rien n'est relie : la passe dessine dans la fenetre (meme si taille vaut 1)
            verdict = "PAS RELIEE";
        } else if (taille == 1) {
            l = lc;
            h = hc;
            verdict = "OK";
        } else {
            // cible posee sans la taille : la passe garde la taille de la fenetre
            if (largeur != lc || hauteur != hc) {   // une seule dimension qui differe suffit
                verdict = "BLOQUE";
                ++bloquantes;
            } else {
                verdict = "SANS EFFET";
            }
        }
        std::cout << nom << " " << l << " " << h << " " << verdict << "\n";
    }
    std::cout << "BLOQUANTES " << bloquantes << "\n";
    return 0;
}