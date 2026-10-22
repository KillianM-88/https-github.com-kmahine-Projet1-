// Projet1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <windows.h> // Fournit system("cls") (pour effacer l'écran de la console) et GetAsyncKeyState(VK_ESCAPE) pour détecter la touche Échap 
#include <cstdlib>  // Fournit rand() et srand
#include <conio.h> // Fournit _getch() et _kbhit() (pour vérifier si une touche a été pressée).
#include <chrono> // Pour std::chrono::seconds / milliseconds
#include <thread> // Pour std::this_thread::sleep_for
#include <ctime> // srand(time(NULL))

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
    int x = 0;
    int y = 0;
    char cell = 'H'; 

};

struct Enemy {

    int hp = 1;
    int x = 0;
    int y = 0;
    char cell = 'X';

};

void init_map(Map& map, Hero& hero, Enemy tab[], int niveau) {

    // Fonction qui gère la mise en place des caractéristique de la map en fonction du niveau

    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 20; ++y) {
            map.grille[x][y] = 0;
        }
    }

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

        hero.x = 9;
        hero.y = 0;

        // liste des waterzones
        map.grille[6][8] = 1;
        map.grille[6][9] = 1;
        map.grille[7][8] = 1;
        map.grille[7][9] = 1;

        // liste des montagnes
        map.grille[7][1] = 2;
        map.grille[7][3] = 2;
        map.grille[4][12] = 2;

        // Mise en place de la sortie
        map.grille[0][10] = 3;

        // Mise en place des coord des ennemis
        tab[0].x = 1;
        tab[0].y = 2;

        tab[1].x = 5;
        tab[1].y = 12;

        tab[2].x = 7;
        tab[2].y = 4;

        tab[3].x = 3;
        tab[3].y = 18;

        tab[4].x = 6;
        tab[4].y = 10;

    }
    

}

void afficher_map(Map& map, Hero& hero, Enemy tab[]) {

    // Fonction qui gère l'affichage de la map (terrain, héros et ennemis)


    system("cls"); // Efface l'écran de la console

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

    std::cout << '\n' << "Level " << niveau << '\n' << '\n';
    std::cout << "Vous avez : " << hero.hp << " vie" << '\n';
    std::cout << '\n' << "Up : Z";
    std::cout << '\n' << "Left : Q";
    std::cout << '\n' << "Down : S";
    std::cout << '\n' << "Right : D" << '\n';
    std::cout << '\n' << "Hero : " << hero.cell;
    std::cout << '\n' << "Ennemi : " << tab[0].cell;
    std::cout << '\n' << "Water : " << map.water;
    std::cout << '\n' << "Moutain : " << map.moutain;
    std::cout << '\n' << "Exit : " << map.exit;
  
}


bool deplacement(Map& map, Hero& hero, Enemy tab[], bool& validmove) {

    // Fonction qui prend en compte les entrées claviers ZQSD et modifie les coordonnées du héros en conséquence

    char touche = _getch();
    validmove = false;

    if ((touche == 'z' || touche == 'Z' ) && hero.x > 0 ) {

        if (map.grille[(hero.x-1)][hero.y] == 0 || map.grille[(hero.x - 1)][hero.y] == 3) {

            hero.x--;
            validmove = true;
        }
        
    }

    else if ((touche == 's' || touche == 'S' ) && hero.x < 9) {


        if (map.grille[(hero.x + 1)][hero.y] == 0 || map.grille[(hero.x + 1)][hero.y]  == 3) {

            hero.x++;
            validmove = true;
        }
    }

    else if ((touche == 'q' || touche == 'Q' ) && hero.y > 0 ) {

        if (map.grille[hero.x][(hero.y - 1)] == 0 || map.grille[hero.x][(hero.y - 1)] == 3) {

            hero.y--;
            validmove = true;
        }
        
    }

    else if ((touche == 'd' || touche == 'D' ) && hero.y < 19 ) {

        if (map.grille[hero.x][(hero.y + 1)] == 0 || map.grille[hero.x][(hero.y + 1)] == 3) {

            hero.y++;
            validmove = true;
        }

    }

    for (int i = 0; i < 5; ++i) {
        if (tab[i].x == hero.x && tab[i].y == hero.y) {
            hero.hp--;
        }
    }
    
    return validmove;
}

void deplacement2(Map& map, Hero& hero, Enemy tab[]) {

    // Fonction qui initialise un entier aléatoire pour déplacer les ennemis dans l'une des 4 directions correspondantes

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

    // Fonction qui gère la fin de partie lorsque le joueur atteint 0 hp

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

    // Fonction qui gère la fin de partie lorsque le joueur atteint la sortie

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

    srand(time(NULL)); //  Hasard remis a zero a chaque lancement
    

    Map map{};
    Hero hero{};
    Enemy tab[5];

    init_map(map, hero, tab, niveau);
    afficher_map(map, hero, tab);

    while (true) {

        bool validmove;


        deplacement(map, hero, tab, validmove);

        if (hero.hp <= 0) {
            afficher_map(map, hero, tab);
            gameover(map, hero);
            break;
        }
        if ((map.grille[hero.x][(hero.y)] == 3)) {

            afficher_map(map, hero, tab);

            victory(map, hero);
            if (niveau == 1) {
                niveau = 2;
                init_map(map, hero, tab, niveau);
                //continue;
            }
            else if (niveau == 2) {
                std::cout << "\n";
                std::cout << "GG T'AS FINI LE JEUU";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
           

        }
        if (validmove == true ) {
            deplacement2(map, hero, tab);
            afficher_map(map, hero, tab);
        }
        

        if (hero.hp <= 0) {
            afficher_map(map, hero, tab);
            gameover(map, hero);
            break;
        }
       

        // Touche Échap pour quitter
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

    }

    return 0;
}
