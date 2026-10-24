#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Convention de la salle : avant = -Z, haut = +Y, repere de la main droite.
// Pour tester l'epreuve qui sait dire non : mettre -1.0f ici, lancer, puis remettre 1.0f.
static const float kSigneLacet = -1.0f;

struct Vec3 { float x, y, z; };

struct Tete {
    float lacet = 0.f;      // radians
    float tangage = 0.f;    // radians
    Vec3 position{0.f, 0.f, 0.f};   // metres

    // Pose la tete directement, sans passer par la souris
    void PoserTete(float lacetRad, float tangageRad, Vec3 pos) {
        lacet = lacetRad;
        tangage = tangageRad;
        position = pos;
    }

    Vec3 Regard() const {
        return { -kSigneLacet * std::sin(lacet) * std::cos(tangage),
                 std::sin(tangage),
                 -std::cos(lacet) * std::cos(tangage) };
    }
};

static bool Proche(float a, float b) { return std::fabs(a - b) < 1e-4f; }

static bool Epreuve(const char* nom, float lacetDeg, float tangageDeg, Vec3 attendu) {
    const float PI = 3.14159265358979f;
    Tete t;
    t.PoserTete(lacetDeg * PI / 180.f, tangageDeg * PI / 180.f, {0.f, 1.7f, 0.f});
    Vec3 o = t.Regard();
    bool ok = Proche(o.x, attendu.x) && Proche(o.y, attendu.y) && Proche(o.z, attendu.z);
    std::printf("%s : attendu (%.3f, %.3f, %.3f), obtenu (%.3f, %.3f, %.3f), %s\n",
                nom, attendu.x, attendu.y, attendu.z, o.x, o.y, o.z, ok ? "OK" : "ECHEC");
    return ok;
}

static int LancerTest() {
    bool ok = true;
    // Les attendus sont ecrits a la main, deduits de la convention, pas recalcules avec Regard()
    ok &= Epreuve("lacet 90, tangage 0",   90.f,  0.f, {-1.f, 0.f,  0.f});
    ok &= Epreuve("lacet -90, tangage 0", -90.f,  0.f, { 1.f, 0.f,  0.f});
    ok &= Epreuve("lacet 180, tangage 0", 180.f,  0.f, { 0.f, 0.f,  1.f});
    ok &= Epreuve("lacet 0, tangage 45",    0.f, 45.f, { 0.f, 0.70711f, -0.70711f});
    return ok ? 0 : 1;
}

int main() {
    const char* v = std::getenv("MASALLE_TEST");
    if (v && std::strcmp(v, "1") == 0) {
        return LancerTest();       // le code de sortie dit si tout passe
    }
    std::printf("Mode normal : pas de salle dans ce programme.\n");
    return 0;
}