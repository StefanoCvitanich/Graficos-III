
//---------------------------------------------------------------------------
#ifndef PG1_DIRECTINPUT_H
#define PG1_DIRECTINPUT_H
//---------------------------------------------------------------------------
#define DIRECTINPUT_VERSION 0x0800
//---------------------------------------------------------------------------
#include "input.h"
//---------------------------------------------------------------------------
#include <dinput.h>
//---------------------------------------------------------------------------
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
//---------------------------------------------------------------------------
#include "DLLExport.h"
//---------------------------------------------------------------------------
class DirectInput : public Input{
public:
	DllExport DirectInput();
	DllExport ~DirectInput();

	DllExport bool init(HINSTANCE hInstance, HWND hWnd);
	DllExport void deinit();

	// Mouse y Keyboard
	DllExport void acquire();
	DllExport void reacquire();
	DllExport void unacquire();
	DllExport void reset();

private:
	LPDIRECTINPUT8 m_lpObjectOne;
	LPDIRECTINPUT8 m_lpObjectTwo;

	LPDIRECTINPUTDEVICE8 m_lpKeyboard;
	LPDIRECTINPUTDEVICE8 m_lpMouse;

	DIMOUSESTATE m_kMouseTaken;
};
//---------------------------------------------------------------------------
#endif // DIRECTINPUT_H
//---------------------------------------------------------------------------
