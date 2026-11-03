#include "NKMath/NkQuat.h"
#include "NKMath/NkAngle.h"
#include <cmath>
#include <cstdio>

using namespace nkentseu;
using namespace nkentseu::math;

static const double kPi = 3.14159265358979323846;

// Geste doux : depart et arrivee a vitesse nulle. Lacet en degres.
static double Lacet(double t, double amplitude, double duree) {
	if (t <= 0.0) return 0.0;
	if (t >= duree) return amplitude;
	return amplitude * 0.5 * (1.0 - std::cos(kPi * t / duree));
}

static NkQuatf Pose(double t, double amplitude, double duree) {
	return NkQuatf::RotateY(NkAngle(static_cast<float>(Lacet(t, amplitude, duree))));
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

// Erreur angulaire entre deux orientations, en degres. Calculee en double avec
// atan2 : Angle() en float ne distingue rien sous 0,04 degre (acos(1 - epsilon)).
static double AngleDeg(const NkQuatf& a, const NkQuatf& b) {
	const NkQuatf d = (b * a.Conjugate()).Normalized();
	const double s = std::sqrt((double)d.x * d.x + (double)d.y * d.y + (double)d.z * d.z);
	return 2.0 * std::atan2(s, std::fabs((double)d.w)) * 180.0 / kPi;
}

static void Geste(const char* nom, double amplitude, double dureeS) {
	const double periode = 1.0 / 72.0;
	const int n = static_cast<int>(dureeS / periode);   // poses pendant le geste
	double sommeAvec = 0.0, sommeSans = 0.0;
	int compte = 0;
	NkQuatf prec = Pose(0.0, amplitude, dureeS);
	for (int i = 1; i <= n; ++i) {
		const double t = i * periode;
		const NkQuatf q = Pose(t, amplitude, dureeS);
		const NkVec3f v = VitesseAngulaire(prec, q, static_cast<float>(periode));
		const NkQuatf predite = Extrapoler(q, v, static_cast<float>(periode));
		const NkQuatf vraie = Pose(t + periode, amplitude, dureeS);   // instant d'affichage
		sommeAvec += AngleDeg(vraie, predite);
		sommeSans += AngleDeg(vraie, q);
		++compte;
		prec = q;
	}
	const double avec = sommeAvec / compte, sans = sommeSans / compte;
	std::printf("%s (%.0f deg en %.0f ms) : avec %.4f deg, sans %.4f deg, rapport %.2f\n",
				nom, amplitude, dureeS * 1000.0, avec, sans, sans / avec);
}

int main() {
	Geste("lent", 45.0, 1.500);
	Geste("rapide", 90.0, 0.400);
	Geste("demi-tour", 180.0, 0.250);
	return 0;
}