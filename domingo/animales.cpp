#include "pch.h"
#include <iostream>
#include <time.h>
#include <conio.h>

#define LIMITE 98

using namespace std;
using namespace System;

class Amazonas {
protected:
    int x, y;
    int velocidad;
    int avanza = 1 ? rand() % 2 : -1;
    
public:
    int getX() {
        return x;
    }

    int getY() {
        return y;
    }


};

class Cocodrilo : public Amazonas {
public:
    Cocodrilo() {
        velocidad = 1 + rand() % 8; // tamanio salto horizontal
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
        Console::SetCursorPosition(x, y);
        cout << "        ";
        Console::SetCursorPosition(x, y + 1);
        cout << "             ";
        Console::SetCursorPosition(x, y + 2);
        cout << "         ";
    }
    void saltoHorizontalCocodrilo() {
        if (x + velocidad < 0 || x + velocidad > LIMITE) return;
        x += velocidad;
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
        velocidad = 1 + rand() % 8; // tamanio salto horizontal
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
        if (x + velocidad <= 3 || x + velocidad > LIMITE) {
            dibujar = false;
            return borraBoa();
        }
        x += velocidad;
    }
    void eliminarBoa()
    {
        if (x <= 3) {
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
        velocidad = 1 + rand() % 8; // tamanio salto horizontal
        int opcion = 1 + rand() % 2;
        
        x = opcion ? 90 : 1;
        if (opcion == 90) velocidad = -1 * velocidad;
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
        if (x +  velocidad < 0 || x + velocidad > LIMITE) {
            dibujar = false;
            return borraTiburon();
        }
        x += velocidad;
    }
    void eliminaTiburon()
    {
        if (x < 5 || x > LIMITE) {
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

template <typename T>
class Arreglo {
public:
    int length = 0;
    T** arreglo = new T * [1];

    void append(T* elemento) {
        if (length == 0) arreglo[0] = elemento;
        else {
            T** nuevo_arr = new T * [length + 1];
            for (int i = 0; i < length; i++) nuevo_arr[i] = arreglo[i];
            nuevo_arr[length + 1] = elemento;
            arreglo = nuevo_arr;
        }
        length++;
    }

    void pop() {
        T** nuevo_arr = new T * [length - 1];
        for (int i = 0; i < length - 1; i++) nuevo_arr[i] = arreglo[i];
        arreglo = nuevo_arr;
    }

    void remove(int pos = 0) {
        T** nuevo_arr = new T * [length - 1];
        for (int i = 0; i < length - 1; i++) {
            if (i == pos) continue;
            nuevo_arr[i] = arreglo[i];
        }
        arreglo = nuevo_arr;
    }
    T* operator [](unsigned int index) { return arreglo[index]; }
};