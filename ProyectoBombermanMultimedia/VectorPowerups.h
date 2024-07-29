#pragma once
#include <vector>
#include "Powerups.h"

using namespace std;

class VectorPowerups {
private:
	vector<Powerup*> powerups;
	int** posiciones;

public:

	VectorPowerups() {
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
	~VectorPowerups() {}

	//Borra el powerup que esté en la posicion i
	void eliminaPowerup(int i) {
		powerups.erase(powerups.begin() + i);
	}
	//Vacia las posiciones colocadas para colocar powerup en el proximo nivel
	void vaciaPowerups() {
		for (int i = 0; i < FILAS; i++) {
			for (int j = 0; j < COLUMNAS; j++) {
				posiciones[i][j] = 0;
			}
		}
	}

	//Creamos un powerup
	void generaPowerup() {
		Powerup* powerup = new Powerup();
		powerups.push_back(powerup);
	}
	//Dibuja y transita entre los sprites de los powerups
	void dibujarPowerups(Graphics^ g, Bitmap^ powerup, int** grid) {
		for (int i = 0; i < powerups.size(); i++) {
			powerups[i]->dibujarPowerup(g, powerup, grid, posiciones);
			powerups[i]->cambiaPowerup();
		}
	}

	vector<Powerup*>* getVector() { 
		return &powerups; 
	}

};