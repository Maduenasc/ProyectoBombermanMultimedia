#include "MenuDeJuego.h"
#include <Windows.h>

using namespace ProyectoBombermanMultimedia;

int main() {
	Application::EnableVisualStyles();

	Application::Run(gcnew MenuDeJuego());

	return 0;
}
