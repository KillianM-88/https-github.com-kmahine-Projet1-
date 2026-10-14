// Projet1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h> // Fournit _getch() sous Windows


struct Map {

    char basic_ground = '.';
    char water = '~';
    char moutain = 'A';
    //char grille[10][20] = {};
    int grille[10][20] = {};

  

};



struct Hero {

    int hp = 1;
    int x = 0;
    int y = 0;
    char pos = 'H'; 
    bool droite = false;
    bool gauche = false;
    bool haut = false;
    bool bas = false;
    
    


};

void init_map(Map& map, Hero& hero) {

    //char grille[10][20] = {};  // a voir pour le changer en attribut de Map ou pasg

    // char waterzone[2] = { grille[5][6], grille[5][7] };   A continuer pour optimiser la mise en place les zones d'eau ou montagnes via des tableaux
     //for (int i = 0; i < 2; ++i) {
       //  waterzone[i] = map.water;
     //}


  
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {

            map.grille[x][y] = 0;

        };
 
    };

    map.grille[5][6] = 1;
    map.grille[5][7] = 1;
    map.grille[9][2] = 2;

    char cell = '0';

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {

            if (map.grille[x][y] == 1) {


                char cell = map.water;
                std::cout << cell;

            }

            else if (map.grille[x][y] == 2) {

                char cell = map.moutain;
                std::cout << cell;

            }
            else {
                char cell = map.basic_ground;
                std::cout << cell;
            }


        };
       
        std::cout << '\n';
    };


}



void afficher_map(Map & map, Hero & hero) {

   
    char touche = _getch();


    if (touche == 's' || touche == 's') {
        std::cout << "-> Effet declenche : Action activee !"  ;
        
    }

      

}
int main(){

    Map map{};
    Hero hero{};

  
    init_map(map, hero);
   

   
    
    while (true) {


       afficher_map(map, hero);

 
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            std::cout << "Touche Echap detectee !\n";
            break;
        }

    }

   
    


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
