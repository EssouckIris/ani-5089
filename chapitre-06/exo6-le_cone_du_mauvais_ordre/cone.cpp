#include "NKMath/NkQuat.h"
#include "NKMath/NkMat.h"
#include "NKMath/NkAngle.h"
#include <cmath>
#include <cstdio>

using namespace nkentseu;
using namespace nkentseu::math;

// Camera de la salle (a brancher dans la boucle de rendu) :
//   cd.target = cd.position + q * NkVec3f(0.f, 0.f, -1.f);
//   cd.up     = q * NkVec3f(0.f, 1.f, 0.f);     // le haut vient du quaternion

static float Hauteur(const NkVec3f& regard) {
    return std::asin(regard.y) * 180.0f / 3.14159265f;   // angle au-dessus de l'horizon
}

int main() {
    const float tangageDeg = 30.f;
    const NkVec3f avant(0.f, 0.f, -1.f);
    const float lacets[5] = {0.f, 45.f, 90.f, 135.f, 180.f};

    for (int ordre = 0; ordre < 2; ++ordre) {
        const char* nom = ordre == 0 ? "lacet*tangage" : "tangage*lacet";
        for (int i = 0; i < 5; ++i) {
            NkQuatf qLacet   = NkQuatf::RotateY(NkAngle(lacets[i]));
            NkQuatf qTangage = NkQuatf::RotateX(NkAngle(tangageDeg));
            NkQuatf q = (ordre == 0) ? (qLacet * qTangage) : (qTangage * qLacet);
            NkVec3f regard = q * avant;
            std::printf("%s, lacet %g : hauteur %.2f deg\n", nom, lacets[i], Hauteur(regard));
        }
    }
    return 0;
}