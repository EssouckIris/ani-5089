#include <iostream>
#include <string>
#include <vector>

struct Rappel {
    long long id;
    std::string type;
};

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::vector<Rappel> registre;

    for (int i = 0; i < n; ++i) {
        std::string commande;
        std::cin >> commande;

        if (commande == "poser") {
            long long id = 0;
            std::string type;
            std::cin >> id >> type;

            // Un identifiant déjà posé est d'abord retiré, puis ajouté à la fin.
            for (std::size_t j = 0; j < registre.size(); ++j) {
                if (registre[j].id == id) {
                    registre.erase(registre.begin() + static_cast<long>(j));
                    break;
                }
            }
            registre.push_back({id, type});
        } else if (commande == "retirer") {
            long long id = 0;
            std::cin >> id;

            // Retirer un identifiant absent ne fait rien.
            for (std::size_t j = 0; j < registre.size(); ++j) {
                if (registre[j].id == id) {
                    registre.erase(registre.begin() + static_cast<long>(j));
                    break;
                }
            }
        } else if (commande == "envoyer") {
            std::string type;
            std::cin >> type;

            bool premier = true;
            for (const Rappel& r : registre) {
                if (r.type == type) {
                    if (!premier) {
                        std::cout << " ";
                    }
                    std::cout << r.id;
                    premier = false;
                }
            }
            if (premier) {
                std::cout << "AUCUN";
            }
            std::cout << "\n";
        }
    }

    return 0;
}