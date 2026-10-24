#include "NKWindow/NKWindow.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKTime/NkChrono.h"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <thread>

using namespace nkentseu;

int main() {
    NkWindowConfig config;
    config.title = "Derive";
    config.width = 1280;
    config.height = 720;
    NkWindow fenetre(config);
    if (!fenetre.IsValid()) return 1;
    fenetre.ShowMouse(false);
    fenetre.CaptureMouse(true);

    // Tete fautive, voulue : on lit le deplacement brut a chaque image, sans rien accumuler
    float lacet = 0.f, tangage = 0.f;
    const float sensibilite = 0.002f;      // radians par compte du capteur
    const float RAD2DEG = 57.2957795f;

    NkChrono chrono;
    long images = 0;
    int prochaine = 1;                     // prochaine seconde a imprimer

    while (fenetre.IsOpen()) {
        NkEvents().PollEvents();

        lacet   += NkInput.MouseRawDeltaX() * sensibilite;
        tangage += NkInput.MouseRawDeltaY() * sensibilite;
        ++images;

        double t = chrono.Elapsed().ToMilliseconds() / 1000.0;
        if (t >= prochaine) {
            std::printf("t = %.1f s, images = %ld, brut = %d, lacet = %.1f deg\n",
                        t, images, (int)NkInput.MouseRawDeltaX(), lacet * RAD2DEG);
            std::fflush(stdout);
            ++prochaine;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(14));   // environ 72 images par seconde
    }
    return 0;
}