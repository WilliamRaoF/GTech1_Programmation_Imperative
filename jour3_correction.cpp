#include <iostream>
#include <vector>

/**************EXERCICE 2************
*void doubler(int* valeur) {
*    if (valeur != nullptr) *valeur *= 2;
*}
**************************************/

//double moyenne(const double* notes, int taille) {
//    double somme = 0.0;
//
//    for (int i = 0; i < taille; ++i) {
//        somme += notes[i];
//    }
//
//    return somme / taille;
//}
/***********EXERCICE 3*********/
double moyenne(std::vector<double> notes) {
    double somme = 0.0;

    for (int i = 0; i < notes.size(); ++i) {
        somme += notes[i];
    }

    return somme / notes.size();
}


double minimum(const double* notes, int taille) {
    double resultat = notes[0];

    for (int i = 1; i < taille; ++i) {
        if (notes[i] < resultat) {
            resultat = notes[i];
        }
    }

    return resultat;
}

double maximum(const double* notes, int taille) {
    double resultat = notes[0];

    for (int i = 1; i < taille; ++i) {
        if (notes[i] > resultat) {
            resultat = notes[i];
        }
    }

    return resultat;
}


int main() {
    /************EXERCICE 1******************
    *int exterieur = 10;
    *{
    *    int interieur = 20;
    *    int* observateurExterieur = &exterieur;
    *}
    *int* proprietaire = new int{ 5 };
    *int* observateurDynamique = proprietaire;
    *
    *delete proprietaire;
    *
    *proprietaire = nullptr;
    *observateurDynamique = nullptr;
    ********************************/


    /**************EXERCICE 2************
    *
    *   int* number = new int{};
    *   int* copy = number;
    *   do {
    *       if (!(std::cin >> *number)) {
    *            std::cout << "Ce n'est pas un nombre \n";
    *            *number = -1001;
    *       }
    *   } while (*number > 1000 || *number < -1000);
    *
    *   doubler(number);
    *   std::cout << *number << "   " << *copy;
    *
    *   delete number;
    *
    *   number = nullptr;
    *   copy = nullptr;
    ***********************************/
    /*******EXERCICE 3*******/
    int taille = 0;
    std::vector<double> vectorNotes;
    std::cout << "Nombre de notes entre 1 et 100 : ";

    if (!(std::cin >> taille) || taille < 1 || taille > 100) {
        std::cout << "Nombre de notes invalide\n";
        return 1;
    }

    double* notes = new double[taille] {};

    for (int i = 0; i < taille; ++i) {
        double note = -1.0;

        do {
            std::cout << "Note " << i + 1
                << " entre 0 et 20 : ";

            if (!(std::cin >> note)) {
                std::cout << "Saisie non numerique\n";

                delete[] notes;
                notes = nullptr;

                return 1;
            }
        } while (note < 0.0 || note > 20.0);
        vectorNotes.push_back(note);
        notes[i] = note;
    }

    std::cout << "Moyenne : " << moyenne(vectorNotes) << '\n';
    std::cout << "Minimum : " << minimum(notes, taille) << '\n';
    std::cout << "Maximum : " << maximum(notes, taille) << '\n';

    delete[] notes;
    notes = nullptr;


    return 0;

}
/***************EXERCICE 1*************************
* Objet                    |  Durée de vie             | Libération
* exterieur                 Jusqu'a la fin du main     Pas besoin
* interieur                 Jusqu'a la ligne 8         Pas besoin
* observateurDynamique      Jusqu'a la fin du main     Automatique
* proprietaire              Jusqu'a la fin du main     Automatique
* observateurExterieur      Jusqu'a la ligne 8         Automatique
* Entier crée par new int{5}Jusqu'a la ligne 12        A la main ligne 12
* ***************************************/


