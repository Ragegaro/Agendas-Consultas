#include <Windows.h>
#include"resource.h"
#include<iostream>

using namespace std;
struct paciente {
	int numeroDePaciente;
	string nombrePaciente;
	string correo;
	int telefono;
	bool genero;
	short edad;
	paciente* ant;
	paciente* sig;

};

LRESULT CALLBACK fVentanaPrincipal(HWND,UINT,WPARAM,LPARAM);


int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,PSTR cmdLine,int cShow) {
	
	HWND hVentanaPrincipal = CreateDialog(hInst,MAKEINTRESOURCE (DLG_PRINCIPAL),NULL, fVentanaPrincipal);
	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));
	ShowWindow(hVentanaPrincipal,cShow);
	while (GetMessage(&msg,NULL,NULL,NULL)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
	}

	return 0;
}
LRESULT CALLBACK fVentanaPrincipal(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CLOSE: {
			DestroyWindow(hwnd);
		} break;
		case WM_DESTROY: {
			PostQuitMessage(117); //Es ventanaPrincipal? si si, si ponlo
		}
		
	}




	return FALSE;
}

