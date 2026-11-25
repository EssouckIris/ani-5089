#include <cstdio>
#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;
    int refusees = 0, averties = 0;
    for (int i = 0; i < n; ++i) {
        std::string nom;
        int commence = 0, rend = 0, gauche = 0, droite = 0;
        std::cin >> nom >> commence >> rend >> gauche >> droite;
        const char* verdict = "OK";
        if (!commence) {
            verdict = "REFUSEE";
            ++refusees;
        } else if (!rend) {
            if (gauche || droite) {
                verdict = "COUCHE SANS RENDU";
                ++averties;
            }
        } else {
            if (gauche && droite) {
                verdict = "OK";
            } else if (!gauche && !droite) {
                verdict = "SOUMISSION VIDE";
                ++averties;
            } else if (!gauche) {
                verdict = "OEIL NOIR G";
                ++averties;
            } else {
                verdict = "OEIL NOIR D";
                ++averties;
            }
        }
        std::printf("%s %s\n", nom.c_str(), verdict);
    }
    std::printf("REFUSEES %d\n", refusees);
    std::printf("AVERTIES %d\n", averties);
    return 0;
}