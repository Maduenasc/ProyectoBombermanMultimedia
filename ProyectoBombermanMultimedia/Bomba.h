#pragma once
enum Estado { normal, explosion, desaparecer };

using namespace System::Drawing;
class Bomba {
private:
	//Posicion en el nivel
	int ejex;
	int ejey;
	//Indice del sprite de la bomba
	int indicex;
	//Dimensiones del sprite de la bomba
	int alto;
	int ancho;
	//Ticks hasta la explosion
	int mecha;
	//Comprobacion de solidos adyacentes
	bool explotaArrAba;
	bool explotaDerIzq;
	//Comprobacion para no expandir la explosion sobre bloques solidos
	bool haySolidoArriba = false;
	bool haySolidoAbajo = false;
	bool haySolidoIzquierda = false;
	bool haySolidoDerecha = false;
	//Comprobacion para que el jugador no pueda pisar la bomba
	bool solida;

	//Estado actual de la bomba
	Estado estado;

	//datos de la explosion
	int indicexExp;
	int indiceyExp;

	int altoExp;
	int anchoExp;


public:
	Bomba(int x, int y) {
		this->ejex = x;
		this->ejey = y;
		estado = normal;

		ancho = 22;
		alto = 24;

		indicex = 0;
		mecha = 0;
		solida = false;

		indicexExp = 0;
		indiceyExp = 0;
		altoExp = 20;
		anchoExp = 20;

		explotaDerIzq = false;
		explotaArrAba = false;
	};


	//Getters y setters
	Estado getEstado() {
		return estado;
	}

	int getX() {
		return ejex;
	}
	void setX(int x) {
		this->ejex = x;
	}
	int getY() {
		return ejey;
	}
	void setY(int y) {
		this->ejey = y;
	}

	void setTiempo(int tiempo) {
		this->mecha = tiempo;
	}
	System::Drawing::Rectangle getRectangle() {
		return System::Drawing::Rectangle(ejex, ejey, 40, 40);
	}

	bool getHaySolidoArriba() {
		return haySolidoArriba;
	}
	bool getHaySolidoAbajo() {
		return haySolidoAbajo;
	}
	bool getHaySolidoDerecha() {
		return haySolidoDerecha;
	}
	bool getHaySolidoIzquierda() {
		return haySolidoIzquierda;
	}

	void setExplotaDerIzq(bool explota) {
		explotaDerIzq = explota;
	}
	void setExplotaArrAba(bool explota) {
		explotaArrAba = explota;
	}

	void setSolido(bool solida) {
		this->solida = solida;
	}
	bool isSolido() {
		return solida;
	}

	bool explotaDI() {
		return explotaDerIzq;
	}
	bool explotaAA() {
		return explotaArrAba;
	}


	//Recorre los sprite de la bomba
	void cambiarEstado() {
		if (indicex >= 0 && indicex < 2)
			indicex++;
		else {
			mecha++;
			indicex = 0;
		}
	}

	//Transito entre sprites de la explosion
	void cambiarExplosion() {
		if (indicexExp >= 0 && indicexExp < 3)
			indicexExp++;
		else {
			estado = desaparecer;
		}
	}

	//Dibuja en pantalla la bomba
	void dibujarBomba(Graphics^ g, Bitmap^ bomba, int ejexBomber, int ejeyBomber, int** grid) {

		if (hitboxBomba(ejexBomber, ejeyBomber, grid)) {
			System::Drawing::Rectangle porcionAUsar = System::Drawing::Rectangle(indicex * ancho, 0, ancho, alto);
			System::Drawing::Rectangle aumento = System::Drawing::Rectangle(ejex, ejey, 40, 40);
			g->DrawImage(bomba, aumento, porcionAUsar, GraphicsUnit::Pixel);
		}
		if (mecha == 5) { 
			estado = explosion; 
		}
	}

	~Bomba() {}


	//Comprueba que se pueda colocar la bomba
	bool hitboxBomba(int ejexBomber, int ejeyBomber, int** grid) {
		return (grid[ejeyBomber / 50][ejexBomber / 50] == 0 || grid[ejeyBomber / 50][ejexBomber / 50] == 2);
	}

	//Dibuja en pantalla la explosion
	void DibujarExplosion(Graphics^ g, Bitmap^ bomba, int** grid) {

		//Variables para asegurar que la bomba se coloca en el centro de la casilla
		int centroX = ejex + 40 / 2;
		int centroY = ejey + 40 / 2;

		System::Drawing::Rectangle tileCentro = System::Drawing::Rectangle(indicexExp * anchoExp, indiceyExp * altoExp, anchoExp, altoExp); // indiceY=0
		System::Drawing::Rectangle centro = System::Drawing::Rectangle(ejex, ejey, 50, 50);
		g->DrawImage(bomba, centro, tileCentro, GraphicsUnit::Pixel);

		//Se cormprueba el espacio a la izquierda
		if (grid[centroY / 50][(centroX - 50) / 50] != 1) {
			System::Drawing::Rectangle tileIzq = System::Drawing::Rectangle(indicexExp * anchoExp, indiceyExp + 2 * altoExp, anchoExp, altoExp); //indiceY = 2
			System::Drawing::Rectangle izquierda = System::Drawing::Rectangle(ejex - 50, ejey, 50, 50);
			g->DrawImage(bomba, izquierda, tileIzq, GraphicsUnit::Pixel);

			if (grid[centroY / 50][(centroX - 50) / 50] == 3) { grid[centroY / 50][(centroX - 50) / 50] = 2; haySolidoIzquierda = true; }
		}

		//Se comprueba el espacio a la derecha
		if (grid[centroY / 50][(centroX + 50) / 50] != 1) {
			System::Drawing::Rectangle tileDer = System::Drawing::Rectangle(indicexExp * anchoExp, indiceyExp + 4 * altoExp, anchoExp, altoExp); //indiceY = 4
			System::Drawing::Rectangle derecha = System::Drawing::Rectangle(ejex + 50, ejey, 50, 50);
			g->DrawImage(bomba, derecha, tileDer, GraphicsUnit::Pixel);

			if (grid[centroY / 50][(centroX + 50) / 50] == 3) { grid[centroY / 50][(centroX + 50) / 50] = 2; haySolidoDerecha = true; }
		}
		//Se comprueba el resto de la trayectoria horizontal de la explosion 
		if (grid[centroY / 50][(centroX + 100) / 50] != 1 && grid[centroY / 50][(centroX + 50) / 50] != 1 && !haySolidoDerecha) {
			System::Drawing::Rectangle tileSiguienteDer = System::Drawing::Rectangle(indicexExp * anchoExp, indiceyExp + 3 * altoExp, anchoExp, altoExp); //indiceY = 3
			System::Drawing::Rectangle SiguienteDer = System::Drawing::Rectangle(ejex + 100, ejey, 50, 50);
			g->DrawImage(bomba, SiguienteDer, tileSiguienteDer, GraphicsUnit::Pixel);

			if (grid[centroY / 50][(centroX + 100) / 50] == 3 && grid[centroY / 50][(centroX + 50) / 50] != 1)
				grid[centroY / 50][(centroX + 100) / 50] = 2;
		}

		if (grid[centroY / 50][(centroX - 100) / 50] != 1 && grid[centroY / 50][(centroX - 50) / 50] != 1 && !haySolidoIzquierda) {
			System::Drawing::Rectangle tileSiguienteIzq = System::Drawing::Rectangle(indicexExp * anchoExp, indiceyExp + 1 * altoExp, anchoExp, altoExp); //indiceY = 1
			System::Drawing::Rectangle SiguienteIzq = System::Drawing::Rectangle(ejex - 100, ejey, 50, 50);
			g->DrawImage(bomba, SiguienteIzq, tileSiguienteIzq, GraphicsUnit::Pixel);

			if (grid[centroY / 50][(centroX - 100) / 50] == 3 && grid[centroY / 50][(centroX - 50) / 50] != 1)
				grid[centroY / 50][(centroX - 100) / 50] = 2;
		}

		//Se repiten las comprobaciones en el eje y
		System::Drawing::Rectangle tileArrAba = System::Drawing::Rectangle(indicexExp * anchoExp, indiceyExp + 6 * altoExp, anchoExp, altoExp); //indiceY = 1
		System::Drawing::Rectangle Arr = System::Drawing::Rectangle(ejex, ejey - 50, 50, 50);
		System::Drawing::Rectangle Aba = System::Drawing::Rectangle(ejex, ejey + 50, 50, 50);

		if (grid[(centroY - 50) / 50][centroX / 50] != 1) { g->DrawImage(bomba, Arr, tileArrAba, GraphicsUnit::Pixel); }
		if (grid[(centroY - 50) / 50][centroX / 50] == 3) { grid[(centroY - 50) / 50][centroX / 50] = 2; haySolidoArriba = true; }
		if (grid[(centroY + 50) / 50][centroX / 50] != 1) { g->DrawImage(bomba, Aba, tileArrAba, GraphicsUnit::Pixel); }
		if (grid[(centroY + 50) / 50][centroX / 50] == 3) { grid[(centroY + 50) / 50][centroX / 50] = 2; haySolidoAbajo = true; }


		if (grid[(centroY - 100) / 50][centroX / 50] != 1 && grid[(centroY - 50) / 50][centroX / 50] != 1 && !haySolidoArriba) {
			System::Drawing::Rectangle tileSiguienteArr = System::Drawing::Rectangle(indicexExp * anchoExp, indiceyExp + 5 * altoExp, anchoExp, altoExp); //indiceY = 5
			System::Drawing::Rectangle SiguienteArr = System::Drawing::Rectangle(ejex, ejey - 100, 50, 50);
			g->DrawImage(bomba, SiguienteArr, tileSiguienteArr, GraphicsUnit::Pixel);

			if (grid[(centroY - 100) / 50][centroX / 50] == 3 && grid[(centroY - 50) / 50][centroX / 50] != 1) { grid[(centroY - 100) / 50][centroX / 50] = 2; }
		}

		if (grid[(centroY + 50) / 50][centroX / 50] != 1) {
			if (grid[(centroY + 100) / 50][centroX / 50] != 1 && !haySolidoAbajo) {
				System::Drawing::Rectangle tileSiguienteAba = System::Drawing::Rectangle(indicexExp * anchoExp, indiceyExp + 7 * altoExp, anchoExp, altoExp); //indiceY = 7
				System::Drawing::Rectangle SiguienteAba = System::Drawing::Rectangle(ejex, ejey + 100, 50, 50);
				g->DrawImage(bomba, SiguienteAba, tileSiguienteAba, GraphicsUnit::Pixel);
				if (grid[(centroY + 100) / 50][centroX / 50] == 3 && grid[(centroY + 50) / 50][centroX / 50] != 1) {
					grid[(centroY + 100) / 50][centroX / 50] = 2;
				}
			}
		}
		estado = explosion;
	}
	

};