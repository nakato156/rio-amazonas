#include "pch.h"
#include "animales.cpp"
#include <conio.h>
#include <time.h>

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
        cout << "  ";
        posicionX = 49;
        posicionY = 23;
        Console::SetCursorPosition(posicionX, posicionY);
        cout << repr;
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

        vector <Animales*> coleccion_animales;

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
                else if (tecla == 't') coleccion_animales.push_back(new Tiburon());
                else if (tecla == 'c') coleccion_animales.push_back(new Cocodrilo());
                else if (tecla == 'b') coleccion_animales.push_back(new Boa());

                cout << player;
            }

            posXPlayer = player.getX();
            posYPlayer = player.getY();

            for (int i = 0; i < coleccion_animales.size(); i++) {
                coleccion_animales[i]->mover();
                if (!coleccion_animales[i]->esVisible()) continue;
                if (!coleccion_animales[i]->esPeligroso()) continue;

                // verificando colisiones
                if (coleccion_animales[i]->checkColision(posXPlayer, posYPlayer)) { player.reset(); }
            }
            _sleep(60);
        }
    }
};

int main() {
    srand(time(NULL));
    Console::SetWindowSize(WIDTH_CONSOLE, HEIGHT_CONSOLE);
    Console::CursorVisible = false;
    
    Game juego;
    juego.init();
    
    return 0;
}