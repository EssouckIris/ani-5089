#include <iostream>
#include <sstream>
#include <string>

int main() {
    int n = 0;
    std::string ligne;

    if (!std::getline(std::cin, ligne)) {
        return 0;
    }
    n = std::stoi(ligne);

    for (int i = 0; i < n; ++i) {
        if (!std::getline(std::cin, ligne)) {
            break;
        }

        // Une touche répétée ou une touche jumelle (W/Z, A/Q) ne compte qu'une fois :
        // on retient seulement si l'action est demandée ou non.
        bool avance = false;
        bool recule = false;
        bool gauche = false;
        bool droite = false;

        std::istringstream flux(ligne);
        std::string touche;
        while (flux >> touche) {
            if (touche == "W" || touche == "Z") {
                avance = true;
            } else if (touche == "S") {
                recule = true;
            } else if (touche == "A" || touche == "Q") {
                gauche = true;
            } else if (touche == "D") {
                droite = true;
            }
            // Toute autre touche (dont "rien") est ignorée.
        }

        int pas = (avance ? 1 : 0) - (recule ? 1 : 0);
        int cote = (droite ? 1 : 0) - (gauche ? 1 : 0);
        std::cout << pas << " " << cote << "\n";
    }

    return 0;
}