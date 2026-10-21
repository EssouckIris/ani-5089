#include "NKImage/Core/NkImage.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace nkentseu;

static long TailleFichier(const std::string& chemin) {
    std::ifstream f(chemin, std::ios::binary | std::ios::ate);
    if (!f) return -1;
    return static_cast<long>(f.tellg());
}

template <typename F>
static void Mesurer(std::ofstream& out, const char* nom,
                    const std::string& fichier, F ecrire) {
    ecrire(fichier);
    long n = TailleFichier(fichier);
    NkImage relue;
    if (n >= 0 && relue.Load(fichier.c_str())) {
        out << nom << " : " << n << " octets, "
            << relue.Width() << " x " << relue.Height() << "\n";
    } else {
        out << nom << " : " << n << " octets, illisible\n";
    }
}

int main() {
    NkImage photo;
    if (!photo.Load("photo.jpg")) {
        std::cout << "Impossible de charger photo.jpg\n";
        return 1;
    }
    std::cout << "Photo : " << photo.Width() << " x " << photo.Height() << "\n";

    std::ofstream out("formats.txt");
    Mesurer(out, "png",  "sortie.png",  [&](const std::string& f) { photo.SavePNG(f.c_str()); });
    Mesurer(out, "jpeg", "sortie.jpg",  [&](const std::string& f) { photo.SaveJPEG(f.c_str()); });
    Mesurer(out, "bmp",  "sortie.bmp",  [&](const std::string& f) { photo.SaveBMP(f.c_str()); });
    Mesurer(out, "tga",  "sortie.tga",  [&](const std::string& f) { photo.SaveTGA(f.c_str()); });
    Mesurer(out, "qoi",  "sortie.qoi",  [&](const std::string& f) { photo.SaveQOI(f.c_str()); });
    return 0;
}