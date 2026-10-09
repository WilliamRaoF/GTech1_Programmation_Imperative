// Challenge jour 3 : tableau extensible manuel et suppression du dernier.
#include <iostream>

constexpr int LIMITE = 100; // Variable constante déterminée à la compilation

// Les references mettent a jour le pointeur et les compteurs de l'appelant.
// Contrat : 0 <= taille <= capacite <= LIMITE ; stockage valide.
bool ajouter(int*& donnees, int& taille, int& capacite, int valeur) {
    if (taille >= LIMITE) return false;
    if (taille == capacite) {
        int nouvelleCapacite = capacite == 0 ? 2 : capacite * 2;
        if (nouvelleCapacite > LIMITE) nouvelleCapacite = LIMITE;

        // Si new echoue, l'ancien tableau reste intact.
        int* nouveau = new int[nouvelleCapacite] {};
        for (int i = 0; i < taille; ++i) nouveau[i] = donnees[i];
        // La copie d'un int ne leve pas d'exception.
        delete[] donnees;
        donnees = nouveau;
        capacite = nouvelleCapacite;
    }
    donnees[taille] = valeur;
    ++taille;
    return true;
}

bool supprimerDernier(int& taille) {
    if (taille == 0) return false;
    --taille; // Ne pas diminuer la capacite ; l'emplacement sera reutilise.
    return true;
}

void afficher(const int* donnees, int taille, int capacite) {
    std::cout << "Elements : ";
    for (int i = 0; i < taille; ++i) std::cout << donnees[i] << ' ';
    std::cout << "\nTaille : " << taille << "\nCapacite : " << capacite << '\n';
}

int main() {
    int* donnees = nullptr;
    int taille = 0;
    int capacite = 2;
    int codeSortie = 0;
   
    donnees = new int[capacite] {};
    for (int valeur = 1; valeur <= 10; ++valeur) {
        ajouter(donnees, taille, capacite, valeur);
    }
    afficher(donnees, taille, capacite); // Taille 10, capacite 16.

    std::cout << "\nBonus : supprimer le dernier element\n";
    supprimerDernier(taille);
    afficher(donnees, taille, capacite); // Taille 9, capacite 16.

    while (supprimerDernier(taille)) {} // Vider sans liberer le stockage.
    std::cout << std::boolalpha;
    std::cout << "Suppression sur collection vide : "
        << supprimerDernier(taille) << '\n';


    // Une seule liberation du stockage encore possede, meme sur exception.
    delete[] donnees;
    donnees = nullptr;
    return codeSortie;
}
