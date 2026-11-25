#include <cstdio>
#include <cstdlib>
#include <iostream>

int main() {
    int n = 0;
    std::cin >> n;
    int justes = 0, pires = 0;
    for (int i = 0; i < n; ++i) {
        long long rendu = 0, reel = 0, soumis = 0;
        std::cin >> rendu >> reel >> soumis;
        const long long sans = rendu - reel;
        const long long avec = rendu - soumis;
        const long long as = sans < 0 ? -sans : sans;
        const long long aa = avec < 0 ? -avec : avec;
        const char* verdict;
        if (avec == 0) {
            verdict = "JUSTE";
            ++justes;
        } else if (aa < as) {
            verdict = "PARTIEL";
        } else if (aa == as) {
            verdict = "SANS EFFET";
        } else {
            verdict = "PIRE";
            ++pires;
        }
        std::printf("SANS %lld AVEC %lld %s\n", sans, avec, verdict);
    }
    std::printf("JUSTES %d\n", justes);
    std::printf("PIRES %d\n", pires);
    return 0;
}