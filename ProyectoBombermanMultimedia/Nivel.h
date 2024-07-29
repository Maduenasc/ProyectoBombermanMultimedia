#pragma 

#include <stdlib.h>
#include <ctime>
#include <iostream>

#define COLUMNAS 17
#define FILAS 15

using namespace System::Drawing;

class Nivel {
private:
	int **grid = nullptr;
public:
	Nivel() {
		grid = new int* [FILAS];
	}

	~Nivel() {}

	//Rellena la matriz de valores para después asignarles un bitmap y dibujarlos
	void rellenaGrid() {
		//Valor 0 es hueco de inicio
		//Valor 1 es son bordes del mapa, y bloques solidos interiores
		//Valor 2 es un hueco transitable
		//Valor 3 es bloque destructible
		srand(time(NULL()));
		for (int i = 0; i < FILAS; i++) {
			grid[i] = new int[COLUMNAS];
		}

		for (int i = 0; i < FILAS; i++) {
			for (int j = 0; j < COLUMNAS; j++) {
				//Bordes
				if (i == 0 || j == 0 || i == FILAS - 1 || j == COLUMNAS - 1)
					grid[i][j] = 1;
				else
				{
					//Bloques solidos en las posiciones pares
					if (i % 2 == 0 && j % 2 == 0)
						grid[i][j] = 1;
					else
					{
						//El personaje empieza en las posicion (1, 1), por lo que (1, 2) y(2, 1) deben de ser transitables
						if ((i == 1 && (j == 1 || j == 2)) || (j == 1 && i == 2) || (i == FILAS - 2 && (j == COLUMNAS - 2 || j == COLUMNAS - 3)) || (i == FILAS - 3 && j == COLUMNAS - 2)) {
							grid[i][j] = 0;
						}	
						else {
							grid[i][j] = rand() % 2 + 2;
						}
					}
				}
			}
		}
	}

	//Dibuja los bloques solidos y los destruibles
	void dibujarGrid(Graphics^ g, Bitmap^ solido, Bitmap^ destruible) {
		int x = 0;
		int y = 0;
		for (int i = 0; i < FILAS; i++)
		{
			x = 0;
			for (int j = 0; j < COLUMNAS; j++)
			{
				if (grid[i][j] == 1)
					g->DrawImage(solido, x, y, 50, 50);
				else
				{
					if (grid[i][j] == 3)
						g->DrawImage(destruible, x, y, 50, 50);
				}
				x += 50;
			}
			y += 50;
		}
	}

	//Dibuja los huecos libres
	void dibujarBase(Graphics^ g, Bitmap^ hueco) {

		int x = 0;
		int y = 0;
		for (int i = 0; i < FILAS; i++) {
			x = 0;
			for (int j = 0; j < COLUMNAS; j++) {

				if (grid[i][j] == 0 || grid[i][j] == 2)
					g->DrawImage(hueco, x, y, 50, 50);
				x += 50;
			}
			y += 50;
		}
	}

	int** getGrid() {
		return grid;
	}

	int getEspacio(int i, int j) {
		return grid[i][j];
	}

};
