using namespace std;
#include <Windows.h>
// #include <Datatime>
#include"resource.h"
#include "Declaraciones.h"

//#include <gl/>

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
#pragma region LogInDesactivado

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
    centrarVentana(hwnd);
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
                hVentanaMedicos = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_MEDICOS), NULL, cVentanaMedicos);
                ShowWindow(hVentanaMedicos, SW_SHOW);
            } break;
            case ID_CONSULTAS: {
                ShowWindow(hwnd, SW_HIDE);
                hVentanaConsultas= CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_CONSULTAS), NULL, cVentanaConsultas);
                ShowWindow(hVentanaConsultas, SW_SHOW);
            }break;
            case ID_Especialidad: {
                ShowWindow(hwnd, SW_HIDE);
                hVentanaEspecialidad = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_ESPECIALIDAD), NULL, cVentanaEspecialidades);
                ShowWindow(hVentanaEspecialidad, SW_SHOW);
            }break;
            case ID_reporte: {
                ShowWindow(hwnd, SW_HIDE);
                hVentanaReporte = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_REPORTES), NULL, cVentanaReporte);
                ShowWindow(hVentanaReporte, SW_SHOW);
            
            }break;
          //  case ID_algoMas: {}break;

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
    HWND hNum = GetDlgItem(hwnd, PAC_CAP_idPaciente);
    HWND hName = GetDlgItem(hwnd, PAC_CAP_namePaciente);
    HWND hApellidoP = GetDlgItem(hwnd, PAC_CAP_ApePatPaciente);
    HWND hApellidoM = GetDlgItem(hwnd, PAC_CAP_ApeMatPaciente);
    HWND hEmail = GetDlgItem(hwnd, PAC_CAP_emailPaciente);
    HWND hTelefono = GetDlgItem(hwnd, PAC_CAP_telefonoPaciente);
    HWND hGenero = GetDlgItem(hwnd, PAC_COMBO_generoPaciente);
    HWND hEdad = GetDlgItem(hwnd, PAC_CAP_edadPaciente);
    HWND hListBox = GetDlgItem(hwnd, PAC_LIST_ALLpacientes); 
    
    switch (msg) {
    case WM_INITDIALOG:{
        SendMessage(hGenero, CB_ADDSTRING, 0, reinterpret_cast<LPARAM> ("HOMBRE"));
        SendMessage(hGenero, CB_ADDSTRING, 0, reinterpret_cast<LPARAM> ("MUJER"));
        SendMessage(hGenero, CB_SETCURSEL, -1, 0);
        centrarVentana(hwnd);
    }
        
    case WM_COMMAND: {
        switch (wParam) {
        case PAC_BTN_borrar: {
        
        /* NOTA:
        -Proximamente: Agregar  lista ligada de pacientes eliminados, para no usar un numero ya usado, en los ultimos 5 a�os
        - Junto con esto agregar un boton para reactivar pacientes
        */
        }break;
        case PAC_BTN_modificar: {// tiene mejoras esta seccion
            int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            char buffer[256];

            if (selectedIndex != LB_ERR) {
                SendMessage(hListBox, LB_GETTEXT, selectedIndex, (LPARAM)buffer);
                int numPaciente = atoi(buffer);
                paciente* aux = pacienteIni;
                while (aux) {
                    if (aux->numPaciente == numPaciente) {
                        SetWindowText(hNum, std::to_string(aux->numPaciente).c_str());
                        SetWindowText(hName, aux->nombrePaciente.c_str());
                        SetWindowText(hApellidoP, aux->apellidoPaterno.c_str());
                        SetWindowText(hApellidoM, aux->apellidoMaterno.c_str());
                        SetWindowText(hEmail, aux->correo.c_str());
                        SetWindowText(hTelefono, std::to_string(aux->telefono).c_str());
                        SetWindowText(hEdad, std::to_string(aux->edad).c_str());
                        SendMessage(hGenero, CB_SETCURSEL, aux->genero ? 0 : 1, 0);
                        EnableWindow(hNum, FALSE);
                        pacienteActual = aux;
                        break;
                    }
                    aux = aux->sig;
                }
            }
        
        }break;
        case PAC_BTN_guardar: {
            pacienteActual = new paciente; // Se inicializa el nodo
            obtenerDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero, pacienteActual);
            agregarNodo(pacienteIni, pacienteFin, pacienteActual);

            // Mensaje de confirmaci�n
            char msgBuffer[100];
            sprintf_s(msgBuffer, "Paciente agregado: %s %s", pacienteActual->nombrePaciente.c_str(), pacienteActual->apellidoPaterno.c_str());
            MessageBox(hwnd, msgBuffer, "Paciente Guardado", MB_OK);
           
            sprintf_s(msgBuffer, "%d - %s %s %s - %s ", pacienteActual->numPaciente, pacienteActual->nombrePaciente.c_str(),
            pacienteActual->apellidoPaterno.c_str(),pacienteActual->apellidoMaterno.c_str(), pacienteActual->genero ? "Hombre" : "Mujer");

            SendMessage(hListBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(msgBuffer));
            limpiarDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero);

           
        } break;
        case PAC_BTN_buscar: {}break;
        case PAC_BTN_regresar: {
            DestroyWindow(hwnd);
            ShowWindow(hVentanaPrincipal, SW_SHOW);
        } break;

        }
        break;
    }
    case WM_CLOSE: {
        DestroyWindow(hwnd);
       
        ShowWindow(hVentanaPrincipal, SW_SHOW);
        break;
    }
    }

    return FALSE;
}


LRESULT CALLBACK cVentanaMedicos(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { 
    centrarVentana(hwnd);
    switch (msg) {
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            hVentanaPrincipal; 
            ShowWindow(hVentanaPrincipal, SW_SHOW);
            break;
        }
    }    
    return FALSE;
}

LRESULT CALLBACK cVentanaConsultas(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    centrarVentana(hwnd);
    switch (msg) {
    case WM_CLOSE: {
        DestroyWindow(hwnd);
        hVentanaPrincipal;
        ShowWindow(hVentanaPrincipal, SW_SHOW);
        break;
    }
    }
    return FALSE; }

LRESULT CALLBACK cVentanaEspecialidades(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { 
    centrarVentana(hwnd);
    switch (msg) {
    case WM_CLOSE: {
        DestroyWindow(hwnd);
        hVentanaPrincipal;
        ShowWindow(hVentanaPrincipal, SW_SHOW);
        break;
    }
    }
    return FALSE; }

LRESULT CALLBACK cVentanaReporte(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { 
    centrarVentana(hwnd);
    switch (msg) {
    case WM_CLOSE: {
        DestroyWindow(hwnd);
        hVentanaPrincipal;
        ShowWindow(hVentanaPrincipal, SW_SHOW);
        break;
    }
    }
    return FALSE; }