
#include "NKWindow/NKWindow.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKTime/NkChrono.h"
#include <chrono>
#include <cstdio>
#include <thread>

using namespace nkentseu;

int main() {
    NkWindowConfig config;
    config.title = "Accumuler puis vider";
    config.width = 1280;
    config.height = 720;
    NkWindow fenetre(config);
    if (!fenetre.IsValid()) return 1;

    fenetre.ShowMouse(false);
    fenetre.CaptureMouse(true);

    const float sens = 0.002f;               // radians par compte du capteur
    const float RAD2DEG = 57.2957795f;
    float lacLu = 0.f, lacVide = 0.f, lacSans = 0.f;
    float accum = 0.f, accumSans = 0.f;      // accumulateurs de la 2e et 3e version
    NkChrono chrono;
    int prochaine = 1;
    bool fin = false;

    while (fenetre.IsOpen() && !fin) {
        // 1) Evenements : on AJOUTE, on ne vide jamais ici
        NkEvent* ev = NkEvents().PollEvent();
        while (ev) {
            if (auto* r = ev->As<NkMouseRawEvent>()) {
                accum     += (float)r->GetDeltaX();
                accumSans += (float)r->GetDeltaX();
            }
            if (auto* k = ev->As<NkKeyPressEvent>()) {
                if (k->GetKey() == NkKey::NK_ESCAPE) fin = true;     // Echap : quitter
            }
            ev = NkEvents().PollEvent();
        }

        // 2) Une fois par image : on LIT, puis on VIDE
        lacLu   += (float)NkInput.MouseRawDeltaX() * sens;           
        lacVide += accum * sens;      accum = 0.f;                  
        lacSans += accumSans * sens;                                 

        double t = chrono.Elapsed().ToMilliseconds() / 1000.0;
        if (t >= prochaine) {
            std::printf("t = %.1f s, lu = %.1f, vide = %.1f, sans vidage = %.1f\n",
                        t, lacLu * RAD2DEG, lacVide * RAD2DEG, lacSans * RAD2DEG);
            std::fflush(stdout);
            ++prochaine;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(14));  // environ 72 images par seconde
    }

    fenetre.ShowMouse(true);         
    fenetre.CaptureMouse(false);
    return 0;
}