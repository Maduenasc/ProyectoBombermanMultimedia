
#pragma once

#include <ctime>
#include <stdlib.h>

using namespace System::Drawing;


class Powerup {
private:
	//Posicion en la que se encuentra
	int fila;
	int columna;
	//Indice del sprite
	int indicex;
	int indicey;
	//Dimensiones
	int ancho;
	int alto;
	//Idintifica la mejora
	int tipo;
	//Señala si la mejora está presente en pantalla o no
	bool presente;


public:
	Powerup() {
		indicex = 0;
		indicey = 0;

		ancho = 16;
		alto = 16;

		tipo = rand() % 5 + 1;
		presente = false;
		fila = rand() % 13 + 1;
		columna = rand() % 15 + 1;

	}

	//Getters y setters
	System::Drawing::Rectangle getRectangleMejora() {
		return System::Drawing::Rectangle(columna * 50, fila * 50, ancho * 3, alto * 3);
	}
	int getTipoMejora() {
		return tipo;
	}

	//Cambia los sprites
	void cambiaPowerup() {
		switch (tipo) {
			//+1 bomba
		case 1:
			indicex = 0;

			if (indicey >= 0 && indicey < 1)
				indicey++;
			else
				indicey = 0;
			break;

			//Patear bombas
		case 2:
			indicex = 4;
			if (indicey == 0)
				indicey++;
			else
				indicey = 0;
			break;

			//Perder vida
		case 3:
			indicex = 5;
			if (indicey == 0)
				indicey++;
			else
				indicey = 0;
			break;

			//Aumentar velocidad de Bomberman
		case 4:
			indicex = 8;
			if (indicey == 0)
				indicey++;
			else
				indicey = 0;
			break;

			//+1 vida
		case 5:
			indicex = 9;
			if (indicey == 0)
				indicey++;
			else
				indicey = 0;
			break;
		}

	}

	//Si aún no esta el power-up en juego, lo coloca y dibuja
	void dibujarPowerup(Graphics^ g, Bitmap^ powerup, int** grid, int** powerups) {
		System::Drawing::Rectangle tile = System::Drawing::Rectangle(indicex * ancho, indicey * alto, ancho, alto);

		while (presente == false) {
			fila = rand() % 13 + 1;
			columna = rand() % 15 + 1;

			if (grid[fila][columna] == 3 && powerups[fila][columna] == 0) {
				presente = true;
				powerups[fila][columna] = 1;
			}
		}

		System::Drawing::Rectangle desplazamiento = System::Drawing::Rectangle(columna * 50, fila * 50, ancho * 3, alto * 3);
		g->DrawImage(powerup, desplazamiento, tile, GraphicsUnit::Pixel);
	}

	~Powerup() {}

};

