#include "NKMath/NkQuat.h"
#include "NKMath/NkMat.h"
#include "NKMath/NkAngle.h"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace nkentseu;
using namespace nkentseu::math;

static NkQuatf Orientation(float lacetRad, float tangageRad) {
    const NkMat4f rotation = NkMat4f::RotationY(NkAngle::FromRad(lacetRad)) *
                             NkMat4f::RotationX(NkAngle::FromRad(tangageRad));
    return NkQuatf(rotation).Normalized();
}

static NkVec3f VitesseAngulaire(const NkQuatf& from, const NkQuatf& to, float dtSeconds) {
    if (dtSeconds <= 0.f) {
        return NkVec3f(0.f, 0.f, 0.f);
    }
    NkQuatf delta = (to * from.Conjugate()).Normalized();
    if (delta.w < 0.f) {
        delta = NkQuatf(-delta.x, -delta.y, -delta.z, -delta.w);
    }
    const float angleRad = delta.Angle().Rad();
    if (angleRad <= 1e-6f) {
        return NkVec3f(0.f, 0.f, 0.f);
    }
    return delta.Axis() * (angleRad / dtSeconds);
}

static NkQuatf Extrapoler(const NkQuatf& orientation, const NkVec3f& vitesse, float dtSeconds) {
    const float speedRad = vitesse.Len();
    if (speedRad > 1e-6f) {
        const NkVec3f axis = vitesse * (1.f / speedRad);
        const NkQuatf delta(NkAngle::FromRad(speedRad * dtSeconds), axis);
        return (delta * orientation).Normalized();
    }
    return orientation;
}

static float AngleDeg(const NkQuatf& a, const NkQuatf& b) {
    return (b * a.Conjugate()).Normalized().Angle().Deg();
}

int main() {
    const char* h = std::getenv("MASALLE_HZ");
    const double hz = h ? std::atof(h) : 0.0;
    if (hz <= 1.0) {
        std::printf("lancez avec MASALLE_HZ=<frequence de l'ecran>\n");
        return 1;
    }
    const float periode = static_cast<float>(1.0 / hz);
    const int nVoulues = 1000;
    const float sensibilite = 0.0022f;

    const int cx = GetSystemMetrics(SM_CXSCREEN) / 2;
    const int cy = GetSystemMetrics(SM_CYSCREEN) / 2;
    std::fprintf(stderr, "Bougez la souris comme pour regarder autour de vous. Depart dans 3 s.\n");
    Sleep(3000);
    SetCursorPos(cx, cy);

    float lacet = 0.f, tangage = 0.f;
    NkQuatf prev = Orientation(0.f, 0.f), pred = prev;
    bool aPred = false;
    int n = 0, immobiles = 0;
    double sommeAvec = 0, sommeSans = 0, maxAvec = 0, maxSans = 0;

    auto prochain = std::chrono::steady_clock::now();
    for (int i = 0; n < nVoulues; ++i) {
        prochain += std::chrono::duration_cast<std::chrono::steady_clock::duration>(
            std::chrono::duration<double>(periode));
        while (std::chrono::steady_clock::now() < prochain) {}

        POINT p;
        GetCursorPos(&p);
        const int dx = p.x - cx, dy = p.y - cy;
        SetCursorPos(cx, cy);

        lacet   -= dx * sensibilite;
        tangage -= dy * sensibilite;
        const float limite = 1.55f;                       // ~89 deg, evite de passer par la verticale
        if (tangage >  limite) tangage =  limite;
        if (tangage < -limite) tangage = -limite;

        const NkQuatf q = Orientation(lacet, tangage);
        if (i > 0) {
            if (aPred) {
                const double avec = AngleDeg(pred, q);    // prediction faite a l'image d'avant
                const double sans = AngleDeg(prev, q);    // image d'avant prise telle quelle
                sommeAvec += avec; sommeSans += sans;
                if (avec > maxAvec) maxAvec = avec;
                if (sans > maxSans) maxSans = sans;
                if (dx == 0 && dy == 0) ++immobiles;
                ++n;
            }
            const NkVec3f v = VitesseAngulaire(prev, q, periode);
            pred = Extrapoler(q, v, periode);
            aPred = true;
        }
        prev = q;
    }
    std::printf("avec prediction : moyenne %.4f deg, max %.4f deg, sur %d images\n", sommeAvec / n, maxAvec, n);
    std::printf("sans prediction : moyenne %.4f deg, max %.4f deg, sur %d images\n", sommeSans / n, maxSans, n);
    std::fprintf(stderr, "images immobiles (dx = dy = 0) : %d sur %d\n", immobiles, n);
    return 0;
}