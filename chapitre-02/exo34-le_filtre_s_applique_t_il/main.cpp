#include <iostream>
#include <string>
#include <map>
#include <sstream>

int main() {
    int V;
    std::cin >> V;

    std::map<std::string, std::string> machine;

    for (int i = 0; i < V; ++i) {
        std::string ligne;
        std::cin >> ligne;

        std::size_t position = ligne.find('=');

        std::string cle = ligne.substr(0, position);
        std::string valeur = ligne.substr(position + 1);

        machine[cle] = valeur;
    }

    int F;
    std::cin >> F;
    std::cin.ignore();

    for (int i = 0; i < F; ++i) {
        std::string condition;
        std::getline(std::cin, condition);

        std::istringstream iss(condition);
        std::string terme;
        bool filtreValide = true;

        while (iss >> terme) {
            // Enlever "&&" s'il apparaît comme séparateur
            if (terme == "&&") {
                continue;
            }

            bool inverse = false;

            if (terme[0] == '!') {
                inverse = true;
                terme = terme.substr(1);
            }

            std::size_t position = terme.find('=');

            std::string cle = terme.substr(0, position);
            std::string valeur = terme.substr(position + 1);

            bool termeVrai = false;

            auto it = machine.find(cle);

            if (it != machine.end()) {
                termeVrai = (it->second == valeur);
            }

            if (inverse) {
                termeVrai = !termeVrai;
            }

            if (!termeVrai) {
                filtreValide = false;
            }
        }

        if (filtreValide) {
            std::cout << "OUI\n";
        } else {
            std::cout << "NON\n";
        }
    }

    return 0;
}