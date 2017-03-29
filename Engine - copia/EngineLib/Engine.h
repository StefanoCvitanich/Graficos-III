#ifndef ENGINE_H
#define ENGINE_H
//========================================================================================
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Game.h"
#include "directinput.h"
#include "pg1_timer.h"
//========================================================================================
using namespace std;
//========================================================================================
class Engine{
public:
	DllExport Engine(HINSTANCE hinst, unsigned int uiW, unsigned int uiH);
	DllExport ~Engine();
	DllExport bool init();
	DllExport void run();
	DllExport void setGame(Game* a);

private:
	HINSTANCE hinstance;
	unsigned int uiWidth;
	unsigned int uiHeight;

	Window* w;
	Renderer* r;
	Game* g;
	DirectInput* i;
	pg1::Timer* _timer;
};
//========================================================================================
#endif