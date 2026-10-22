#include "NKImage/Core/NkImage.h"
#include "NKTime/NkChrono.h"
#include <fstream>
#include <iostream>

using namespace nkentseu;

struct Filtre { const char* nom; NkResizeFilter f; const char* png; };

int main() {
    NkImage photo;
    if (!photo.Load("photo.jpg")) {
        std::cout << "Impossible de charger photo.jpg\n";
        return 1;
    }

    // Source : la photo reduite/agrandie en 2048 x 2048
    NkImage source = photo.Resize(2048, 2048, NkResizeFilter::NK_BILINEAR);
    std::cout << "source : " << source.Width() << " x " << source.Height() << "\n";

    const Filtre filtres[4] = {
        {"NK_NEAREST",  NkResizeFilter::NK_NEAREST,  "nearest.png"},
        {"NK_BILINEAR", NkResizeFilter::NK_BILINEAR, "bilinear.png"},
        {"NK_BICUBIC",  NkResizeFilter::NK_BICUBIC,  "bicubic.png"},
        {"NK_LANCZOS3", NkResizeFilter::NK_LANCZOS3, "lanczos3.png"},
    };

    NkImage resultats[4];
    long long moyennes[4];
    const int REPETITIONS = 20;

    for (int i = 0; i < 4; ++i) {
        long long total = 0;
        for (int r = 0; r < REPETITIONS; ++r) {
            NkChrono chrono;
            NkImage reduit = source.Resize(256, 256, filtres[i].f);
            total += chrono.Elapsed().ToMicroseconds();
            if (r == REPETITIONS - 1) resultats[i] = std::move(reduit);
        }
        moyennes[i] = total / REPETITIONS;
        resultats[i].SavePNG(filtres[i].png);
    }

    // Comparaison au pixel pres avec le bilineaire (indice 1)
    std::ofstream out("mesures.txt");
    for (int i = 0; i < 4; ++i) {
        long long diff = 0;
        for (int y = 0; y < 256; ++y)
            for (int x = 0; x < 256; ++x)
                if (resultats[i].GetPixel(x, y) != resultats[1].GetPixel(x, y)) ++diff;
        out << filtres[i].nom << " : " << moyennes[i]
            << " us, differences : " << diff << "\n";
    }
    return 0;
}