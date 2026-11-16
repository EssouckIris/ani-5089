#include <cstdio>
#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;
    int fautes = 0;
    for (int i = 0; i < n; ++i) {
        std::string nom, intention, pose;
        std::cin >> nom >> intention >> pose;
        const char* verdict = "OK";
        if (intention == "TENIR" && pose == "AIM") {
            verdict = "FLOTTE";
            ++fautes;
        } else if (intention == "POINTER" && pose == "GRIP") {
            verdict = "PART DE TRAVERS";
            ++fautes;
        }
        std::printf("%s %s\n", nom.c_str(), verdict);
    }
    std::printf("FAUTES %d\n", fautes);
    return 0;
}