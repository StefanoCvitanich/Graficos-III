#define _CRT_SECURE_NO_DEPRECATE
#include "Engine.h"
#include <sstream>
//==================================================================================
Engine::Engine(HINSTANCE hinst, unsigned int uiW, unsigned int uiH)
	:
	w(new Window()),
	r(new Renderer()),
	g(NULL),
	i(new DirectInput()),
	hinstance(hinst),
	uiWidth(uiW),
	uiHeight(uiH),
	_timer(new pg1::Timer)
{
	AllocConsole();
	freopen("CONIN$", "r",stdin);
	freopen("CONOUT$", "w",stdout);
	freopen("CONOUT$", "w",stderr);
	}
//==================================================================================
Engine::~Engine(){
	delete g;
	g = NULL;
	delete r;
	r = NULL;
	delete w;
	w = NULL;
	delete i;
	i = NULL;
	delete _timer;
	_timer = NULL;
}
//==================================================================================
bool Engine::init(){
	if (!w->init(hinstance, uiWidth, uiHeight))
		return false;
	//------------------------------------------
	if (!r->init(w->hWnd, uiWidth, uiHeight))
		return false;
	//------------------------------------------
	if (!i->init(hinstance, w->hWnd))
		return false;
	//------------------------------------------
	if (!g->init(*r))
		return false;
	//------------------------------------------
	if (_timer)	_timer->firstMeasure();

	else return false;
	//------------------------------------------
	return true;
}
//==================================================================================
void Engine::run(){
	MSG Msg;

	while (!g->isDone())
	{
		static std::stringstream showFps;
		showFps.str("");
		showFps << "Engine (" << _timer->fps() << " FPS)";
		w->setTitle(showFps.str());

		i->reacquire();
		r->beginFrame();
		g->frame(*r, *i, *_timer);
		_timer->measure();
		r->endFrame();

		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)){
			switch (Msg.message){
				case WM_QUIT:
				{
					g->setDone(true);
					break;
				}
			}
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}

	g->deinit();
}
//==================================================================================
void Engine::setGame(Game* a){
	g = a;
}
//==================================================================================