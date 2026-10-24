#include "NKMath/NkQuat.h"
#include "NKMath/NkAngle.h"
#include <cmath>
#include <cstdio>

using namespace nkentseu;
using namespace nkentseu::math;

struct Pos { float x, y, z; };

struct Yeux { Pos gaucheTete, droitTete, gaucheMonde, droitMonde; };

// Droite de la tete : image de +X par l'orientation q.
// Formule du quaternion unitaire : v' = v + 2w(u x v) + 2 u x (u x v), avec v = (1, 0, 0).
static Pos Droite(const NkQuatf& q) {
    const float ux = q.vector.x, uy = q.vector.y, uz = q.vector.z, w = q.scalar;
    const float cx = 0.f, cy = uz, cz = -uy;                       // u x v
    const float dx = uy * cz - uz * cy;                            // u x (u x v)
    const float dy = uz * cx - ux * cz;
    const float dz = ux * cy - uy * cx;
    return { 1.f + 2.f * w * cx + 2.f * dx,
             2.f * w * cy + 2.f * dy,
             2.f * w * cz + 2.f * dz };
}

static Pos Decaler(const Pos& p, const Pos& axe, float d) {
    return { p.x + axe.x * d, p.y + axe.y * d, p.z + axe.z * d };
}

static Yeux Calculer(const Pos& tete, const NkQuatf& orientation, float ipd) {
    const float demiEcart = ipd * 0.5f;
    const Pos droiteTete = Droite(orientation);
    const Pos droiteMonde = { 1.f, 0.f, 0.f };
    Yeux y;
    y.gaucheTete  = Decaler(tete, droiteTete, -demiEcart);
    y.droitTete   = Decaler(tete, droiteTete,  demiEcart);
    y.gaucheMonde = Decaler(tete, droiteMonde, -demiEcart);
    y.droitMonde  = Decaler(tete, droiteMonde,  demiEcart);
    return y;
}

static float EcartMm(const Pos& a, const Pos& b) {
    const float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz) * 1000.f;
}

static void Ligne(const char* nom, const char* methode, const Pos& g, const Pos& d) {
    std::printf("%s, %s : G (%.4f, %.4f, %.4f) D (%.4f, %.4f, %.4f)\n",
                nom, methode, g.x, g.y, g.z, d.x, d.y, d.z);
}

int main() {
    const Pos tete = { 0.30f, 1.70f, 1.20f };
    const float ipd = 0.063f;

    const char* noms[3] = { "neutre", "roulis 30", "lacet 90" };
    const Yeux yeux[3] = {
        Calculer(tete, NkQuatf::Identity(), ipd),
        Calculer(tete, NkQuatf::RotateZ(NkAngle(30.f)), ipd),
        Calculer(tete, NkQuatf::RotateY(NkAngle(90.f)), ipd)
    };

    for (int i = 0; i < 3; ++i) {
        Ligne(noms[i], "tete", yeux[i].gaucheTete, yeux[i].droitTete);
        Ligne(noms[i], "monde", yeux[i].gaucheMonde, yeux[i].droitMonde);
    }
    for (int i = 0; i < 3; ++i) {
        std::printf("%s : ecart %.1f mm\n", noms[i], EcartMm(yeux[i].gaucheTete, yeux[i].gaucheMonde));
    }
    return 0;
}