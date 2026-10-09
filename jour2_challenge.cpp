// Challenge jour 2 : rotation sur place, sans second tableau ni allocation.
#include <iostream>

// Contrat : valeurs pointe sur taille entiers si taille > 0.
void inverserPortion(int* valeurs, int debut, int fin) {
    // debut et fin sont des indices inclusifs valides, ou une plage vide.
    while (debut < fin) {
        int temporaire = valeurs[debut];
        valeurs[debut] = valeurs[fin];
        valeurs[fin] = temporaire;
        ++debut;
        --fin;
    }
}

void rotationDroite(int* valeurs, int taille, int decalage) {
    // Le contrat demande taille et decalage non negatifs.
    // Les cas invalides sont ignores ici, sans acces au tableau.
    if (taille <= 1 || decalage < 0 || valeurs == nullptr) return;
    decalage %= taille; // Apres le traitement du tableau vide.
    if (decalage == 0) return;

    // {1,2,3,4,5}, k=2 :
    // {5,4,3,2,1} -> {4,5,3,2,1} -> {4,5,1,2,3}.
    inverserPortion(valeurs, 0, taille - 1);
    inverserPortion(valeurs, 0, decalage - 1);
    inverserPortion(valeurs, decalage, taille - 1);
}

void afficher(const int* valeurs, int taille) {
    for (int i = 0; i < taille; ++i) std::cout << valeurs[i] << ' ';
    std::cout << '\n';
}

int main() {
    int valeurs[5] = { 1, 2, 3, 4, 5 };
    int decalage = -1;
    while (true) {
        std::cout << "Decalage entier positif ou nul : ";
        if (std::cin >> decalage) {
            if (decalage >= 0) break;
            std::cout << "Le decalage doit etre positif ou nul.\n";
        }
        else {
            if (std::cin.eof() || std::cin.bad()) return 1;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Saisie non numerique.\n";
        }
    }
    std::cout << "Avant : ";
    afficher(valeurs, 5);
    rotationDroite(valeurs, 5, decalage);
    std::cout << "Apres : ";
    afficher(valeurs, 5);

    // Cas limites : aucun acces invalide.
    rotationDroite(nullptr, 0, decalage);
    int unique[1] = { 42 };
    rotationDroite(unique, 1, decalage);
    std::cout << "Un element : ";
    afficher(unique, 1);
    return 0;
}
// Tests : k=2 ou 7 -> 4 5 1 2 3 ; k=0 ou 5 -> 1 2 3 4 5.
// Chaque inversion parcourt au plus taille elements : temps O(taille),
// memoire supplementaire O(1), quel que soit le decalage saisi.
