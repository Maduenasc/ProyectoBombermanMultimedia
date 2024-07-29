#pragma once

#include "Nivel.h"
#include "Bomber.h"
#include "VectorBombas.h"
#include "VectorPowerups.h"
#include "VectorMonstruos.h"
#include <iostream>

class Sistema {
private:
	//Nuestro mapa actual
	Nivel* nivel;
	int nivelActual;
	//El pj
	Bomber* Bomberman;
	//Vector de bombas
	VectorBombas* bombas;
	//Vector de powerups
	VectorPowerups* vpowerups;
	//Vector de monstruos
	VectorMonstruos* monstruos;
	//Controla la patada
	bool patearBombas;

public:
	Sistema() {
		nivel = new Nivel();	
		Bomberman = new Bomber(); 
		bombas = new VectorBombas();
		vpowerups = new VectorPowerups();
		monstruos = new VectorMonstruos();
		nivelActual = 1;
		patearBombas = false;
	}
	~Sistema() {}
	int getNivelActual() {
		return nivelActual;
	}

	Bomber* getBomberman() {
		return Bomberman;
	}

	VectorMonstruos* getMonstruos() {
		return monstruos;
	}

	VectorPowerups* getPowerups() {
		return vpowerups;
	}

	void avanzaNivel() {
		nivelActual++;
		monstruos->eliminaMonstruos();
		vpowerups->vaciaPowerups();
		Bomberman->reiniciaBomberman();
	}

	//Genero un nivel
	void crearNivel() {
		nivel->rellenaGrid();
	}

	void pateaBombas() {
		if (patearBombas == true) {
			for (int i = 0; i < bombas->getVectorBombas().size(); i++)
			{
				if (bombas->getVectorBombas()[i]->getEstado() == normal && Bomberman->getRectangle().IntersectsWith(bombas->getVectorBombas()[i]->getRectangle()))
				{
					if (Bomberman->getDireccion() == Aba && nivel->getEspacio((bombas->getVectorBombas()[i]->getY() + 50) / 50, (bombas->getVectorBombas()[i]->getX()) / 50) == 2) {
						bombas->getVectorBombas()[i]->setY(bombas->getVectorBombas()[i]->getY() + 50);
						bombas->getVectorBombas()[i]->setTiempo(0);
					}
					if (Bomberman->getDireccion() == Arr && nivel->getEspacio((bombas->getVectorBombas()[i]->getY() - 50) / 50, (bombas->getVectorBombas()[i]->getX()) / 50) == 2) {
						bombas->getVectorBombas()[i]->setY(bombas->getVectorBombas()[i]->getY() - 50);
						bombas->getVectorBombas()[i]->setTiempo(0);
					}
					if (Bomberman->getDireccion() == Der && nivel->getEspacio((bombas->getVectorBombas()[i]->getY()) / 50, (bombas->getVectorBombas()[i]->getX() + 50) / 50) == 2) {
						bombas->getVectorBombas()[i]->setX(bombas->getVectorBombas()[i]->getX() + 50);
						bombas->getVectorBombas()[i]->setTiempo(0);
					}
					if (Bomberman->getDireccion() == Izq && nivel->getEspacio((bombas->getVectorBombas()[i]->getY()) / 50, (bombas->getVectorBombas()[i]->getX() - 50) / 50) == 2) {
						bombas->getVectorBombas()[i]->setX(bombas->getVectorBombas()[i]->getX() - 50);
						bombas->getVectorBombas()[i]->setTiempo(0);
					}
				}
			}
		}
	}

	void equipaPowerup() {
		for (int i = 0; i < vpowerups->getVector()->size(); i++) {
			if (Bomberman->getRectangle().IntersectsWith(vpowerups->getVector()->at(i)->getRectangleMejora())) {
				switch (vpowerups->getVector()->at(i)->getTipoMejora()) {
					//+1 bomba
				case 1: 
					bombas->setTotalBombas(bombas->getTotalBombas() + 1);
					break;
					//Patear bombas
				case 2:
					patearBombas = true;
					break;
					//-1 vida (calavera)
				case 3: 
					Bomberman->setVidas(Bomberman->getVidas() - 1);
					break;
					//Aumenta velocidad (patines)
				case 4: 
					Bomberman->aumentaVelocidad(5);
					break;
					//+1 vida (corazon)
				case 5: 
					Bomberman->setVidas(Bomberman->getVidas() + 1);
					break;
				}
				vpowerups->eliminaPowerup(i);
			}
		}
	}

	void perderVidaMonstruo() {
		for (int i = 0; i < monstruos->getVector().size(); i++) {
			if (Bomberman->getRectangle().IntersectsWith(monstruos->getVector().at(i)->getRectangle()))
				Bomberman->perderVida();
		}
	}

	void perderVidaBomba() {
		int extremoIzquierda, extremoDerecha, extremoArriba, extremoAbajo, xcentroInicio, xcentroFin, ycentroInicio, ycentroFin;
		for (int i = 0; i < bombas->getVectorBombas().size(); i++) {
			extremoIzquierda = bombas->getVectorBombas()[i]->getX() - 100;
			extremoDerecha = bombas->getVectorBombas()[i]->getX() + 150;
			extremoArriba = bombas->getVectorBombas()[i]->getY() - 100;
			extremoAbajo = bombas->getVectorBombas()[i]->getY() + 150;
			xcentroInicio = bombas->getVectorBombas()[i]->getX();
			ycentroInicio = bombas->getVectorBombas()[i]->getY();
			xcentroFin = bombas->getVectorBombas()[i]->getX() + 50;
			ycentroFin = bombas->getVectorBombas()[i]->getY() + 50;

			if (bombas->getVectorBombas()[i]->getEstado() == explosion) {
				//si no ha expandido (tiene un bloque fijo adyacente)
				if (!bombas->getVectorBombas()[i]->explotaAA()) {
					extremoArriba = ycentroInicio;
					extremoAbajo = ycentroFin;
				}

				if (!bombas->getVectorBombas()[i]->explotaDI()) {
					extremoIzquierda = xcentroInicio;
					extremoDerecha = xcentroFin;
				}

				//si ha roto algun bloque en los adyacentes
				if (bombas->getVectorBombas().at(i)->getHaySolidoArriba())
					extremoArriba = ycentroInicio - 50;
				if (bombas->getVectorBombas().at(i)->getHaySolidoAbajo())
					extremoAbajo = ycentroFin + 50;
				if (bombas->getVectorBombas().at(i)->getHaySolidoDerecha())
					extremoDerecha = xcentroFin + 50;
				if (bombas->getVectorBombas().at(i)->getHaySolidoIzquierda())
					extremoIzquierda = xcentroInicio - 50;


				Bomberman->perderVida(extremoIzquierda, extremoDerecha, extremoArriba, extremoAbajo, xcentroInicio, xcentroFin, ycentroInicio, ycentroFin);
				monstruos->monstruosAreaExplosion(extremoIzquierda, extremoDerecha, extremoArriba, extremoAbajo, xcentroInicio, xcentroFin, ycentroInicio, ycentroFin);
			}
		}

	}

	//Dibujo los elementos del juego
	void dibujarJuego(Graphics^ g, Bitmap^ hueco, Bitmap^ solido, Bitmap^ destruible, Bitmap^ bomber, Bitmap^bomba, Bitmap^ explosion, Bitmap^ powerups, Bitmap^ monstruo) {
		nivel->dibujarBase(g, hueco);
		vpowerups->dibujarPowerups(g, powerups, nivel->getGrid());
		nivel->dibujarGrid(g, solido, destruible);
		Bomberman->desplazaBomberman(g, bomber, nivel->getGrid());
		bombas->dibujarVectorBomba(g, bomba, explosion, Bomberman->getejex(), Bomberman->getejey(), nivel->getGrid());
		monstruos->dibujarMonstruos(g, monstruo, nivel->getGrid());
		equipaPowerup();
		pateaBombas();

		perderVidaBomba();
		perderVidaMonstruo();

	}
	
	//Metodo que crea enemigos y powerups
	void generaPowerupsYEnemigos() {
		vpowerups->generaPowerup();
		monstruos->generaMonstruos();
	}

	void aniadeBomba() {
		bombas->generaBomba(Bomberman->getejex(), Bomberman->getejey(), nivel->getGrid());
	}

};