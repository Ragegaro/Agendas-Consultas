using namespace std;
#include <Windows.h>
#include <fstream>
// #include <Datatime>
#include"resource.h"
#include "Declaraciones.h"

//  "DATA GRID" EN WIN API  //
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
//////////////////////////////////////



int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,PSTR cmdLine,int cShow) {
	
	hVentanaPrincipal = CreateDialog(hInst,MAKEINTRESOURCE (DLG_PRINCIPAL),NULL, cVentanaPrincipal);
	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));
	ShowWindow(hVentanaPrincipal,cShow);
	while (GetMessage(&msg,NULL,NULL,NULL)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
#pragma region VentanaLogIn

/*LRESULT CALLBACK fVentanaLogIn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INITDIALOG: {
        hCombo = GetDlgItem(hwnd, COMBO_typeUser);
        SendMessage(hCombo, CB_ADDSTRING, NULL, reinterpret_cast<LPARAM>("VENDEDOR"));
        SendMessage(hCombo, CB_ADDSTRING, NULL, reinterpret_cast<LPARAM>("CLIENTE"));
        SendMessage(hCombo, CB_SETCURSEL, (WPARAM)0, NULL);
        return TRUE;
    }

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case BTN_logIn: {

            hUser = GetDlgItem(hwnd, CAP_USER);
            hPassword = GetDlgItem(hwnd, CAP_PASSWORD);
            hCombo = GetDlgItem(hwnd, COMBO_typeUser);
            hremeber = GetDlgItem(hwnd, CHECK_RememberUser);
            int iTextLength = GetWindowTextLength(hUser);
            int cojoxtLength = GetWindowTextLength(hCombo);
            char combo[20];

            if (HIWORD(wParam) == BN_CLICKED) {
                /* char name[100];
                 char password[20];
                 bool remeber;
                 int iTextLength = GetWindowTextLength(hUser);
                 int cojoxtLength = GetWindowTextLength(hCombo);

                 if (iTextLength < 1) {
                     MessageBox(hwnd, "Escribe algo", "ERROR", MB_OK);
                 }
                 else {
                     GetWindowText(hUser, name, iTextLength + 1);
                     GetWindowText(hPassword,password,iTextLength+1);

                       /// funcion para checar usuarios

                    // ShowWindow(hwnd, SW_HIDE);
                     //HWND hVentanaPrincipal = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, cVentanaPrincipal);
                     ShowWindow(hVentanaPrincipal, SW_SHOW);
                 }*/
  /*              if (iTextLength < 1) MessageBox(hwnd, "Escriba algo en nombre de usuario", "ERROR", MB_OK);
                else {
                    // corregir la logica para checar si exitste el usuario
                      //prueba(hUser, hPassword, hCombo, iTextLength, cojoxtLength + 1);
                    ShowWindow(hwnd, SW_HIDE);
                    HWND hVentanaPrincipal = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, cVentanaPrincipal);
                    ShowWindow(hVentanaPrincipal, SW_SHOW);
                }
            }

            SetWindowText(hUser, "");
            break;
        }
        case BTN_SingIn: {
            if (HIWORD(wParam) == BN_CLICKED) {
                MessageBox(hwnd, "Funcion en desarrollo", "ERROR", MB_OK);
            }
            break;
        }
        }
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE;
}




*/
#pragma endregion


LRESULT CALLBACK cVentanaPrincipal(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
        case WM_INITDIALOG: {
            hMenuCitas = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
            if (hMenuCitas) { SetMenu(hwnd, hMenuCitas); DrawMenuBar(hwnd); }
        } break;

        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
            case BTN_PRINC_LogOut: {
                MessageBox(hwnd, "Funcion en desarrollo", "ERROR", MB_OK);

            }break;
            case ID_PACIENTES: {
                ShowWindow(hwnd, SW_HIDE);
                hVentanaPacientes = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_PACIENTE), NULL, cVentanaPaciente);
                ShowWindow(hVentanaPacientes, SW_SHOW);
            }break;
            case ID_MEDICOS: {
                ShowWindow(hwnd, SW_HIDE);
                hVentanaPacientes = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_PACIENTE), NULL, cVentanaPaciente);
                ShowWindow(hVentanaPacientes, SW_SHOW);
            } break;
            case ID_CONSULTAS: {}break;
            case ID_Especialidad: {}break;
            case ID_reporte: {}break;
            case ID_algoMas: {}break;
            case ID_salir: {
                DestroyWindow(hwnd); PostQuitMessage(117);
            }break;
            }

        }break;


        case WM_CLOSE: {DestroyWindow(hwnd);} break;
        case WM_DESTROY: { PostQuitMessage(117); break; /*Es ventanaPrincipal ? si si, si ponlo*/ }
		
	}
	return FALSE;
}

LRESULT CALLBACK cVentanaPaciente(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            HWND hVentanaPrincipal = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_PRINCIPAL), NULL, cVentanaPrincipal);
            ShowWindow(hVentanaPrincipal, SW_SHOW);
            break;
        }
    }
    return FALSE;
}

LRESULT CALLBACK cVentanaMedicos(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { return FALSE; }

LRESULT CALLBACK cVentanaConsultas(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { return FALSE; }

LRESULT CALLBACK cVentanaEspecialidades(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { return FALSE; }

LRESULT CALLBACK cVentanaReporte(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { return FALSE; }