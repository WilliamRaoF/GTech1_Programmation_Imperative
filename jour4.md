# Jour 4 — Structures et projet de synthèse

## Objectifs

Regrouper des données dans une `struct`, manipuler des structures par référence ou pointeur et développer un programme complet avec une gestion mémoire cohérente.

## 1. Définir une structure

Une structure regroupe des données liées, éventuellement de types différents. Elle permet de nommer un concept du programme.

```cpp
#include <string>

struct Etudiant {
    std::string nom;
    int age = 0;
    double moyenne = 0.0;
};
```

Le point-virgule final est obligatoire. En C++, les membres d'une `struct` sont publics par défaut. Une structure peut également posséder des fonctions membres ; aujourd'hui, nous utilisons des fonctions séparées pour concentrer le travail sur les données.

```cpp
Etudiant alice{"Alice", 20, 15.5};
Etudiant inconnu{};
```

Les champs sont initialisés dans l'ordre de leur déclaration. Dans `inconnu`, le nom est vide, l'âge et la moyenne valent zéro.

## 2. Accéder aux membres et copier

Avec un objet, utiliser le point :

```cpp
std::cout << alice.nom << '\n';
alice.moyenne = 16.0;
```

Avec un pointeur, utiliser la flèche :

```cpp
Etudiant* p = &alice;
p->moyenne = 17.0;
```

`p->nom` est équivalent à `(*p).nom`. Les parenthèses de cette seconde écriture sont nécessaires.

Une copie de cette structure copie ses membres :

```cpp
Etudiant copie = alice;
copie.nom = "Autre";
```

`alice.nom` reste `"Alice"`. `std::string` gère ses propres ressources. Attention : si une structure contient un pointeur brut, sa copie copie l'adresse, pas automatiquement l'objet pointé. Pour ce cours, la structure n'a pas de pointeur propriétaire comme membre.

## 3. Fonctions sur les structures

Pour lire sans copier :

```cpp
void afficher(const Etudiant& etudiant) {
    std::cout << etudiant.nom << " | "
              << etudiant.age << " ans | "
              << etudiant.moyenne << "/20\n";
}
```

`const Etudiant&` évite la copie et interdit la modification par ce paramètre.

Pour modifier :

```cpp
bool modifierMoyenne(Etudiant& etudiant, double nouvelle) {
    if (nouvelle < 0.0 || nouvelle > 20.0) {
        return false;
    }
    etudiant.moyenne = nouvelle;
    return true;
}
```

Le résultat booléen indique si la modification a été acceptée. Une fonction par valeur, `void modifier(Etudiant etudiant)`, ne modifierait que sa copie.

## 4. Tableaux de structures

```cpp
Etudiant groupe[3] = {
    {"Alice", 20, 15.5},
    {"Karim", 21, 13.0},
    {"Lea", 19, 17.0}
};

for (int i = 0; i < 3; ++i) {
    afficher(groupe[i]);
}
```

Le tableau est contigu, mais ne suppose pas que la taille d'une structure est exactement la somme des tailles de ses champs : le compilateur peut ajouter du remplissage pour respecter l'alignement. Un `std::string` peut aussi gérer du stockage séparé pour son texte.

## 5. Allocation dynamique de structures

```cpp
Etudiant* etudiant = new Etudiant{"Nora", 22, 14.0};
afficher(*etudiant);
delete etudiant;
etudiant = nullptr;
```

Pour plusieurs étudiants :

```cpp
Etudiant* groupe = new Etudiant[3]{};
groupe[0] = {"Nora", 22, 14.0};
delete[] groupe;
groupe = nullptr;
```

`delete[]` détruit chaque structure, donc aussi ses membres `std::string`, puis libère le stockage du tableau. Aucun `delete` séparé n'est nécessaire pour les noms.

## 6. Recherche et durée de vie du résultat

```cpp
Etudiant* rechercher(Etudiant* groupe, int taille,
                    const std::string& nom) {
    for (int i = 0; i < taille; ++i) {
        if (groupe[i].nom == nom) {
            return &groupe[i];
        }
    }
    return nullptr;
}
```

Le résultat est un pointeur **observateur** : l'appelant ne doit pas le libérer. Il désigne un élément du groupe et devient invalide si le groupe est libéré ou remplacé par une autre allocation.

```cpp
Etudiant* trouve = rechercher(groupe, taille, "Alice");
if (trouve != nullptr) {
    modifierMoyenne(*trouve, 18.0);
}
```

## Atelier Visual Studio — Inspecter une structure

Poser un point d'arrêt après la création d'`alice`. Ouvrir **Variables locales** et développer `alice` pour voir ses membres. Ajouter `alice.nom`, `alice.moyenne`, `p` et `p->moyenne` à **Espion 1** une fois `p` initialisé.

Avancer avec `F10` pendant une modification. Utiliser `F11` pour entrer dans `modifierMoyenne` et observer que la référence concerne l'objet original. Pour un tableau dynamique nommé `groupe`, l'expression de débogueur `groupe,3` affiche trois éléments : adapter ce nombre à la taille réellement allouée. Cette syntaxe est un affichage du débogueur, pas une expression à recopier dans le programme.

## Exercices pratiques

### Exercice 1 — Bibliothèque (30 min)

Créer une structure `Livre` avec titre, auteur et année. Créer trois livres dans un tableau fixe. Écrire une fonction `void afficherLivre(const Livre& livre)`.

Afficher tous les livres, puis uniquement ceux publiés après 2000. Les années doivent être comprises entre 1 et 2100.

**Test :** des livres datés de 1998, 2005 et 2020 doivent produire deux résultats au second affichage. Vérifier aussi le cas où aucun livre ne correspond.

**Critères :** données regroupées, fonction réutilisée, parcours valide.

### Exercice 2 — Rechercher et modifier (30 min)

Créer un tableau fixe de trois étudiants. Écrire `rechercher` et `modifierMoyenne`.

1. Chercher un nom présent et afficher l'étudiant.
2. Modifier sa moyenne à travers le résultat de recherche.
3. Chercher un nom absent et afficher un message.
4. Tester une moyenne invalide sans changer l'ancienne valeur.

**Test :** Alice commence à `15.5`, passe à `18`, puis une tentative à `25` est refusée et elle reste à `18`.

**Critères :** vérifier `nullptr`, modifier l'objet original, aucune allocation nécessaire pour la recherche.

## Projet pratique — Gestion d'un groupe d'étudiants

### Cahier des charges

Écrire un programme console. Il demande un nombre d'étudiants entre 1 et 100, crée un tableau dynamique de structures, puis permet :

1. La saisie initiale du groupe.
2. L'affichage de tous les étudiants.
3. Le calcul de la moyenne du groupe.
4. L'affichage de l'étudiant ayant la meilleure moyenne.
5. La recherche d'un étudiant par nom.
6. La modification d'une moyenne.
7. La sortie avec libération du tableau.

Utiliser un menu répété jusqu'au choix de sortie. Pour cette version, les noms sont saisis sans espaces et sont uniques. Âges autorisés : 1 à 120 ; moyennes : 0 à 20. Les saisies sont supposées du bon type dans la version obligatoire.

### Fonctions proposées

```cpp
void saisirGroupe(Etudiant* groupe, int taille);
void afficherGroupe(const Etudiant* groupe, int taille);
double moyenneGroupe(const Etudiant* groupe, int taille);
const Etudiant* meilleurEtudiant(const Etudiant* groupe, int taille);
Etudiant* rechercher(Etudiant* groupe, int taille,
                    const std::string& nom);
bool modifierMoyenne(Etudiant& etudiant, double nouvelle);
```

**Contrats :**

- Les pointeurs de tableau désignent au moins `taille` éléments lorsque `taille > 0`.
- `moyenneGroupe` exige une taille strictement positive ; vérifier ce préalable dans l'appelant.
- `meilleurEtudiant` renvoie `nullptr` pour un groupe vide ; en cas d'égalité, renvoyer le premier meilleur étudiant.
- `rechercher` renvoie `nullptr` si le nom est absent.
- Les fonctions reçoivent le groupe en observation ; seul `main` possède et libère l'allocation.

### Squelette de départ

```cpp
#include <iostream>
#include <string>

struct Etudiant {
    std::string nom;
    int age = 0;
    double moyenne = 0.0;
};

// Ajouter les prototypes ici.

int main() {
    int taille = 0;
    std::cout << "Nombre d'etudiants (1 a 100) : ";
    std::cin >> taille;
    if (!std::cin || taille < 1 || taille > 100) {
        std::cout << "Taille invalide\n";
        return 1;
    }

    Etudiant* groupe = new Etudiant[taille]{};

    // Saisie, puis menu.
    // Ne pas quitter par un return qui oublierait la liberation.

    delete[] groupe;
    groupe = nullptr;
    return 0;
}

// Ajouter les definitions des fonctions ici.
```

Le squelette compile, mais ses fonctionnalités restent à compléter. Cette version manuelle sert à travailler la propriété mémoire ; la gestion automatique ci-dessous traite mieux les sorties exceptionnelles.


## Modernisation

Remplacer le propriétaire brut par un vecteur :

```cpp
#include <vector>
std::vector<Etudiant> groupe(taille);
```

Adapter les fonctions :

```cpp
void afficherGroupe(const std::vector<Etudiant>& groupe);
double moyenneGroupe(const std::vector<Etudiant>& groupe);
Etudiant* rechercher(std::vector<Etudiant>& groupe,
                    const std::string& nom);
```

Utiliser `groupe.size()` et, si utile, une boucle par plage :

```cpp
for (const Etudiant& etudiant : groupe) {
    afficher(etudiant);
}
```

Ne plus appeler `delete[]`. Un pointeur renvoyé par la recherche reste soumis à la durée de vie des éléments ; une réallocation du vecteur peut l'invalider.

## Challenge — Ajouter et supprimer des étudiants

Étendre la version manuelle avec deux fonctions :

```cpp
bool ajouter(Etudiant*& groupe, int& taille,
             const Etudiant& nouveau);
bool supprimer(Etudiant*& groupe, int& taille,
               const std::string& nom);
```

La référence au pointeur permet de remplacer le pointeur de `main`. La référence à la taille permet de mettre à jour le nombre d'éléments.

### Règles

- Refuser un ajout si le nom existe déjà ou si le groupe contient 100 étudiants.
- Lors d'un ajout, allouer un tableau de `taille + 1`, copier puis ajouter.
- Lors d'une suppression, ne rien changer si le nom est absent.
- Sinon allouer un tableau réduit et copier les autres étudiants dans le même ordre.
- Si le dernier étudiant est supprimé, libérer le tableau et utiliser `nullptr` avec une taille de zéro.
- Ne remplacer l'ancien pointeur qu'après création et copie du nouveau tableau.
- Ne plus utiliser les anciens pointeurs de recherche après remplacement.
- Adapter moyenne et meilleur étudiant au cas vide dans le menu.

Le challenge est un approfondissement, sans pénalité pour ceux qui ne le réalisent pas.

## Documentation Microsoft

- [Inspection des variables](https://learn.microsoft.com/fr-fr/visualstudio/debugger/watch-and-quickwatch-windows?view=vs-2022)
