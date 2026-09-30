#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <functional>
#include <sstream>

int main() {
    int N;
    std::cin >> N;

    std::map<std::string, std::vector<std::string>> dependances;
    std::set<std::string> tousLesModules;

    for (int i = 0; i < N; ++i) {
        std::string module;
        std::cin >> module;

        tousLesModules.insert(module);

        std::string ligne;
        std::getline(std::cin, ligne);

        std::istringstream iss(ligne);
        std::string besoin;

        while (iss >> besoin) {
            dependances[module].push_back(besoin);
        }
    }

    int M;
    std::cin >> M;

    std::vector<std::string> a_traiter;

    for (int i = 0; i < M; ++i) {
        std::string module;
        std::cin >> module;

        if (tousLesModules.insert(module).second) {
            a_traiter.push_back(module);
        }
    }

    // Trouver toutes les dépendances nécessaires
    for (std::size_t i = 0; i < a_traiter.size(); ++i) {
        const std::string& module = a_traiter[i];

        for (const std::string& besoin : dependances[module]) {
            if (tousLesModules.insert(besoin).second) {
                a_traiter.push_back(besoin);
            }
        }
    }

    // Nombre de modules qui dépendent de chaque module
    std::map<std::string, int> compte;

    for (const std::string& module : tousLesModules) {
        compte[module] = 0;
    }

    for (const std::string& module : tousLesModules) {
        for (const std::string& besoin : dependances[module]) {
            compte[besoin]++;
        }
    }

    // Les modules disponibles, dans l'ordre alphabétique
    std::priority_queue<
        std::string,
        std::vector<std::string>,
        std::greater<std::string>
    > disponibles;

    for (const std::string& module : tousLesModules) {
        if (compte[module] == 0) {
            disponibles.push(module);
        }
    }

    std::vector<std::string> resultat;

    while (!disponibles.empty()) {
        std::string module = disponibles.top();
        disponibles.pop();

        resultat.push_back(module);

        for (const std::string& besoin : dependances[module]) {
            compte[besoin]--;

            if (compte[besoin] == 0) {
                disponibles.push(besoin);
            }
        }
    }

    
    if (resultat.size() != tousLesModules.size()) {
        std::cout << "CYCLE\n";
        return 0;
    }

    for (const std::string& module : resultat) {
        std::cout << module << '\n';
    }

    return 0;
}