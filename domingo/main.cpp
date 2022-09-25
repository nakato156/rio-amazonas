#include "pch.h"
#include "animales.cpp"
#include <iostream>
#include <conio.h>
#include <thread>

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
        // Se inician los hilos de los animales

        // se crea al nadador
        Nadador player;
        cout << player << endl;

        Cocodrilo* cocodrilo = new Cocodrilo();
        Boa* boa = new Boa();
        Tiburon* tiburon = new Tiburon();

        Arreglo <Cocodrilo> coleccion_cocodrilo;
        Arreglo <Boa> coleccion_boa;
        Arreglo <Tiburon> coleccion_tiburon;

        while (true)
        {
            if (kbhit()) {
                char tecla = getch();
                if (tecla == AVANZAR) player.mover(1, 0);
                else if (tecla == RETROCEDER) player.mover(-1, 0);
                else if (tecla == ARRIBA) player.mover(0, -1);
                else if (tecla == ABAJO) player.mover(0, 1);
                else if (tecla == 't') {
                    coleccion_tiburon.append(new Tiburon());
                }
                else if (tecla == 'c') {
                    coleccion_cocodrilo.append(new Cocodrilo());
                }
                else if (tecla == 'b') {
                    coleccion_boa.append(new Boa());
                }

                for (int i = 0; i < coleccion_cocodrilo.length; i++) coleccion_cocodrilo[i]->crearCocodrilo();
                for (int i = 0; i < coleccion_boa.length; i++) coleccion_boa[i]->creaBoa();
                for (int i = 0; i < coleccion_tiburon.length; i++) coleccion_tiburon[i]->pintaTiburon();
                
                cout << player;

                // comprobar colision
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