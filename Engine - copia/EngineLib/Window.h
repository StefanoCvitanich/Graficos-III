#ifndef WINDOW_H
#define WINDOW_H
//========================================================================================
#include <windows.h>
#include <tchar.h>
#include <string>
using namespace std;
//========================================================================================
#include "DLLExport.h"
//========================================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//========================================================================================
//Se encarga de registrar y crear la ventana
class Window{
public:
	HWND hWnd; //Handler de la ventana
	DllExport Window();
	DllExport ~Window();
	DllExport bool init(HINSTANCE hInst, unsigned int uiWidth, unsigned int uiHeight);
	DllExport void setTitle(string title);
};
//========================================================================================
#endif