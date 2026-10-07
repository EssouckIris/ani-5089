#include <iostream>
#include <string>

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    // Notre accumulateur : on ajoute, on vide à chaque image.
    long long totalX = 0;
    long long totalY = 0;

    // Moteur défectueux : écrase à chaque mouvement, ne se vide jamais.
    long long moteurX = 0;
    long long moteurY = 0;

    for (int i = 0; i < n; ++i) {
        std::string commande;
        std::cin >> commande;

        if (commande == "bouge") {
            long long dx = 0;
            long long dy = 0;
            std::cin >> dx >> dy;
            totalX += dx;
            totalY += dy;
            moteurX = dx;
            moteurY = dy;
        } else if (commande == "image") {
            std::cout << totalX << " " << totalY << " "
                      << moteurX << " " << moteurY << "\n";
            // Remise à zéro systématique, même si rien n'a bougé.
            totalX = 0;
            totalY = 0;
        }
    }

    return 0;
}