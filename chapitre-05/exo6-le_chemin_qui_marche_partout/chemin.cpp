#include "NKImage/Core/NkImage.h"
#include "NKFileSystem/NkPath.h"
#include <iostream>

using namespace nkentseu;

int main() {
    // AVANT : chemin relatif, part du dossier de lancement
    NkImage avant;
    bool okAvant = avant.Load("murs/mur.jpg");
    std::cout << "avant : charge " << okAvant << ", " << avant.Width()
              << " x " << avant.Height() << "\n";

    // APRES : chemin trouve par le moteur
    auto chemin = NkPath::LocateResource("murs/mur.jpg");
    if (chemin.Empty()) {
        std::cout << "apres : LocateResource n'a rien trouve\n";
        return 1;
    }
    NkImage apres;
    bool okApres = apres.Load(chemin.CStr());
    std::cout << "apres : charge " << okApres << ", " << apres.Width()
              << " x " << apres.Height() << "\n";
    return 0;
}