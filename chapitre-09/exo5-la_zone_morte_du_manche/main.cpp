#include <cstdio>
#include <iostream>

int main() {
    long long seuil = 0, maximum = 0;
    std::cin >> seuil >> maximum;
    int n = 0;
    std::cin >> n;
    int morts = 0;
    for (int i = 0; i < n; ++i) {
        long long v = 0;
        std::cin >> v;
        const long long a = v < 0 ? -v : v;
        long long vitesse = 0;
        if (a < seuil) {
            ++morts;
        } else {
            const long long reste = a - seuil;
            const long long course = 1000 - seuil;
            if (course > 0) {
                vitesse = maximum * reste * reste / (course * course);
            }
            if (v < 0) vitesse = -vitesse;
        }
        std::printf("%lld\n", vitesse);
    }
    std::printf("MORTS %d\n", morts);
    return 0;
}