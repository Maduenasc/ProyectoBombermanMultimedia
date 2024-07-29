#pragma once
enum Direcciones{Arr, Aba, Izq, Der, No};

using namespace System::Drawing;

class Bomber {

private:
	//Vida del personaje
	int vidas;
	//Posicion del personaje
	int ejex;
	int ejey;
	//Indice de sprite
	int indicex;
	int indicey;
	//Alto sprite
	int alto;
	//Ancho sprite
	int ancho;
	//Velocidad en cada eje del personaje
	int vejex;
	int vejey;
	int patines;
	//Control de la direccion del personaje
	Direcciones direccion;
	Direcciones anterior;
	//Hitbox del personaje
	System::Drawing::Rectangle hitboxX;
	System::Drawing::Rectangle hitboxY;
		
public:

	Bomber() {
		//Spawn del jugador
		ejex = 50;
		ejey = 50;
		vidas = 3;

		//Empieza quieto
		vejex = 0;
		vejey = 0;
		patines = 0;

		//Sprites
		ancho = 18;
		alto = 26;
		indicex = 0;
		indicey = 0;

		//Direcciones
		direccion = No;
		anterior = Aba;
	}

	~Bomber(){}
	System::Drawing::Rectangle getRectangle() { 
		return System::Drawing::Rectangle(ejex + 2 * 3, ejey + 15 * 3, (ancho - 4) * 3, (alto - 15) * 3); 
	}

	void reiniciaBomberman() {
		ejex = 50;
		ejey = 10;
	}

	int getejex() {
		return ejex + 6;
	}

	int getejey() {
		return ejey + 45 + vejey;
	}

	int getVidas() {
		return vidas;
	}

	void setVidas(int _vidas) {
		vidas = _vidas;
	}

	Direcciones getDireccion() {
		return direccion;
	}

	void aumentaVelocidad(int _patines) {
		patines += _patines;
	}

	//Comprueba que el personaje pueda moverse a un cuadrado
	void compruebaHitbox(int **grid) {
		int x, y = 0;
		for (int i = 0; i < FILAS; i++) {
			x = 0;
			for (int j = 0; j < COLUMNAS; j++) {
				System::Drawing::Rectangle r1 = System::Drawing::Rectangle(x, y, 50, 50);
				if (grid[i][j] == 1 || grid[i][j] == 3) {
					if (hitboxX.IntersectsWith(r1)) vejex = 0;
					if (hitboxY.IntersectsWith(r1)) vejey = 0;
				}
				x += 50;
			}
			y += 50;
		}
	}

	//Selecciona al sprite de la imagen
	void dibujarBomberman(Graphics^ g, Bitmap^ bomber, int** grid) {
		hitboxX = System::Drawing::Rectangle(ejex + 6 + vejex, ejey + 45, (ancho - 5)*3, (alto - 15)*3);
		hitboxY = System::Drawing::Rectangle(ejex + 6, ejey + 45 + vejey, (ancho - 5) * 3, (alto - 16) * 3);

		g->DrawRectangle(Pens::Transparent, hitboxX);
		g->DrawRectangle(Pens::Transparent, hitboxY);

		compruebaHitbox(grid);

		System::Drawing::Rectangle tile = System::Drawing::Rectangle(indicex * ancho, indicey * alto, ancho, alto);
		System::Drawing::Rectangle desplazamiento = System::Drawing::Rectangle(ejex, ejey, ancho*3, alto*3);
		g->DrawImage(bomber, desplazamiento, tile, GraphicsUnit::Pixel);

		//Aumento la posicion en funcion del desplazamiento
		ejex += vejex;
		ejey += vejey;
	}

	//Desplaza al personaje
	void desplazaBomberman(Graphics^ g, Bitmap^ bomber, int **grid) {
		//Cuadramos las posiciones para arreglar bug visuales
		if (direccion == No || direccion == Aba || direccion == Arr) {
			ancho = 17;
		}
		else {
			ancho = 18;
		}
		switch (direccion) {

		case No:
			vejex = 0;
			vejey = 0;
			if (anterior = Arr)
			{
				indicex = 0;
				indicey = 0;
			}

			if (anterior = Izq)
			{
				indicex = 1;
				indicey = 3;
			}

			if (anterior = Der)
			{
				indicex = 1;
				indicey = 1;
			}

			if (anterior = Aba)
			{
				indicex = 0;
				indicey = 2;
			}

			break;
		case Der:
			indicey = 1;
			if (indicex >= 1 && indicex < 3) {
				indicex++;
			}
			else {
				indicex = 1;
			}
			vejex = 15 + patines;
			vejey = 0;
			anterior = Der;
			break;

		case Izq:
			indicey = 3;
			if (indicex >= 1 && indicex < 3) {
				indicex++;
			}
			else {
				indicex = 1;
			}
			vejex = -15 - patines;
			vejey = 0;
			anterior = Izq;
			break;

		case Aba:
			indicex = 0;
			if (indicey >= 1 && indicey < 3) {
				indicey++;
			}
			else {
				indicey = 1;
			}
			vejex = 0;
			vejey = 15 + patines;
			anterior = Aba;
			break;

		case Arr:
			indicey = 0;
			if (indicex >= 1 && indicex < 3) {
				indicex++;
			}
			else {
				indicex = 1;
			}
			vejex = 0;
			vejey = -15 - patines;
			anterior = Arr;
			break;
		}
		dibujarBomberman(g, bomber, grid);
	}

	void setDirecciones(Direcciones nuevaDireccion) {
		this->direccion = nuevaDireccion;
	}

	void perderVida() {
		ejex = 50;
		ejey = 10;
		this->anterior = Aba;
		vidas--;
	}

	void perderVida(int extremoIzquierda, int extremoDerecha, int extremoArriba, int extremoAbajo, int xcentroInicio,
		int xcentroFin, int ycentroInicio, int ycentroFin) {

		if (getejex() + 30 >= extremoIzquierda && getejex() + 10 <= extremoDerecha && (getejey() + 40 > ycentroInicio && getejey() + 10 < ycentroFin)) {
			perderVida();
		}
		else {
			if (getejey() + 30 >= extremoArriba && getejey() + 10 <= extremoAbajo && (getejex() + 40 > xcentroInicio && getejex() + 10 < xcentroFin)) {
				perderVida();
			}
		}
	}
};