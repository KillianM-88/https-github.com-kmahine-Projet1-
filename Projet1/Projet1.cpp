// Projet1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h> // Fournit _getch() sous Windows
#include <chrono> // Pour std::chrono::seconds / milliseconds
#include <thread> // Pour std::this_thread::sleep_for


struct Map {

    char basic_ground = '.';
    char water = '~';
    char moutain = 'A';
    //char enemies = 'X';
    int grille[10][20] = {};

};



struct Hero {

    int hp = 1;
    //int pos = 10;
    int x = 0;
    int y = 0;
    char cell = 'H'; 
    /*bool droite = false;
    bool gauche = false;
    bool haut = false;
    bool bas = false;*/

};

struct Enemy {

    int hp = 1;
    //int pos = 10;
    int x = 0;
    int y = 0;
    char cell = 'X';
    /*bool droite = false;
    bool gauche = false;
    bool haut = false;
    bool bas = false;*/

};
void init_map(Map& map, Hero& hero, Enemy& enemy) {

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {
            map.grille[x][y] = 0;
        }
    }

    // char waterzone[2] = { grille[5][6], grille[5][7] };   A continuer pour optimiser la mise en place les zones d'eau ou montagnes via des tableaux
    //for (int i = 0; i < 2; ++i) {
    //  waterzone[i] = map.water;
    //}
    map.grille[5][6] = 1;
    map.grille[5][7] = 1;
    map.grille[9][2] = 2;


    enemy.x = 0 ;
    enemy.y = 7;
    map.grille[enemy.x ][enemy.y] = 3;
   

    map.grille[8][4] = 3;
    map.grille[2][10] = 3;
    map.grille[7][7] = 3;
    map.grille[6][3] = 3;


}


void afficher_map(Map& map, Hero& hero, Enemy& enemy) {


    system("cls");

    

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {

            if (x == hero.x && y == hero.y) {
                std::cout << hero.cell;
            }

            else if (x == enemy.x && y == enemy.y) {

                std::cout << enemy.cell;
            }


            else if (map.grille[x][y] == 1) {
                std::cout << map.water;
            }

            

            else if (map.grille[x][y] == 2) {
                std::cout << map.moutain;
            }
            else {
                std::cout << map.basic_ground;
            }

        }
        std::cout << '\n';
    }
    std::cout << "Vous avez : " << hero.hp << " vie";
    
}


void deplacement(Map& map, Hero& hero) {

    char touche = _getch();


    if ((touche == 'z' || touche == 'Z' ) && hero.x > 0 ) {

        if (map.grille[(hero.x - 1)][hero.y] == 3) {

            
            hero.x--;
            hero.hp--;
        }

        else if (map.grille[(hero.x-1)][hero.y] == 0) {

            hero.x--;
        }
        
    }

    else if ((touche == 's' || touche == 'S' ) && hero.x < 9) {

        if (map.grille[(hero.x + 1)][hero.y] == 3) {

            hero.x++;
            hero.hp--;
        }

        else if (map.grille[(hero.x + 1)][hero.y] == 0) {

            hero.x++;
        }
    }

    else if ((touche == 'q' || touche == 'Q' ) && hero.y > 0 ) {

        if (map.grille[(hero.x)][hero.y - 1] == 3) {

            hero.y--;
            hero.hp--;
        }

        else if (map.grille[hero.x][(hero.y - 1)] == 0) {

            hero.y--;
        }
        
    }

    else if ((touche == 'd' || touche == 'D' ) && hero.y < 19 ) {

        if (map.grille[(hero.x)][hero.y + 1] == 3) {

            hero.y++;
            hero.hp--;
        }

        else if (map.grille[hero.x][(hero.y + 1)] == 0) {

            hero.y++;
        }

    }
    
}

void deplacement(Map& map, Hero& hero) {

}

void gameover(Map& map, Hero& hero) {

    while (_kbhit()) (void)_getch();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    while (_kbhit()) (void)_getch();

    system("cls");

    std::cout << "\n";
    std::cout << "  Game over !! ";
    std::cout << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(3));

}




int main() {

    Map map{};
    Hero hero{};
    Enemy enemy{};
    //Enemy enemy2{};

    init_map(map, hero, enemy);

   
    afficher_map(map, hero, enemy);

    while (true) {


        deplacement(map, hero);


        if (hero.hp <= 0) {
            afficher_map(map, hero, enemy);
            gameover(map, hero);
            break;
        }

        afficher_map(map, hero, enemy);


        // Touche Échap pour quitter
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
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
