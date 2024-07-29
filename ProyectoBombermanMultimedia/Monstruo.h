#pragma once
#include <ctime>
#include <stdlib.h>

using namespace System::Drawing;
enum Estado_Monstruo { Muerto, Vivo };

class Monstruo {

private:
	//Posicion en el grid
	int fila;
	int columna;
	//Posicion en pantalla
	int ejex;
	int ejey;
	//Desplazamiento
	int vejex;
	int vejey;
	//Indice del sprite
	int indicex;
	int indicey;
	//Dimensiones
	int ancho;
	int alto;
	//Para comprobarciones auxiliares
	bool enPantalla;
	bool giro;
	bool seleccionarMovimiento;
	int Movimiento;

	Estado_Monstruo estado;


public:
	Monstruo() {
		ejex = 0;
		ejey = 0;
		vejex = 5;
		vejey = 5;
		fila = rand() % 13 + 1;
		columna = rand() % 13 + 2;
		indicex = 0;
		indicey = 0;
		ancho = 16;
		alto = 16;
		enPantalla = false;
		giro = false;
		seleccionarMovimiento = true;

		estado = Vivo;
	}
	~Monstruo() {}

	System::Drawing::Rectangle getRectangle() {
		return System::Drawing::Rectangle(ejex, ejey, 50, 50);
	}

	//Transita entre sprites del enemigo
	void cambiaEstado() {
		if (giro == false) {
			indicex++;
			if (indicex == 5)
				giro = true;
		}
		if (giro == true) {
			indicex--;
			if (indicex == 0)
				giro = false;
		}
	}

	//Dibuja al monstruo enemigo
	void dibujarMonstruo(Graphics^ g, Bitmap^ monstruo, int** grid, int** monstruos) {
		System::Drawing::Rectangle tile = System::Drawing::Rectangle(indicex * ancho, indicey * alto, ancho, alto);
		while (enPantalla == false) {
			fila = rand() % 12 + 2;
			columna = rand() % 13 + 2;

			if (grid[fila][columna] == 2 && monstruos[fila][columna] == 0) {
				enPantalla = true;
				ejex = columna * 50;
				ejey = fila * 50;
				monstruos[fila][columna] = 1;
			}
		}
		System::Drawing::Rectangle desplazamiento = System::Drawing::Rectangle(ejex, ejey, 40, 40);
		g->DrawImage(monstruo, desplazamiento, tile, GraphicsUnit::Pixel);
		enPantalla = true;
		while (seleccionarMovimiento) {
			//Selecciona una direccion al azar para moverse
			Movimiento = rand() % 4 + 1;
			switch (Movimiento) {
			case 1: 
				if (grid[ejey / 50][(ejex + 40) / 50] == 2 || grid[ejey / 50][(ejex + 40) / 50] == 0) {
					vejex = 10;
					vejey = 0;
					seleccionarMovimiento = false;
				}
				break;
			case 2: 
				if (grid[ejey / 50][(ejex - 10) / 50] == 2 || grid[ejey / 50][(ejex - 10) / 50] == 0) {
					vejex = -10;
					vejey = 0;
					seleccionarMovimiento = false;
				}
				break;
			case 3:
				if (grid[(ejey - 10) / 50][ejex / 50] == 2 || grid[(ejey - 10) / 50][ejex / 50] == 0) {
					vejex = 0;
					vejey = -10;
					seleccionarMovimiento = false;
				}
				break;
			case 4:
				if (grid[(ejey + 50) / 50][ejex / 50] == 2 || grid[(ejey + 50) / 50][ejex / 50] == 0) {
					vejex = 0;
					vejey = 10;
					seleccionarMovimiento = false;
				}
				break;
			}
		}
		ejex += vejex;
		ejey += vejey;
		//Si choca tiene que volver a elegir una direccion
		if ((Movimiento == 1 && (grid[ejey / 50][(ejex + 40) / 50] == 3 || grid[ejey / 50][(ejex + 40) / 50] == 1)) ||
			(Movimiento == 2 && (grid[ejey / 50][(ejex - 10) / 50] == 3 || grid[ejey / 50][(ejex - 10) / 50] == 1)) ||
			(Movimiento == 3 && (grid[(ejey - 10) / 50][ejex / 50] == 3 || grid[(ejey - 10) / 50][ejex / 50] == 1)) ||
			(Movimiento == 4 && (grid[(ejey + 50) / 50][ejex / 50] == 3 || grid[(ejey + 50) / 50][ejex / 50] == 1)))
			seleccionarMovimiento = true;
	}
	//Comprueba si el enemigo está en el area de la bomba
	bool matarMonstruo(int extremoIzquierdo, int extremoDerecha, int extremoArriba, int extremoAbajo, int xcentroInicio,
		int xcentroFin, int ycentroInicio, int ycentroFin) {

		if (ejex + 30 >= extremoIzquierdo && ejex + 10 <= extremoDerecha && (ejey + 30 > ycentroInicio && ejey + 20 < ycentroFin)) {
			return true;
		}
		else {
			if (ejey + 30 >= extremoArriba && ejey + 10 <= extremoAbajo && (ejex + 30 > xcentroInicio && ejex + 20 < xcentroFin)) {
				return true;
			}
		}
		return false;
	}


};