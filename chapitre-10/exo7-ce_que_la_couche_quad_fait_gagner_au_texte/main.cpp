#include <cstdio>
#include <iostream>
#include <string>

int main() {
    long long r1 = 0, r2 = 0, r3 = 0, seuil = 0;
    std::cin >> r1 >> r2 >> r3 >> seuil;
    int n = 0;
    std::cin >> n;
    int gagnes = 0, perdus = 0;
    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long pixels = 0;
        std::cin >> nom >> pixels;
        long long scene = pixels;
        scene = scene * r1 / 1000;
        scene = scene * r2 / 1000;
        scene = scene * r3 / 1000;
        const bool lisibleScene = scene >= seuil;
        const bool lisibleQuad = pixels >= seuil;
        if (!lisibleScene && lisibleQuad) ++gagnes;
        if (lisibleScene && !lisibleQuad) ++perdus;
        std::printf("%s %lld %lld %s %s\n", nom.c_str(), scene, pixels,
                    lisibleScene ? "LISIBLE" : "FLOU",
                    lisibleQuad ? "LISIBLE" : "FLOU");
    }
    std::printf("GAGNES %d\n", gagnes);
    std::printf("PERDUS %d\n", perdus);
    return 0;
}