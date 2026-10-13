// Projet1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <windows.h>

struct Map {

    char basic_ground = '.';
    char water = '~';
    char moutain = 'A';
    char grille[10][20] = {};
    int grillenb[10][20] = {};

  

};



struct Hero {

    int hp = 1;
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


    map.grille[5][6] = map.water;
    map.grille[5][7] = map.water;
    map.grille[9][2] = map.moutain;
    map.grille[0][0] = hero.pos;



    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {

            if (map.grille[x][y] != map.water && map.grille[x][y] != map.moutain && map.grille[x][y] != hero.pos) {

                map.grille[x][y] = map.basic_ground;


            }
            std::cout << map.grille[x][y] << ' ';

        };
        std::cout << '\n';


    };


}

void init_map2(Map& map, Hero& hero) {

    //char grille[10][20] = {};  // a voir pour le changer en attribut de Map ou pasg

    // char waterzone[2] = { grille[5][6], grille[5][7] };   A continuer pour optimiser la mise en place les zones d'eau ou montagnes via des tableaux
     //for (int i = 0; i < 2; ++i) {
       //  waterzone[i] = map.water;
     //}


    map.grillenb[5][6] = 1;
    map.grillenb[5][7] = 1;
    map.grillenb[9][2] = 2;
    map.grillenb[0][0] = 10;



    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {

            if (map.grillenb[x][y] = 10) {

                map.grille[x][y] = hero.pos;

            }

            if (map.grillenb[x][y] = 1) {

                map.grille[x][y] = map.water;

            }
            if (map.grillenb[x][y] = 2 ) {

                map.grille[x][y] = map.moutain;

            }
            
            else {
                map.grille[x][y] = map.basic_ground;
            }

            std::cout << map.grille[x][y] << ' ';

        }
        std::cout << '\n';


    }


}

void afficher_map(Map & map, Hero & hero) {

   
    if ((GetAsyncKeyState('S') & 0x8000)) {

        hero.bas = true;
        
    }
    

    if (hero.bas == true) {

     
        std::cout << "Hourra";  // ca marcheeee
        // hero.pos = map.grille[x][y + 1];


        /*
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < 20; ++y) {
                if (hero.pos = map.grille[x][y]) {

                    hero.pos = map.grille[x][y + 1];
                    

                }
                std::cout << map.grille[x][y] << ' ';
                

            }
            std::cout << '\n';
        }*/

            
           // std::cout << map.grille[x][y];
    }
      

}
int main(){

    Map map{};
    Hero hero{};

  
    init_map(map, hero);
   

   
    
    while (true) {


       afficher_map(map, hero);

       /*
       for (int x = 0; x < 10; ++x) {
           for (int y = 0; y < 20; ++y) {

               std::cout << map.grille[x][y];
           }

       }
       */
 
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
