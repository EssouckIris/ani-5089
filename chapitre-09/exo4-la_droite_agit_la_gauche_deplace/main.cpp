#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

static bool EstDroite(const std::string& u) {
    return u == "SELECT" || u == "GRAB" || u == "AIM_POSE" || u == "GRIP_POSE" ||
           u == "HAPTIC" || u == "MOVE_RIGHT";
}

static bool EstGauche(const std::string& u) {
    return u == "SELECT_LEFT" || u == "GRAB_LEFT" || u == "AIM_POSE_LEFT" ||
           u == "GRIP_POSE_LEFT" || u == "HAPTIC_LEFT" || u == "MENU" || u == "MOVE";
}

int main() {
    int n = 0;
    std::string ligne;
    std::getline(std::cin, ligne);
    n = std::atoi(ligne.c_str());
    int deuxMains = 0;
    for (int i = 0; i < n; ++i) {
        if (!std::getline(std::cin, ligne)) break;
        std::istringstream flux(ligne);
        std::string nom, usage;
        flux >> nom;
        int droite = 0, gauche = 0;
        while (flux >> usage) {
            if (EstGauche(usage)) ++gauche;
            else if (EstDroite(usage)) ++droite;
        }
        const bool deux = droite > 0 && gauche > 0;
        if (deux) ++deuxMains;
        std::printf("%s %d %d %s\n", nom.c_str(), droite, gauche, deux ? "DEUX MAINS" : "UNE MAIN");
    }
    std::printf("DEUX MAINS %d\n", deuxMains);
    return 0;
}