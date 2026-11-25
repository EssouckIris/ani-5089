#include <cstdio>
#include <iostream>
#include <string>

int main() {
    long long hauteur = 0;
    int n = 0;
    std::cin >> hauteur >> n;
    int decalees = 0;
    for (int i = 0; i < n; ++i) {
        std::string nom, pose, couche;
        std::cin >> nom >> pose >> couche;
        long long decalage = 0;
        const char* verdict = "OK";
        if (pose != couche) {
            ++decalees;
            if (pose == "STAGE") {
                decalage = hauteur;
                verdict = "LEVITATION";
            } else {
                decalage = -hauteur;
                verdict = "ENTERRE";
            }
        }
        std::printf("%s %lld %s\n", nom.c_str(), decalage, verdict);
    }
    std::printf("DECALEES %d\n", decalees);
    return 0;
}