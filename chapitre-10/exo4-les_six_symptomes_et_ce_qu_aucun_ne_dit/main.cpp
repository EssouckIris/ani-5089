#include <cstdio>
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, std::string> cause;
    cause["BLOQUE_AU_WAIT"] = "FIN DE TRAME";
    cause["PAS_DE_REPRISE"] = "FIN SANS RENDU";
    cause["OEIL_NOIR"] = "CHAINE MANQUANTE";
    cause["TREMBLEMENT"] = "MAUVAIS INSTANT";
    cause["CORRECTION_DE_TRAVERS"] = "POSE FRAICHE";
    cause["SCENE_DECALEE"] = "MAUVAIS ESPACE";

    int n = 0;
    std::cin >> n;
    int diagnostiques = 0, inconnus = 0;
    for (int i = 0; i < n; ++i) {
        std::string symptome;
        std::cin >> symptome;
        std::map<std::string, std::string>::const_iterator it = cause.find(symptome);
        if (it == cause.end()) {
            ++inconnus;
            std::printf("%s INCONNU\n", symptome.c_str());
        } else {
            ++diagnostiques;
            std::printf("%s %s\n", symptome.c_str(), it->second.c_str());
        }
    }
    std::printf("DIAGNOSTIQUES %d\n", diagnostiques);
    std::printf("INCONNUS %d\n", inconnus);
    return 0;
}