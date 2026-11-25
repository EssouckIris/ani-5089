#include <cstdio>
#include <iostream>

int main() {
    int images = 0, trames = 0;
    std::cin >> images >> trames;
    int index = 0, rendues = 0;
    for (int i = 1; i <= trames; ++i) {
        int dessine = 0;
        std::cin >> dessine;
        if (dessine) {
            std::printf("%d OUI 1 %d\n", i, index);
            ++rendues;
            if (images > 0) {
                index = (index + 1) % images;
            }
        } else {
            std::printf("%d NON 0 -\n", i);
        }
    }
    std::printf("RENDUES %d\n", rendues);
    std::printf("FINS %d\n", trames);
    return 0;
}