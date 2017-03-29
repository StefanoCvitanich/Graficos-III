//Cvitanich, Morales
#include "engine.h"
#include "pacman.h"
//===============================================================================================
using namespace std;
//===============================================================================================
static const unsigned int width = 1280;
static const unsigned int heigth = 720;
//===============================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine eng(hInstance, width, heigth);

	Game* a = new Pacman();
	eng.setGame(a);

	if (!eng.init()) return 1;

	eng.run();

	return 0;
}
//===============================================================================================