#include "pch.h"
#include "animales.cpp"
#include <iostream>
#include <conio.h>
#include <thread>
#include <vector>

#define WIDTH_CONSOLE 100
#define HEIGHT_CONSOLE 24
#define ARRIBA 72
#define AVANZAR 77
#define ABAJO 80
#define RETROCEDER 75

using namespace std;
using namespace System;

class Nadador {
private:
    char repr = char(219);
    int color = 2;
    int posicionX = 49, posicionY = 23;
public:
    int getX() {
        return posicionX;
    }
    int getY() {
        return posicionY;
    }
    void reset() {
        Console::SetCursorPosition(posicionX, posicionY);
        cout << " ";
        Console::SetCursorPosition(49, 23);
    }
    void mover(int x, int y) {
        if (posicionX + x < 0 || posicionY + y < 0) return;
        else if (posicionX + x > WIDTH_CONSOLE || posicionY + y > HEIGHT_CONSOLE) return;
        Console::SetCursorPosition(posicionX, posicionY);
        cout << " ";
        posicionX += x;
        posicionY += y;
    }

    ~Nadador() {
        cout << "Ha terminado el juego";
        exit(EXIT_SUCCESS);
    }
    friend ostream& operator<<(ostream& os, const Nadador& obj) {
        Console::SetCursorPosition(obj.posicionX, obj.posicionY);
        Console::ForegroundColor = ConsoleColor(obj.color);
        os << obj.repr;
        Console::ForegroundColor = ConsoleColor(7);
        return os;
    }
};


class Game {
public:
    void init() {
        // se crea al nadador
        Nadador player;
        cout << player << endl;

        Cocodrilo* cocodrilo = new Cocodrilo();
        Boa* boa = new Boa();
        Tiburon* tiburon = new Tiburon();

        vector <Cocodrilo*> coleccion_cocodrilo;
        vector <Boa*> coleccion_boa;
        vector <Tiburon*> coleccion_tiburon;

        int posXPlayer, posYPlayer;

        while (true)
        {
            if (kbhit()) {
                char tecla = getch();
                
                if (tecla == AVANZAR) player.mover(1, 0);
                else if (tecla == RETROCEDER) player.mover(-1, 0);
                else if (tecla == ARRIBA) player.mover(0, -1);
                else if (tecla == ABAJO) player.mover(0, 1);
                
                // creacion de animales
                else if (tecla == 't') {
                    coleccion_tiburon.push_back(new Tiburon());
                }
                else if (tecla == 'c') {
                    coleccion_cocodrilo.push_back(new Cocodrilo());
                }
                else if (tecla == 'b') {
                    coleccion_boa.push_back(new Boa());
                }

                posXPlayer = player.getX();
                posYPlayer = player.getY();

                // verificando colisiones
                for (int i = 0; i < coleccion_cocodrilo.size(); i++) {
                    coleccion_cocodrilo[i]->crearCocodrilo();
                    int posX = coleccion_cocodrilo[i]->getX();
                    int posY = coleccion_cocodrilo[i]->getY();
                    if ((posX <= posXPlayer && (posX - 5) <= posXPlayer) || (posY <= player.getY() && (posY - 2) <= posYPlayer) ) player.reset();
                }
                for (int i = 0; i < coleccion_boa.size(); i++) {
                    coleccion_boa[i]->creaBoa();
                    int posX = coleccion_boa[i]->getX();
                    int posY = coleccion_boa[i]->getY();
                    if ((posX <= posXPlayer && (posX - 5) <= posXPlayer) || (posY <= player.getY() && (posY - 2) <= posYPlayer)) player.reset();
                }
                for (int i = 0; i < coleccion_tiburon.size(); i++) {
                    coleccion_tiburon[i]->pintaTiburon();
                    int posX = coleccion_tiburon[i]->getX();
                    int posY = coleccion_tiburon[i]->getY();
                    if ((posX <= posXPlayer && (posX - 5) <= posXPlayer) || (posY <= player.getY() && (posY - 2) <= posYPlayer)) player.reset();
                }
                
                cout << player;
            }
            _sleep(100);
        }
    }
};

int main() {
    srand(time(NULL));
    Console::SetWindowSize(WIDTH_CONSOLE, HEIGHT_CONSOLE);
    Console::CursorVisible = 0;
    
    Game juego;
    juego.init();
    
    return 0;
}