#include "NKMath/NkQuat.h"
#include "NKMath/NkAngle.h"
#include <cmath>
#include <cstdio>

using namespace nkentseu;
using namespace nkentseu::math;

static const double kPi = 3.14159265358979323846;
static const double kPeriode = 1.0 / 72.0;
static const double kDebutGeste = 1.0;
static const int kNbPoses = 216;                 // trois secondes a 72 Hz

// Un quart de tour en 400 ms, depart et arrivee doux.
static double Lacet(double t) {                  // t depuis le debut, lacet en degres
    const double amplitude = 90.0, duree = 0.400;
    if (t <= 0.0) return 0.0;
    if (t >= duree) return amplitude;
    return amplitude * 0.5 * (1.0 - std::cos(kPi * t / duree));
}

static NkQuatf Pose(double t) {
    return NkQuatf::RotateY(NkAngle(static_cast<float>(Lacet(t - kDebutGeste))));
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

static double AngleDeg(const NkQuatf& a, const NkQuatf& b) {
    return (b * a.Conjugate()).Normalized().Angle().Deg();
}

// ---- Tableau circulaire de 64 poses, comme le simulateur du moteur ----
struct Echantillon {
    double temps;
    NkQuatf pose;
    NkVec3f vitesse;
};

struct Historique {
    static const unsigned kMax = 64u;
    Echantillon s[kMax];
    unsigned tete = 0u;       // le plus recent
    unsigned compte = 0u;

    void Ajouter(const Echantillon& e) {
        tete = (compte == 0u) ? 0u : (tete + 1u) % kMax;
        s[tete] = e;
        if (compte < kMax) ++compte;
    }

    const Echantillon& EchantillonA(double now, double latence) const {
        if (latence <= 0.0 || compte <= 1u) {
            return s[tete];
        }
        const double cible = now - latence;
        unsigned index = tete;
        for (unsigned i = 0u; i < compte; ++i) {
            if (s[index].temps <= cible) {
                return s[index];
            }
            index = (index + kMax - 1u) % kMax;
        }
        return s[(tete + kMax - (compte - 1u)) % kMax];   // le plus vieux disponible
    }
};

static void Remplir(Historique& h, int i, NkQuatf& prec) {
    const double t = i * kPeriode;
    const NkQuatf q = Pose(t);
    Echantillon e;
    e.temps = t;
    e.pose = q;
    e.vitesse = (i == 0) ? NkVec3f(0.f, 0.f, 0.f)
                         : VitesseAngulaire(prec, q, static_cast<float>(kPeriode));
    h.Ajouter(e);
    prec = q;
}

// Pose predite a l'instant 'quand' ; dtUtilise rend l'horizon reellement applique.
static NkQuatf Predire(const Echantillon& e, double quand, bool borne, double& dtUtilise) {
    float dt = static_cast<float>(quand - e.temps);
    if (borne) {
        dt = std::fmax(-0.1f, std::fmin(0.1f, dt));
    }
    dtUtilise = dt;
    return Extrapoler(e.pose, e.vitesse, dt);
}

static double LacetDeg(const NkQuatf& q) {
    return 2.0 * std::atan2(static_cast<double>(q.y), static_cast<double>(q.w)) * 180.0 / kPi;
}

// Erreurs de t = 1 s a t = 1,9 s pour une latence donnee (prediction bornee).
static void MesurerLatence(double latence, double r[4]) {
    Historique h;
    NkQuatf prec = Pose(0.0);
    double sommeA = 0.0, maxA = 0.0, sommeS = 0.0, maxS = 0.0;
    int n = 0;
    for (int i = 0; i < kNbPoses; ++i) {
        Remplir(h, i, prec);
        const double t = i * kPeriode;
        if (t < 1.0 - 1e-9 || t > 1.9 + 1e-9) continue;
        const Echantillon& e = h.EchantillonA(t, latence);
        const NkQuatf vraie = Pose(t + kPeriode);          // instant d'affichage
        double dt = 0.0;
        const double avec = AngleDeg(vraie, Predire(e, t + kPeriode, true, dt));
        const double sans = AngleDeg(vraie, e.pose);
        sommeA += avec; sommeS += sans;
        if (avec > maxA) maxA = avec;
        if (sans > maxS) maxS = sans;
        ++n;
    }
    r[0] = sommeA / n; r[1] = maxA; r[2] = sommeS / n; r[3] = maxS;
}

// Latence d'une seconde : l'image dont l'echantillon est le plus proche de 1,2 s.
static void TesterBorne(bool borne) {
    Historique h;
    NkQuatf prec = Pose(0.0);
    double meilleur = 1e9, quandMeilleur = 0.0;
    Echantillon e0 = {};
    bool trouve = false;
    for (int i = 0; i < kNbPoses; ++i) {
        Remplir(h, i, prec);
        const double t = i * kPeriode;
        const Echantillon& e = h.EchantillonA(t, 1.0);
        const double ecart = std::fabs(e.temps - 1.2);
        if (ecart < meilleur) {
            meilleur = ecart;
            quandMeilleur = t + kPeriode;
            e0 = e;
            trouve = true;
        }
    }
    if (!trouve) return;
    double dt = 0.0;
    const NkQuatf predite = Predire(e0, quandMeilleur, borne, dt);
    const NkQuatf vraie = Pose(quandMeilleur);
    std::printf("%s : echantillon a %.4f s, horizon %.1f ms, predit %.1f deg, vrai %.1f deg\n",
                borne ? "avec borne" : "sans borne", e0.temps, dt * 1000.0,
                LacetDeg(predite), LacetDeg(vraie));
}

int main() {
    const double latencesMs[5] = { 0.0, 10.0, 20.0, 40.0, 80.0 };
    std::FILE* csv = std::fopen("courbe.csv", "w");
    for (int k = 0; k < 5; ++k) {
        double r[4];
        MesurerLatence(latencesMs[k] / 1000.0, r);
        std::printf("latence %.0f ms : avec %.4f deg (max %.4f), sans %.4f deg (max %.4f)\n",
                    latencesMs[k], r[0], r[1], r[2], r[3]);
        if (csv) std::fprintf(csv, "%.0f,%.6f,%.6f\n", latencesMs[k], r[0], r[2]);
    }
    if (csv) std::fclose(csv);
    TesterBorne(false);
    TesterBorne(true);
    return 0;
}