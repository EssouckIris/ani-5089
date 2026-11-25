#include <cstdio>
#include <iostream>
#include <string>

enum Etat { REPOS, ATTENDUE, COMMENCEE };

int main() {
    int n = 0;
    std::cin >> n;
    Etat etat = REPOS;
    int fautes = 0, bloque = 0;
    for (int i = 1; i <= n; ++i) {
        std::string geste;
        std::cin >> geste;
        const char* verdict = "OK";
        if (geste == "ATTEND") {
            if (etat == REPOS) {
                etat = ATTENDUE;
            } else if (etat == ATTENDUE) {
                verdict = "DEJA ATTENDUE";
                ++fautes;
            } else {
                verdict = "TRAME EN COURS";
                ++fautes;
                if (bloque == 0) bloque = i;
            }
        } else if (geste == "COMMENCE") {
            if (etat == ATTENDUE) {
                etat = COMMENCEE;
            } else if (etat == REPOS) {
                verdict = "PAS ATTENDUE";
                ++fautes;
            } else {
                verdict = "DEJA COMMENCEE";
                ++fautes;
            }
        } else if (geste == "FINIT") {
            if (etat == COMMENCEE) {
                etat = REPOS;
            } else {
                verdict = "PAS COMMENCEE";
                ++fautes;
            }
        }
        std::printf("%d %s %s\n", i, geste.c_str(), verdict);
    }
    std::printf("FAUTES %d\n", fautes);
    std::printf("BLOQUE %d\n", bloque);
    return 0;
}