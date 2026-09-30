#include <iostream>
#include <string>

bool finitPar(const std::string& texte, const std::string& suffixe) {
    if (texte.length() < suffixe.length()) {
        return false;
    }

    return texte.compare(
        texte.length() - suffixe.length(),
        suffixe.length(),
        suffixe
    ) == 0;
}

int main() {
    std::string architecture;
    int F;

    std::cin >> architecture;
    std::cin >> F;

    long long tailleTotale = 0;
    bool signe = false;
    bool abiPresente = false;
    int inutile = 0;

    for (int i = 0; i < F; ++i) {
        std::string chemin;
        long long taille;

        std::cin >> chemin >> taille;

        tailleTotale += taille;

        // Vérification de la signature
        if (chemin.rfind("META-INF/", 0) == 0 &&
            (finitPar(chemin, ".RSA") ||
             finitPar(chemin, ".DSA") ||
             finitPar(chemin, ".EC"))) {
            signe = true;
        }

        // Vérification de l'architecture
        if (chemin.rfind("lib/", 0) == 0) {
            std::string prefixeABI = "lib/" + architecture + "/";

            if (chemin.rfind(prefixeABI, 0) == 0) {
                abiPresente = true;
            } else {
                ++inutile;
            }
        }
    }

    std::cout << tailleTotale << '\n';

    if (signe) {
        std::cout << "SIGNE\n";
    } else {
        std::cout << "NON SIGNE\n";
    }

    if (abiPresente) {
        std::cout << "ABI OUI\n";
    } else {
        std::cout << "ABI NON\n";
    }

    std::cout << "INUTILE " << inutile << '\n';

    return 0;
}