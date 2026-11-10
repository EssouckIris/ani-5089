#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    long long images = 0;
    int n = 0;
    std::cin >> images >> n;

    // index -> valeur. On ne sait pas ce que la valeur designe, on la garde telle quelle,
    // dans un entier de 64 bits. Un index absent de la table veut dire "VIDE".
    std::unordered_map<long long, unsigned long long> poignees;

    for (int i = 0; i < n; ++i) {
        std::string commande;
        std::cin >> commande;

        if (commande == "POSE") {
            long long index = 0;
            unsigned long long valeur = 0;
            std::cin >> index >> valeur;
            if (index < 0 || index >= images) {
                std::cout << "HORS ANNEAU\n";
            } else {
                poignees[index] = valeur;      // reposer remplace, sans compter deux fois
            }
        } else if (commande == "LIT") {
            long long index = 0;
            std::cin >> index;
            auto it = poignees.find(index);    // hors anneau : jamais pose, donc VIDE
            if (it == poignees.end()) {
                std::cout << "VIDE\n";
            } else {
                std::cout << it->second << "\n";   // zero est une valeur comme une autre
            }
        }
    }
    std::cout << "POSEES " << poignees.size() << "\n";
    return 0;
}