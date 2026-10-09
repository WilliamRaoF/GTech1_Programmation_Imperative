// Challenge jour 1 : grille 3 x 3 et carre magique normal.
#include <iostream>

constexpr int ORDRE = 3; // Variable constante déterminée à la compilation

bool lireNombre(int& nombre) {
    while (true) {
        if (std::cin >> nombre) {
            if (nombre >= -100 && nombre <= 100) return true;
            std::cout << "Valeur attendue entre -100 et 100 : ";
        }
        else {
            if (std::cin.eof() || std::cin.bad()) return false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Saisir un entier : ";
        }
    }
}

int main() {
    int grille[ORDRE][ORDRE] = {};
    for (int ligne = 0; ligne < ORDRE; ++ligne) {
        for (int colonne = 0; colonne < ORDRE; ++colonne) {
            std::cout << "Case [" << ligne << "][" << colonne << "] : ";
            if (!lireNombre(grille[ligne][colonne])) return 1;
        }
    }

    int sommesLignes[ORDRE] = {};
    int sommesColonnes[ORDRE] = {};
    int diagonalePrincipale = 0;
    int diagonaleSecondaire = 0;
    bool nombresDe1a9 = true;
    bool sansDoublon = true;
    bool vus[10] = {}; // Indices 1 a 9 utilises pour le bonus.

    std::cout << "\nGrille :\n";
    for (int ligne = 0; ligne < ORDRE; ++ligne) {
        for (int colonne = 0; colonne < ORDRE; ++colonne) {
            const int valeur = grille[ligne][colonne];
            std::cout << valeur << '\t';
            sommesLignes[ligne] += valeur;
            sommesColonnes[colonne] += valeur;

            // Ne jamais indexer vus avec un nombre hors de 1 a 9.
            if (valeur < 1 || valeur > 9) {
                nombresDe1a9 = false;
            }
            else {
                vus[valeur] = true;
            }

            // Comparer avec toutes les cases precedentes : detecte aussi
            // des doublons de valeurs negatives ou superieures a 9.
            const int position = ligne * ORDRE + colonne;
            for (int precedent = 0; precedent < position; ++precedent) {
                if (grille[precedent / ORDRE][precedent % ORDRE] == valeur) {
                    sansDoublon = false;
                }
            }
        }
        std::cout << '\n';
        diagonalePrincipale += grille[ligne][ligne];
        diagonaleSecondaire += grille[ligne][ORDRE - 1 - ligne];
    }

    const int reference = sommesLignes[0];
    bool sommesEgales = true;
    for (int i = 0; i < ORDRE; ++i) {
        std::cout << "Somme ligne " << i << " : " << sommesLignes[i] << '\n';
        std::cout << "Somme colonne " << i << " : " << sommesColonnes[i] << '\n';
        if (sommesLignes[i] != reference || sommesColonnes[i] != reference) {
            sommesEgales = false;
        }
    }
    bool tousPresents = true;
    for (int nombre = 1; nombre <= 9; ++nombre) {
        if (!vus[nombre]) tousPresents = false;
    }
    const bool diagonalesEgales = diagonalePrincipale == reference
        && diagonaleSecondaire == reference;
    const bool magiqueNormal = sommesEgales && diagonalesEgales
        && nombresDe1a9 && sansDoublon && tousPresents;

    std::cout << "Diagonale principale : " << diagonalePrincipale << '\n';
    std::cout << "Diagonale secondaire : " << diagonaleSecondaire << '\n';
    std::cout << std::boolalpha;
    std::cout << "Lignes et colonnes de meme somme : " << sommesEgales << '\n';
    std::cout << "Diagonales de meme somme : " << diagonalesEgales << '\n';
    std::cout << "Sans doublon : " << sansDoublon << '\n';
    std::cout << "Carre magique normal : " << magiqueNormal << '\n';
    return 0;
}
// Test : 8 1 6 / 3 5 7 / 4 9 2 -> toutes les sommes valent 15,
// et Carre magique normal : true. Neuf zeros -> normal : false.
