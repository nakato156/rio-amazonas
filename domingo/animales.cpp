#include "pch.h"
#include <iostream>
#include <vector>

#define LIMITE 100

using namespace std;
using namespace System;

class Animales{
protected:
    bool visible = true, mata = true;
    int length, height = 3;
    int posicionX = 0, posicionY = 0;
    int aceleracion = 1;
    vector<string> repr;

public:
    int getX() { return posicionX; }
    int getY() { return posicionY; }
    
    bool esVisible() { return visible; }
    bool esPeligroso() { return mata; }
    
    void imprimir() {
        for (int i = 0; i < repr.size(); i++) {
            Console::SetCursorPosition(posicionX, posicionY + i);
            cout << repr[i];
        }
    };

    void mover() {
        if (posicionX + aceleracion < 0 || posicionX + aceleracion > LIMITE) visible = false;
        else {
            for (int i = 0; i < repr.size(); i++) {
                Console::SetCursorPosition(posicionX, posicionY + i);
                cout << "                    ";
            }
            posicionX += aceleracion;
            imprimir();
        }
    };

    bool checkColision(int x, int y) {
        bool colisionX = x >= posicionX && x < (posicionX + length);
        bool colisionY = y >= posicionY && y < (posicionY + height);
        return (colisionX || (colisionX && colisionY));
    }
};

class Cocodrilo : public Animales {
public:
    Cocodrilo() { 
        length = 20;
        posicionY = rand() % 22;
        repr.push_back("   (0)(0) - ^^^");
        repr.push_back(" [••]]     =====^^^^");
        repr.push_back("   [][]———[][]");
    }
};

class Boa : public Animales {
public:
    Boa() { 
        length = 5, height = 4;
        posicionY = rand() % 22;
        repr.push_back(" O__O");
        repr.push_back("    |");
        repr.push_back("    |");
        repr.push_back("    |__");
    }
};

class Tiburon : public Animales {
public:
    Tiburon() {
        length = 16;
        mata = false;
        posicionY = rand() % 22;
        repr.push_back("       __)\\_  ");
        repr.push_back(" (\\_.-'    a`-.");
        repr.push_back(" ( /~~````(/~^^`");
    }
 };