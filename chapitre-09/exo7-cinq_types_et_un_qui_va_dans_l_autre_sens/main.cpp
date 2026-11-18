#include <cstdio>
#include <iostream>
#include <map>
#include <string>

int main() {
    int a = 0;
    std::cin >> a;
    std::map<std::string, bool> sortie;   // nom -> vrai si c'est une sortie
    int entrees = 0, sorties = 0;
    for (int i = 0; i < a; ++i) {
        std::string nom, type;
        std::cin >> nom >> type;
        const bool estSortie = (type == "HAPTIC");
        sortie[nom] = estSortie;
        if (estSortie) ++sorties; else ++entrees;
    }
    int o = 0;
    std::cin >> o;
    for (int i = 0; i < o; ++i) {
        std::string nom, operation;
        std::cin >> nom >> operation;
        std::map<std::string, bool>::const_iterator it = sortie.find(nom);
        if (it == sortie.end()) continue;
        if (it->second && operation == "LIT") {
            std::printf("%s LIT UNE SORTIE\n", nom.c_str());
        } else if (!it->second && operation == "ECRIT") {
            std::printf("%s ECRIT UNE ENTREE\n", nom.c_str());
        }
    }
    std::printf("ENTREES %d\n", entrees);
    std::printf("SORTIES %d\n", sorties);
    return 0;
}