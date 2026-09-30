#include <iostream>
#include <string>

struct Scene {
    std::string nom;
    long long debug;
    long long release;
};

int main() {
    long long budget;
    int S;

    std::cin >> budget;
    std::cin >> S;

    int trompe = 0;

    for (int i = 0; i < S; ++i) {
        Scene scene;

        std::cin >> scene.nom >> scene.debug >> scene.release;

        long long facteur = (scene.debug + scene.release / 2) / scene.release;

        if (scene.release <= budget) {
            std::cout << scene.nom << " " << facteur << " TIENT\n";
        } else {
            std::cout << scene.nom << " " << facteur << " DEPASSE\n";
        }

        if (scene.debug > budget && scene.release <= budget) {
            ++trompe;
        }
    }

    std::cout << "TROMPE " << trompe << "\n";

    return 0;
}