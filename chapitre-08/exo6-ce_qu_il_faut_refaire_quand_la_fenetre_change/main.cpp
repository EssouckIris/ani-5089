#include <iostream>
#include <sstream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;
    std::string ligne;
    std::getline(std::cin, ligne);          // fin de la ligne qui porte N

    int survivants = 0;
    int lues = 0;
    while (lues < n && std::getline(std::cin, ligne)) {
        if (!ligne.empty() && ligne.back() == '\r') ligne.pop_back();
        std::istringstream mots(ligne);     // une ligne entiere : le nombre de mots varie
        std::string nom;
        if (!(mots >> nom)) continue;       // ligne vide : on l'ignore
        ++lues;

        // position de la premiere occurrence de chaque mot (-1 s'il est absent)
        int posDetruit = -1, posRecree = -1, posReenregistre = -1;
        int rang = 0;
        std::string mot;
        while (mots >> mot) {
            if (mot == "DETRUIT" && posDetruit < 0) posDetruit = rang;
            else if (mot == "RECREE" && posRecree < 0) posRecree = rang;
            else if (mot == "REENREGISTRE" && posReenregistre < 0) posReenregistre = rang;
            // REDIMENSIONNE n'entre jamais dans la decision
            ++rang;
        }

        const char *verdict;
        if (posDetruit >= 0 && posRecree >= 0 && posRecree < posDetruit) {
            verdict = "MAUVAIS ORDRE";          // teste avant les absences
        } else if (posDetruit < 0 || posRecree < 0) {
            verdict = "CHAINE PERIMEE";
        } else if (posReenregistre < 0) {
            verdict = "POIGNEES PERDUES";
        } else {
            verdict = "SURVIT";
            ++survivants;
        }
        std::cout << nom << " " << verdict << "\n";
    }
    std::cout << "SURVIVANTS " << survivants << "\n";
    return 0;
}