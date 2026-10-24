#include "NKWindow/NKWindow.h"
#include "NKEvent/NkKeyboardEvent.h"
#include <cstring>
#include <iostream>

using namespace nkentseu;

static void Reprendre(NkWindow& w, bool clip) {
    w.ShowMouse(false);
    w.CaptureMouse(true);
    if (clip) w.ClipMouseToClient(true);
    std::cout << "pointeur repris\n";
}

static void Rendre(NkWindow& w) {
    w.ShowMouse(true);
    w.CaptureMouse(false);
    w.ClipMouseToClient(false);
    std::cout << "pointeur rendu\n";
}

int main(int argc, char** argv) {
    // options : clip = ClipMouseToClient en plus ; sans-rendu = ne rend PAS a la fin
    bool clip = false, sansRendu = false;
    for (int i = 1; i < argc; ++i) {
        if (!std::strcmp(argv[i], "clip")) clip = true;
        if (!std::strcmp(argv[i], "sans-rendu")) sansRendu = true;
    }

    NkWindowConfig config;
    config.title = "Pointeur";
    config.width = 1280;
    config.height = 720;
    NkWindow fenetre(config);
    if (!fenetre.IsValid()) return 1;

    Reprendre(fenetre, clip);          // juste apres l'ouverture

    while (fenetre.IsOpen()) {
        NkEvent* ev = NkEvents().PollEvent();
        while (ev) {
            if (auto* k = ev->As<NkKeyPressEvent>()) {
                if (k->GetKey() == NkKey::NK_ESCAPE) Rendre(fenetre);          // rend
                if (k->GetKey() == NkKey::NK_E)      Reprendre(fenetre, clip); // reprend
            }
            ev = NkEvents().PollEvent();
        }
    }

    if (!sansRendu) Rendre(fenetre);   // toujours rendre avant de finir
    return 0;
}