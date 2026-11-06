#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;

    bool acquise = false;            // une image est acquise (on dessine dessus)
    bool attendSoumission = false;   // une image rendue attend d'etre soumise
    int fautes = 0;

    for (int tour = 1; tour <= n; ++tour) {
        std::string appel;
        std::cin >> appel;

        const char *refus = nullptr;   // la raison du refus, ou nullptr si l'appel passe

        if (appel == "ACQUIERT") {
            if (acquise) refus = "DEJA ACQUISE";
            else acquise = true;
        } else if (appel == "DESSINE") {
            if (!acquise) refus = "PAS ACQUISE";
        } else if (appel == "REND") {
            if (!acquise) refus = "RIEN ACQUIS";
            else { acquise = false; attendSoumission = true; }
        } else if (appel == "SOUMET") {
            if (!attendSoumission) refus = "PAS RENDUE";
            else attendSoumission = false;
        }

        std::cout << tour << " " << appel << " " << (refus ? refus : "OK") << "\n";
        if (refus) ++fautes;
    }
    std::cout << "FAUTES " << fautes << "\n";
    return 0;
}