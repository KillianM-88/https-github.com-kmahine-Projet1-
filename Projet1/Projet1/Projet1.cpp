// Projet1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

struct Map {

    char basic_ground = '.';
    char water = '~';
    char moutain = 'A';

};

void afficher_map(const Map& map) {

    char grille[10][20] = {};  // a voir pour le changer en attribut de Map ou pas

    // char waterzone[2] = { grille[5][6], grille[5][7] };   A continuer pour optimiser la mise en place les zones d'eau ou montagnes via des tableaux
     //for (int i = 0; i < 2; ++i) {
       //  waterzone[i] = map.water;
     //}


   grille[5][6] = map.water;
   grille[5][7] = map.water;
   grille[9][2] = map.moutain;

    for (int ligne = 0; ligne < 10; ++ligne) {
        for (int colonne = 0; colonne < 20; ++colonne) {

            if (grille[ligne][colonne] != map.water && grille[ligne][colonne] != map.moutain) {

                grille[ligne][colonne] = map.basic_ground;


            }
            std::cout << grille[ligne][colonne] << ' ';


        };
        std::cout << '\n';

    };


}


struct Hero {

    int hp = 1;
    char body = 'H';

};

int main(){

    Map map{};
    afficher_map(map);


    return 0;

    
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
