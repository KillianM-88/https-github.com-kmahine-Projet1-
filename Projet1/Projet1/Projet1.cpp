// Projet1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h> // Fournit _getch() sous Windows
#include <chrono> // Pour std::chrono::seconds / milliseconds
#include <thread> // Pour std::this_thread::sleep_for
#include <ctime>

int niveau = 1;

struct Map {

    char basic_ground = '.';
    char water = '~';
    char moutain = 'A';
    char exit = 'E';

    int grille[10][20] = {};
    
    int waterzones[5] = {};

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
void init_map(Map& map, Hero& hero, Enemy tab[], int niveau) {

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {
            map.grille[x][y] = 0;
        }
    }

    // char waterzone[2] = { grille[5][6], grille[5][7] };   A continuer pour optimiser la mise en place les zones d'eau ou montagnes via des tableaux
    //for (int i = 0; i < 2; ++i) {
    //  waterzone[i] = map.water;
    //}

    if (niveau == 1) {

        // liste des waterzones
        map.grille[5][6] = 1;
        map.grille[5][7] = 1;
        map.grille[3][15] = 1;
        map.grille[3][16] = 1;

        // liste des montagnes
        map.grille[9][2] = 2;
        map.grille[9][17] = 2;
        map.grille[7][14] = 2;

        // Mise en place de la sortie
        map.grille[9][19] = 3;

        // Mise en place des coord des ennemis
        tab[0].x = 0;
        tab[0].y = 7;

        tab[1].x = 6;
        tab[1].y = 14;

        tab[2].x = 5;
        tab[2].y = 4;

        tab[3].x = 1;
        tab[3].y = 12;

        tab[4].x = 7;
        tab[4].y = 16;
    }

    else if (niveau == 2) {

        // liste des waterzones
        map.grille[6][8] = 1;
        map.grille[6][9] = 1;
        map.grille[7][8] = 1;
        map.grille[7][9] = 1;

        // liste des montagnes
        map.grille[9][2] = 2;
        map.grille[9][17] = 2;
        map.grille[7][14] = 2;

        // Mise en place de la sortie
        map.grille[9][19] = 3;

        // Mise en place des coord des ennemis
        tab[0].x = 0;
        tab[0].y = 7;

        tab[1].x = 6;
        tab[1].y = 14;

        tab[2].x = 5;
        tab[2].y = 4;

        tab[3].x = 1;
        tab[3].y = 12;

        tab[4].x = 7;
        tab[4].y = 16;

    }
    

}

void afficher_map(Map& map, Hero& hero, Enemy tab[]) {


    system("cls");

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {

            bool caselibre = true;

            for (int i = 0; i < 5; ++i) {

                if (x == tab[i].x && y == tab[i].y) {

                    std::cout << tab[i].cell;
                    caselibre = false;

                }
            }

            if (caselibre == true) {

                if (x == hero.x && y == hero.y) {
                    std::cout << hero.cell;
                }

                else if (map.grille[x][y] == 1) {
                    std::cout << map.water;
                }

                else if (map.grille[x][y] == 2) {
                    std::cout << map.moutain;
                }

                else if (map.grille[x][y] == 3) {
                    std::cout << map.exit;
                }

                else {
                    std::cout << map.basic_ground;
                }

            }

        }
        std::cout << '\n';
    }
    std::cout << "Vous avez : " << hero.hp << " vie";
    
}


void deplacement(Map& map, Hero& hero, Enemy tab[]) {

    char touche = _getch();


    if ((touche == 'z' || touche == 'Z' ) && hero.x > 0 ) {

        if (map.grille[(hero.x-1)][hero.y] == 0 || map.grille[(hero.x - 1)][hero.y] == 3) {

            hero.x--;
        }
        
    }

    else if ((touche == 's' || touche == 'S' ) && hero.x < 9) {


        if (map.grille[(hero.x + 1)][hero.y] == 0 || map.grille[(hero.x + 1)][hero.y]  == 3) {

            hero.x++;
        }
    }

    else if ((touche == 'q' || touche == 'Q' ) && hero.y > 0 ) {

        if (map.grille[hero.x][(hero.y - 1)] == 0 || map.grille[hero.x][(hero.y - 1)] == 3) {

            hero.y--;
        }
        
    }

    else if ((touche == 'd' || touche == 'D' ) && hero.y < 19 ) {

        if (map.grille[hero.x][(hero.y + 1)] == 0 || map.grille[hero.x][(hero.y + 1)] == 3) {

            hero.y++;
        }

    }

    for (int i = 0; i < 5; ++i) {
        if (tab[i].x == hero.x && tab[i].y == hero.y) {
            hero.hp--;
        }
    }
    
}

void deplacement2(Map& map, Hero& hero, Enemy tab[]) {

    //int nb = 1 + rand() % 4; // rand() % 4 donne un reste compris entre 0 et 3 car le reste d'une division par 4 vaut toujours 0, 1, 2 ou 3

    for (int i = 0; i < 5; ++i) {

        int nb = 1 + rand() % 4; // rand() % 4 donne un reste compris entre 0 et 3 car le reste d'une division par 4 vaut toujours 0, 1, 2 ou 3

        if (nb == 1 && tab[i].x > 0) {

            if (map.grille[(tab[i].x - 1)][tab[i].y] == 0) {

                tab[i].x--;
            }

        }

        else if (nb == 2 && tab[i].x < 9) {

            if (map.grille[tab[i].x + 1][tab[i].y] == 0) {

                tab[i].x++;
            }

        }

        else if (nb == 3 && tab[i].y > 0) {

            if (map.grille[tab[i].x][tab[i].y - 1] == 0) {

                tab[i].y--;
            }
        }

        else if (nb == 4 && tab[i].y < 19) {

            if (map.grille[tab[i].x][tab[i].y + 1] == 0) {

                tab[i].y++;
            }
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (tab[i].x == hero.x && tab[i].y == hero.y) {
            hero.hp--;
        }
    }
    

      

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

void victory(Map& map, Hero& hero) {

    while (_kbhit()) (void)_getch();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    while (_kbhit()) (void)_getch();

    system("cls");

    std::cout << "\n";
    std::cout << "  Victory  !! ";
    std::cout << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(3));

}




int main() {

    srand(time(NULL)); //  Hasard remis a zero a chq lancement
    

    Map map{};
    Hero hero{};
    //Enemy enemy{};
    //Enemy enemy2{};
   
    
    //Enemy enemy3{};
    Enemy tab[5];

    init_map(map, hero, tab, niveau);
    afficher_map(map, hero, tab);

    while (true) {


        deplacement(map, hero, tab);

        if (hero.hp <= 0) {
            afficher_map(map, hero, tab);
            gameover(map, hero);
            break;
        }
        if ((map.grille[hero.x][(hero.y)] == 3)) {
            afficher_map(map, hero, tab);
            victory(map, hero);
            niveau = 2;

        }

        deplacement2(map, hero, tab);

        if (hero.hp <= 0) {
            afficher_map(map, hero, tab);
            gameover(map, hero);
            break;
        }
       

        

        afficher_map(map, hero, tab);


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
