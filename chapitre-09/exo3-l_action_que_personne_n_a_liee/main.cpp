#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int a = 0;
    std::cin >> a;
    std::vector<std::string> noms(a), usages(a);
    for (int i = 0; i < a; ++i) {
        std::cin >> noms[i] >> usages[i];
    }
    int l = 0;
    std::cin >> l;
    std::vector<std::string> fournis(l);
    for (int i = 0; i < l; ++i) {
        std::cin >> fournis[i];
    }
    int mortes = 0;
    for (int i = 0; i < a; ++i) {
        bool active = false;
        for (int j = 0; j < l; ++j) {
            if (fournis[j] == usages[i]) {
                active = true;
                break;
            }
        }
        if (!active) ++mortes;
        std::printf("%s %s\n", noms[i].c_str(), active ? "ACTIVE" : "MORTE");
    }
    std::printf("MORTES %d\n", mortes);
    return 0;
}