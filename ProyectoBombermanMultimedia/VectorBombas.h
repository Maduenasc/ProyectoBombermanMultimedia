#pragma once
#include "Bomba.h"
#include <vector>

using namespace std;

class VectorBombas {

private:
	vector<Bomba*> vectorBombas;
	int maxBombas;

public:
	VectorBombas() {
		maxBombas = 1;
	}
	~VectorBombas(){}

	vector<Bomba*> getVectorBombas() {
		return vectorBombas;
	}

	void setTotalBombas(int maxbombas) {
		this->maxBombas = maxbombas;
	}
	int getTotalBombas() {
		return maxBombas;
	}

	//Dibuja las transiciones de la bomba en pantalla
	void dibujarVectorBomba(Graphics^ g, Bitmap^ bomba, Bitmap^ explosion, int ejexBomber, int ejeyBomber, int** grid) {
		for (int i = 0; i < vectorBombas.size(); i++) {
			switch (vectorBombas.at(i)->getEstado()) {
			case Estado::normal:
				vectorBombas.at(i)->dibujarBomba(g, bomba, ejexBomber, ejeyBomber, grid);
				vectorBombas.at(i)->cambiarEstado();
				break;
			case Estado::explosion:
				vectorBombas.at(i)->DibujarExplosion(g, explosion, grid);
				vectorBombas.at(i)->cambiarExplosion();
				break;
			case Estado::desaparecer:
				vectorBombas.erase(vectorBombas.begin() + i);
				break;
			}
		}
	}

	//Creamos una bomba y la añadimos a las puestas
	void generaBomba(int ejex, int ejey, int** grid) {
		if (vectorBombas.size() < maxBombas) {
			Bomba* bomba = new Bomba(ejex, ejey);

			int centroX = bomba->getX() + 40 / 2;
			int centroY = bomba->getY() + 40 / 2;

			if (grid[centroY / 50][(centroX - 50) / 50] != 1 || grid[centroY / 50][(centroX + 50) / 50] != 1){
				bomba->setExplotaDerIzq(true);
			}

			if (grid[(centroY - 50) / 50][centroX / 50] != 1 || grid[(centroY + 50) / 50][centroX / 50] != 1){
				bomba->setExplotaArrAba(true);
			}

			vectorBombas.push_back(bomba);
		}
	}
	
};