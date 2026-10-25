// Projet1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cstdlib>  // Fournit rand(), srand et system("cls") (pour effacer l'écran de la console)
#include <conio.h> // Fournit _getch() 
#include <chrono> // Pour std::chrono::seconds / milliseconds
#include <thread> // Pour std::this_thread::sleep_for
#include <ctime> // srand(time(NULL))
#include <fstream> 
#include <string> 

int niveau = 1;


struct Map {

    char basic_ground = '.';
    char water = '~';
    char moutain = 'A';
    char exit = 'E';
    int grille[10][20] = {};

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

bool load_level(Map& map, Hero& hero, Enemy tab[], int niveau) {

    std::string nomFichier = "levels/level" + std::to_string(niveau) + ".txt";
    std::ifstream fichier(nomFichier);

    if (!fichier.is_open()) {
        std::cout << "Erreur : impossible d'ouvrir " << nomFichier << '\n';
        return false;
    }

    std::string lignes[10];
    std::string ligne;
    int nblignes = 0;

    while (std::getline(fichier, ligne)) {

        if (nblignes < 10) {
            lignes[nblignes] = ligne;
        }

        nblignes++;
    }

    if (nblignes != 10) {

        std::cout << "Erreur le fichier contient " << nblignes << " lignes au lieu de 10" << '\n';

        return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (lignes[i].size() != 20) {

            std::cout << "Erreur la ligne " << i + 1 << " contient "<< lignes[i].size() << " caracteres au lieu de 20" << '\n';

            return false;
        }
    }

    char charvalides[6] = { 'A', 'X', 'E','H', '.', '~', };
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            bool validchar = false;
            for (int k = 0; k < 6; k++) {

                if (lignes[i][j] == charvalides[k]) {
                    validchar = true;
                }
            }
            if (validchar == false) {
                std::cout << "Erreur le caractere " << j + 1 << " de la " << i + 1 << " eme ligne n'est pas valide" << '\n';
                return false;
            }
        }
    }

    int nb_H = 0;
    int nb_E = 0;
    int nb_X = 0;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {

            if (lignes[i][j] == 'H') {
                nb_H += 1;
            }
            else if (lignes[i][j] == 'E') {
                nb_E += 1;
            }
            else if (lignes[i][j] == 'X') {
                nb_X += 1;
            }
        }
    }

    if (nb_H != 1) {

        std::cout << "Erreur il y a " << nb_H << " H sur la map" << "\n";
        return false;
    }

    else if (nb_E != 1) {

        std::cout << "Erreur il y a " << nb_E << " E sur la map" << "\n";
        return false;
    }

    else if (nb_X != 5) {

        std::cout << "Erreur il y a " << nb_X << " X sur la map" << "\n";
        return false;
    }

    int nbenemy = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {

            if (lignes[i][j] == '.') {

                map.grille[i][j] = 0;
            }

            else if (lignes[i][j] == '~') {

                map.grille[i][j] = 1;
            }

            else if (lignes[i][j] == 'A') {
                map.grille[i][j] = 2;
            }

            else if (lignes[i][j] == 'E') {
                map.grille[i][j] = 3;
            }

            else if (lignes[i][j] == 'H') {

                map.grille[i][j] = 0;

                hero.x = i;
                hero.y = j;

            }

            else if (lignes[i][j] == 'X') {

                map.grille[i][j] = 0;
                tab[nbenemy].x = i;
                tab[nbenemy].y = j;
                nbenemy++;
            }
        }
    }

    return true;
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


bool deplacement(Map& map, Hero& hero, Enemy tab[]) {

    // Fonction qui prend en compte les entrées claviers ZQSD et modifie les coordonnées du héros en conséquence

    char touche = _getch();
    bool validmove = false;

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


void endgame(Hero& hero) {

    // Fonction qui gère la fin de partie selon les hp du joueur

    std::this_thread::sleep_for(std::chrono::seconds(2));

    system("cls");

    if (hero.hp > 0) {

        std::cout << "\n";
        std::cout << "  Victory  !! ";
        std::cout << "\n";
    }
    
    else {

        std::cout << "\n";
        std::cout << "  Game over !! ";
        std::cout << "\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));


}


int main() {

    srand(time(NULL)); //  Hasard remis a zero a chaque lancement
    

    Map map{};
    Hero hero{};
    Enemy tab[5];

    if (!load_level(map, hero, tab, niveau)) {

        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 1;
        
    }
    afficher_map(map, hero, tab);

    while (true) {

        bool validmove;
        


        validmove = deplacement(map, hero, tab);

        if (hero.hp <= 0) {
            afficher_map(map, hero, tab);
            endgame(hero);
            break;
        }
        if ((map.grille[hero.x][(hero.y)] == 3)) {

            afficher_map(map, hero, tab);

            endgame(hero);
            if (niveau == 1) {
                niveau = 2;
                if (!load_level(map, hero, tab, niveau)) {
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
                validmove = false;
                afficher_map(map, hero, tab);
            }

            else if (niveau == 2) {
                std::cout << "\n";
                std::cout << "  ***CONGRATULATIONS*** ";
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
            endgame(hero);
            break;
        }

    }

    return 0;
}
