#include "NKMath/NkQuat.h"
#include "NKMath/NkMat.h"
#include "NKMath/NkAngle.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace nkentseu;
using namespace nkentseu::math;

// Vitesse angulaire entre deux poses, comme dans le module de realite virtuelle.
NkVec3f VitesseAngulaire(const NkQuatf &from, const NkQuatf &to, float32 dtSeconds) {
	if (dtSeconds <= 0.f) {
		return NkVec3f(0.f, 0.f, 0.f);
	}
	NkQuatf delta = (to * from.Conjugate()).Normalized();
	const float32 angleRad = delta.Angle().Rad();
	if (angleRad <= 1e-6f) {
		return NkVec3f(0.f, 0.f, 0.f);
	}
	return delta.Axis() * (angleRad / dtSeconds);
}

static NkQuatf Orientation(float lacetRad, float tangageRad) {
	const NkMat4f rotation = NkMat4f::RotationY(NkAngle::FromRad(lacetRad)) *
							 NkMat4f::RotationX(NkAngle::FromRad(tangageRad));
	return NkQuatf(rotation).Normalized();
}

int main() {
	// MASALLE_TOUR = vitesse du tour programme, en degres par seconde (20)
	const char *t = getenv("MASALLE_TOUR");
	const double tour = t ? atof(t) : 0.0;
	if (tour <= 0.0) {
		std::printf("lancez avec MASALLE_TOUR=20\n");
		return 1;
	}
	const char *h = getenv("MASALLE_HZ");
	const double hz = (h && atof(h) > 1.0) ? atof(h) : 72.0;
	const char *g = getenv("MASALLE_TANGAGE");
	const double tangageDeg = g ? atof(g) : 0.0;

	const double PI = 3.14159265358979;
	const double dt = 1.0 / hz;
	const int nImages = (int)std::ceil(360.0 / (tour * dt)) + 1;   // un tour complet

	NkQuatf precedente = Orientation(0.f, (float)(tangageDeg * PI / 180.0));
	for (int i = 0; i < nImages; ++i) {
		const double lacetDeg = tour * dt * (double)i;
		const NkQuatf courante = Orientation((float)(lacetDeg * PI / 180.0),
											 (float)(tangageDeg * PI / 180.0));
		const NkVec3f v = (i == 0) ? NkVec3f(0.f, 0.f, 0.f)
								   : VitesseAngulaire(precedente, courante, (float)dt);
		const NkQuatf d = (courante * precedente.Conjugate()).Normalized();
		const double k = 180.0 / PI;   // rad/s -> deg/s
		std::printf("image %d : lacet = %.2f deg, vitesse = (%.2f, %.2f, %.2f) deg/s, delta.w = %.6f\n",
					i, lacetDeg, v.x * k, v.y * k, v.z * k, (double)d.w);
		precedente = courante;
	}
	return 0;
}
