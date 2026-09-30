#include <iostream>
#include <string>
#include <vector>
#include <set>

struct Prefixe {
    std::string prefixe;
    std::string module;
};

int main() {
    int P;
    std::cin >> P;

    std::vector<Prefixe> prefixes;

    for (int i = 0; i < P; ++i) {
        Prefixe p;
        std::cin >> p.prefixe >> p.module;
        prefixes.push_back(p);
    }

    int L;
    std::cin >> L;
    std::cin.ignore();

    std::set<std::string> modules;
    int inconnus = 0;

    const std::string marqueur = "undefined reference to '";

    for (int i = 0; i < L; ++i) {
        std::string ligne;
        std::getline(std::cin, ligne);

        std::size_t debut = ligne.find(marqueur);

        if (debut == std::string::npos) {
            continue;
        }

        debut += marqueur.length();

        std::size_t fin = ligne.find('\'', debut);

        if (fin == std::string::npos) {
            continue;
        }

        std::string symbole = ligne.substr(debut, fin - debut);

        std::string meilleurModule;
        std::size_t longueurMax = 0;

        for (const Prefixe& p : prefixes) {
            if (symbole.compare(0, p.prefixe.length(), p.prefixe) == 0) {
                if (p.prefixe.length() > longueurMax) {
                    longueurMax = p.prefixe.length();
                    meilleurModule = p.module;
                }
            }
        }

        if (longueurMax == 0) {
            ++inconnus;
        } else {
            modules.insert(meilleurModule);
        }
    }

    for (const std::string& module : modules) {
        std::cout << module << '\n';
    }

    if (inconnus > 0) {
        std::cout << "INCONNU " << inconnus << '\n';
    }

    return 0;
}