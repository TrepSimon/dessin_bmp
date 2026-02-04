#include "Fenetre.h"

bool Fenetre::create_window(int largeur, int hauteur, const char* titre) {
	HINSTANCE instance = GetModuleHandleA(0);

	WNDCLASSA ws = {};
	ws.hInstance = instance;
	ws.hIcon = LoadIcon(instance, IDI_APPLICATION);
	ws.hCursor = LoadCursor(NULL, IDC_ARROW);
	ws.lpszClassName = titre;
	ws.lpfnWndProc = DefWindowProcA;

	if (!RegisterClassA(&ws)) {
		return false;
	}

	int style = WS_OVERLAPPEDWINDOW;

	HWND window = CreateWindowExA(0, titre, titre,
		style, 100, 100, largeur, hauteur, NULL, NULL, instance, NULL);

	if (window == NULL) {
		return false;
	}

	ShowWindow(window, SW_SHOW);

	return true;
}
