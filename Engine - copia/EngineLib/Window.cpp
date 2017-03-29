#include "Window.h"
//==================================================================================
Window::Window(){
}
//==================================================================================
Window::~Window(){
}
//==================================================================================
bool Window::init(HINSTANCE hInst, unsigned int uiWidth, unsigned int uiHeight){
	static TCHAR szWindowClass[] = _T("engine_fn");
	static TCHAR szTitle[] = _T("EngineFN");
	//------------------register Window-----------------------------------------
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = szWindowClass;
	//---------check if the window couldnt be registered------------------------
	if (!RegisterClassEx(&wc)){
		MessageBox(NULL, _T("ClassEx Register failed!"), _T("EngineFN"), NULL);
		return false;
	}
	//---------------create the Window------------------------------------------
	hWnd = CreateWindowEx(NULL,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW | WS_EX_CLIENTEDGE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		uiWidth, uiHeight,
		NULL,
		NULL,
		hInst,
		NULL);
	//---------check if the window couldnt be created---------------------------
	if (!hWnd){
		MessageBox(NULL, _T("Window Create failed!"), _T("EnginFN"), NULL);
		return false;
	}
	//--------------------------------------------------------------------------
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return true;
}
//==================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
//==================================================================================
void Window::setTitle(string title){
	SetWindowText( hWnd, title.c_str());
}
//==================================================================================