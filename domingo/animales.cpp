#include "pch.h"
#include <iostream>
#include <time.h>

using namespace std;
using namespace System;

class Amazonas {
protected:
    int x;
    int y;
    int dx;
    int dy;
    int ax;
    int ay;
    int posicionX = 0, posicionY = 0;
    int avanza = 1 ? rand() % 2 : -1;
public:
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    Amazonas() {}
    ~Amazonas() {}

};

class Cocodrilo : public Amazonas {
public:
    bool dibujar = true;
    Cocodrilo() {
        ax = 0;
        ay = 0;
        dx = 1 + rand() % 8; // tamanio salto horizontal
        dy = 1 + rand() % 2; // tamanio salto vertical
        x = 1;
        y = 2 + rand() % 20;
    }
    ~Cocodrilo() {}

    void pintaCocodrilo()
    {
        Console::SetCursorPosition(x, y);
        cout << "   _____";
        Console::SetCursorPosition(x, y + 1);
        cout << "| | ____=====";
        Console::SetCursorPosition(x, y + 2);
        cout << "   /   \\";
    }
    void borraCocodrilo()
    {
        dibujar = false;
        Console::SetCursorPosition(x, y);
        cout << "        ";
        Console::SetCursorPosition(x, y + 1);
        cout << "             ";
        Console::SetCursorPosition(x, y + 2);
        cout << "         ";
    }
    void saltoHorizontalCocodrilo() {
        if (x + dx < 0 || x + dx + ax > 100) {
            dx *= -1;
        }
        if (x > 95) {
            return;
        }
        x += dx;
    }
    void eliminaCocodrilo()
    {
        if (x > 95)
        {
            borraCocodrilo();
        }
    }
    void crearCocodrilo()
    {
        borraCocodrilo();
        saltoHorizontalCocodrilo();
        pintaCocodrilo();
        eliminaCocodrilo();
    }
};

class Boa : public Amazonas {
public:
    Boa() {
        ax = 0;
        ay = 0;
        dx = 1 + rand() % 8; // tamanio salto horizontal
        dy = 1 + rand() % 2; // tamanio salto vertical
        x = 99;
        y = 2 + rand() % 20;
    }
    ~Boa() {}
    bool dibujar = true;
    void pintaBoa() {
        if (dibujar) {
            Console::SetCursorPosition(x, y);
            cout << " O__O ";
            Console::SetCursorPosition(x, y + 1);
            cout << "     |";
            Console::SetCursorPosition(x, y + 2);
            cout << "     |__";
        }
    }
    void borraBoa() {
        Console::SetCursorPosition(x, y);
        cout << "      ";
        Console::SetCursorPosition(x, y + 1);
        cout << "      ";
        Console::SetCursorPosition(x, y + 2);
        cout << "        ";
        Console::SetCursorPosition(x, y + 3);
        cout << "             ";
    }
    void saltoHorizontalBoa() {
        if (x + dx < 0 || x + dx + ax > 98) {

            dx *= -1;
        }
        if (x <= 2) {
            dibujar = false;
            borraBoa();
        }
        x += dx;
    }
    void eliminarBoa()
    {
        if (x <= 2) {
            borraBoa();
        }
    }
    void creaBoa() {
        borraBoa();
        saltoHorizontalBoa();
        pintaBoa();
        eliminarBoa();
    }
};

class Tiburon : public Amazonas {
public:
    Tiburon() {
        ax = 0;
        ay = 0;
        dx = 1 + rand() % 8; // tamanio salto horizontal
        dy = 1 + rand() % 2; // tamanio salto vertical
        int opcion = 1 + rand() % 2;
        if (opcion == 0) {
            x = 1;
        }
        if (opcion == 1) {
            x = 90;
            dx = -dx;
        }
        y = 2 + rand() % 20;
    }
    bool dibujar = true;
    void pintaTiburon() {
        if (dibujar) {
            Console::SetCursorPosition(x, y);
            cout << "      __)\\_  ";
            Console::SetCursorPosition(x, y + 1);
            cout << "(\\_.-'    a`-.";
            Console::SetCursorPosition(x, y + 2);
            cout << "( /~~````(/~^^`";
        }
    }
    void borraTiburon() {
        Console::SetCursorPosition(x, y);
        cout << "               ";
        Console::SetCursorPosition(x, y + 1);
        cout << "                ";
        Console::SetCursorPosition(x, y + 2);
        cout << "                ";
    }
    void saltoHorizontalTiburon() {
        if (x + dx < 0 || x + dx + ax > 100) {
            dibujar = false;
            return borraTiburon();
        }
        x += dx;
    }
    void eliminaTiburon()
    {
        if (x > 100) {
            borraTiburon();
        }
        if (x < 3) {
            borraTiburon();
        }
    }
    void creaTiburon()
    {
        borraTiburon();
        saltoHorizontalTiburon();
        pintaTiburon();
        eliminaTiburon();
    }
};