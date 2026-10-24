#include "NKMath/NkQuat.h"
#include "NKMath/NkMat.h"
#include "NKMath/NkAngle.h"
#include <cstdio>

using namespace nkentseu;
using namespace nkentseu::math;

// Calcul a la main (tete qui leve les yeux de 30 degres puis tourne de 45) :
//   tangage seul : (0, 0, -1) -> (0, 0.5, -0.8660)
//   puis lacet 45 : (-0.6124, 0.5, -0.6124)    => composante y = sin 30 = 0.5
// Ordre inverse (lacet puis tangage) : (-0.7071, 0.3536, -0.6124)  => y = sin30 x cos45 = 0.3536

int main() {
    const float lacetDeg = 45.f, tangageDeg = 30.f;
    const NkVec3f avant(0.f, 0.f, -1.f);

    const NkQuatf qLacet   = NkQuatf::RotateY(NkAngle(lacetDeg));
    const NkQuatf qTangage = NkQuatf::RotateX(NkAngle(tangageDeg));

    NkVec3f a = (qLacet * qTangage) * avant;      // lacet * tangage
    NkVec3f b = (qTangage * qLacet) * avant;      // tangage * lacet

    const NkMat4f rotation = NkMat4f::RotationY(NkAngle(lacetDeg)) *
                             NkMat4f::RotationX(NkAngle(tangageDeg));
    const NkQuatf q = NkQuatf(rotation).Normalized();
    NkVec3f c = q * avant;                         // chemin du simulateur : matrices

    std::printf("lacet*tangage : (%.4f, %.4f, %.4f)\n", a.x, a.y, a.z);
    std::printf("tangage*lacet : (%.4f, %.4f, %.4f)\n", b.x, b.y, b.z);
    std::printf("matrices : (%.4f, %.4f, %.4f)\n", c.x, c.y, c.z);
    return 0;
}