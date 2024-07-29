#pragma once
#include "Monstruo.h"
#include <vector>
using namespace std;

class VectorMonstruos {
private:
	vector<Monstruo*> vectorMonstruos;
	//Posiciones donde hay montruos
	int** posiciones;

public:
	VectorMonstruos() {
		vectorMonstruos = vector<Monstruo*>();
		posiciones = new int* [FILAS];
		for (int i = 0; i < FILAS; i++) {
			posiciones[i] = new int[COLUMNAS];
		}
		for (int i = 0; i < FILAS; i++) {
			for (int j = 0; j < COLUMNAS; j++) {
				posiciones[i][j] = 0;
			}
		}
	}

	vector<Monstruo*> getVector() {
		return vectorMonstruos;
	}

	~VectorMonstruos() {}
	//Comprueba si los enemigos estan en el rango de explosion de la bomba
	void monstruosAreaExplosion(int extremoIzquierdo, int extremoDerecha, int extremoArriba, int extremoAbajo, int xcentroInicio,
		int xcentroFin, int ycentroInicio, int ycentroFin) {
		for (int i = 0; i < vectorMonstruos.size(); i++) {
			if (vectorMonstruos.at(i)->matarMonstruo(extremoIzquierdo, extremoDerecha, extremoArriba,
				extremoAbajo, xcentroInicio, xcentroFin, ycentroInicio, ycentroFin))
				vectorMonstruos.erase(vectorMonstruos.begin() + i);
		}
	}

	//Carga los enemigos
	void generaMonstruos() {
		Monstruo* monstruo = new Monstruo();
		vectorMonstruos.push_back(monstruo);
	}

	//Vacia las posiciones al terminar el nivel
	void eliminaMonstruos() {
		for (int i = 0; i < FILAS; i++) {
			for (int j = 0; j < COLUMNAS; j++) {
				posiciones[i][j] = 0;
			}
		}
	}

	//Dibuja los enemigos en pantalla
	void dibujarMonstruos(Graphics^ g, Bitmap^ monstruo, int** grid) {
		for (int i = 0; i < vectorMonstruos.size(); i++) {
			vectorMonstruos.at(i)->dibujarMonstruo(g, monstruo, grid, posiciones);
			vectorMonstruos.at(i)->cambiaEstado();
		}
	}

};