#include "NKMath/NkQuat.h"
#include "NKMath/NkMat.h"
#include "NKMath/NkAngle.h"
#include "NKTime/NkChrono.h"
#include <cmath>
#include <cstdio>

using namespace nkentseu;
using namespace nkentseu::math;

static NkQuatf ParMatrices(float lacetDeg, float tangageDeg) {
    const NkMat4f rotation = NkMat4f::RotationY(NkAngle(lacetDeg)) *
                             NkMat4f::RotationX(NkAngle(tangageDeg));
    return NkQuatf(rotation).Normalized();
}

static NkQuatf ParQuaternions(float lacetDeg, float tangageDeg) {
    // meme ordre que les matrices : lacet * tangage
    return (NkQuatf::RotateY(NkAngle(lacetDeg)) * NkQuatf::RotateX(NkAngle(tangageDeg))).Normalized();
}

int main() {
    // 1) Meme quaternion sur un angle ? (q et -q representent la meme rotation)
    NkQuatf a = ParMatrices(45.f, 30.f), b = ParQuaternions(45.f, 30.f);
    std::printf("matrices   : (%.5f, %.5f, %.5f, %.5f)\n", a.vector.x, a.vector.y, a.vector.z, a.scalar);
    std::printf("quaternion : (%.5f, %.5f, %.5f, %.5f)\n", b.vector.x, b.vector.y, b.vector.z, b.scalar);

    // 2) Chronometrage : un million d'iterations, trois mesures par version
    const int N = 1000000;
    for (int essai = 1; essai <= 3; ++essai) {
        double somme = 0;
        NkChrono c;
        for (int i = 0; i < N; ++i) {
            NkQuatf q = ParMatrices((i % 3600) * 0.1f, 30.f);
            somme += q.vector.x + q.vector.y + q.vector.z + q.scalar;
        }
        double ms1 = c.Elapsed().ToMilliseconds();

        somme = 0;
        NkChrono c2;
        for (int i = 0; i < N; ++i) {
            NkQuatf q = ParQuaternions((i % 3600) * 0.1f, 30.f);
            somme += q.vector.x + q.vector.y + q.vector.z + q.scalar;
        }
        double ms2 = c2.Elapsed().ToMilliseconds();
        std::printf("matrices : %.1f ms | quaternions : %.1f ms | somme %.3f\n", ms1, ms2, somme);
    }
    return 0;
}