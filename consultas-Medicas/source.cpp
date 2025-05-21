using namespace std;
#include <Windows.h>
// #include <Datatime>
#include"resource.h"
#include "Declaraciones.h"




int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,PSTR cmdLine,int cShow) {
	
	hVentanaPrincipal = CreateDialog(hInst,MAKEINTRESOURCE (DLG_PRINCIPAL),NULL, cVentanaPrincipal);
    leerPacienteBin("paciente.bin");
    leerEspecialidadBin("Especialidad.bin");
    //leerEspecialidadBin("paciente.bin");
	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));
	ShowWindow(hVentanaPrincipal,cShow);
	while (GetMessage(&msg,NULL,NULL,NULL)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
   
   // guardarEnArchivos(pacienteIni);
    
    guardarPacienteBin(pacienteIni, "paciente.bin");
    guardarEspecialidadBin(espeIni, "Especialidad.bin");
    

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

    case WM_CLOSE: {
        
        DestroyWindow(hwnd);
        
    
    
    } break;

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
    HWND hbotonGuardar = GetDlgItem(hwnd, PAC_BTN_guardar);
    

    paciente* pacienteVacio = new paciente;
    pacienteVacio->id = 0;  // ID especial para paciente vac�o
    pacienteVacio->nombre = "Nuevo Paciente";
    pacienteVacio->sig = nullptr;pacienteVacio->ant = nullptr;


    switch (msg) {
    case WM_INITDIALOG: {
        SendMessage(hGenero, CB_ADDSTRING, 0, reinterpret_cast<LPARAM> ("Seleccione"));
        SendMessage(hGenero, CB_ADDSTRING, 0, reinterpret_cast<LPARAM> ("HOMBRE"));
        SendMessage(hGenero, CB_ADDSTRING, 0, reinterpret_cast<LPARAM> ("MUJER"));
        SendMessage(hGenero, CB_SETCURSEL, 2, 0);
         
        // Agregar el paciente vac�o al list box
        
        LlenarlistBox(hListBox, pacienteIni, pacienteVacio);

        // Establecer el paciente vac�o como seleccionado       
        // Aqu� puedes realizar m�s inicializaciones si es necesario
    } break;

    case WM_COMMAND: {

        switch (LOWORD(wParam)) {
        case PAC_LIST_ALLpacientes: {
            //leerPacienteBin("paciente.bin");
            if (HIWORD(wParam) == LBN_SELCHANGE) {
                int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                char buffer[256];
                if (selectedIndex != LB_ERR) {
                    if (selectedIndex != 0) {
                        paciente* aux =(paciente*)SendMessage(hListBox, LB_GETITEMDATA, selectedIndex, 0);
                        while (aux) {
                            if (aux != nullptr) {
                                SetWindowText(hNum, to_string(aux->id).c_str());
                                SetWindowText(hName, aux->nombre.c_str());
                                SetWindowText(hApellidoP, aux->apellidoPaterno.c_str());
                                SetWindowText(hApellidoM, aux->apellidoMaterno.c_str());
                                SetWindowText(hEmail, aux->correo.c_str());
                                SetWindowText(hTelefono, to_string(aux->telefono).c_str());
                                SetWindowText(hEdad, to_string(aux->edad).c_str());
                                SendMessage(hGenero, CB_SETCURSEL, aux->genero ? 0 : 1, 0);
                                EnableWindow(hNum, FALSE);
                                EnableWindow(hbotonGuardar, FALSE);
                                break;
                            }
                            aux = aux->sig;
                        }
                        
                    }
                    else {
                        limpiarDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero);
                        EnableWindow(hNum, true);
                        EnableWindow(hbotonGuardar, TRUE);

                    }
                }
            }
        } break;
        case PAC_BTN_guardar: {

            pacienteActual = new paciente; // Se inicializa el nodo
            obtenerDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero, pacienteActual);

            if (pacienteActual->id <= 0)  MessageBox(hwnd, "El ID no puede ser 0 � menor a 0.", "Error", MB_OK);
            else {
                paciente* PacienteExistente = BusquedaBinariaID(pacienteIni, pacienteActual->id);
                if (PacienteExistente != nullptr) {
                    MessageBox(hwnd, "El paciente con este ID ya existe.", "Error", MB_OK);
                    delete pacienteActual;

                }
                else {
                    agregarNodo(pacienteIni, pacienteFin, pacienteActual);
                    char msgBuffer[100];
                    sprintf_s(msgBuffer, "Paciente agregado: %s %s", pacienteActual->nombre.c_str(), pacienteActual->apellidoPaterno.c_str());
                    MessageBox(hwnd, msgBuffer, "Paciente Guardado", MB_OK);
                    quicksortPacientes(pacienteIni, pacienteFin);
                    limpiarDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero);

                    SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
                    LlenarlistBox(hListBox, pacienteIni, pacienteVacio);
                   

                }
            }

        } break;
        case PAC_BTN_modificar: {

            paciente* PacienteSeleccionado = new paciente;
            obtenerDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero, PacienteSeleccionado);
            paciente* Pacientebuscado = BusquedaBinariaID(pacienteIni, PacienteSeleccionado->id);

            if (Pacientebuscado) {
                Pacientebuscado->nombre = PacienteSeleccionado->nombre;
                Pacientebuscado->apellidoPaterno = PacienteSeleccionado->apellidoPaterno;
                Pacientebuscado->apellidoMaterno = PacienteSeleccionado->apellidoMaterno;
                Pacientebuscado->correo = PacienteSeleccionado->correo;
                Pacientebuscado->telefono = PacienteSeleccionado->telefono;
                Pacientebuscado->edad = PacienteSeleccionado->edad;
                Pacientebuscado->genero = PacienteSeleccionado->genero;
                int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

                if (selectedIndex != LB_ERR) {
                    // Borra la l�nea seleccionada
                    SendMessage(hListBox, LB_RESETCONTENT, 0, 0);

                    // Prepara el nuevo texto
                    LlenarlistBox(hListBox,pacienteIni,pacienteVacio);
                    EnableWindow(hNum, TRUE);
                    EnableWindow(hbotonGuardar, TRUE);

                    limpiarDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero);
                    EnableWindow(hNum, TRUE);
                    EnableWindow(hbotonGuardar, TRUE);
                }

            }

            delete PacienteSeleccionado;
        } break;
        case PAC_BTN_borrar: {
            paciente* elimnar = new paciente;
            obtenerDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero, elimnar);
            paciente* encontrado = BusquedaBinariaID(pacienteIni, elimnar->id);
            if (encontrado) {
                eliminarNodo(pacienteIni, pacienteFin, encontrado);
                int selectedIndex = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                if (selectedIndex != LB_ERR) {
                    SendMessage(hListBox, LB_DELETESTRING, selectedIndex, 0);
                }
                limpiarDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero);

            }
            delete elimnar;
            EnableWindow(hNum, TRUE);

        }break;
        case PAC_BTN_buscar: {
            paciente* filtro = new paciente;
            obtenerDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero, filtro);

            // Limpiar el ListBox antes de mostrar los resultados
            SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
            char msgBuffer[256];
            sprintf_s(msgBuffer, "%d - %s", pacienteVacio->id, pacienteVacio->nombre.c_str());
            int index = (int)SendMessage(hListBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(msgBuffer));
            SendMessage(hListBox, LB_SETITEMDATA, index, (LPARAM)pacienteVacio->id);

            paciente* temp = pacienteIni;
            while (temp) {
                bool coincide = true;

                if (filtro->id != 0 && temp->id != filtro->id) coincide = false;
                if (!filtro->nombre.empty() && temp->nombre != filtro->nombre) coincide = false;
                if (!filtro->apellidoPaterno.empty() && temp->apellidoPaterno != filtro->apellidoPaterno) coincide = false;
                if (!filtro->apellidoMaterno.empty() && temp->apellidoMaterno != filtro->apellidoMaterno) coincide = false;
                if (!filtro->correo.empty() && temp->correo != filtro->correo) coincide = false;
                if (filtro->telefono != 0 && temp->telefono != filtro->telefono) coincide = false;
                if (filtro->edad != 0 && temp->edad != filtro->edad) coincide = false;

                //                int generoSeleccionado = (int)SendMessage(hGenero, CB_GETCURSEL, 0, 0);
                                //if (generoSeleccionado != CB_ERR && temp->genero != filtro->genero) coincide = false;

                if (coincide) {
                    char buffer[256];
                    sprintf_s(buffer, "%d - %s %s %s - %s", temp->id,
                        temp->nombre.c_str(),
                        temp->apellidoPaterno.c_str(),
                        temp->apellidoMaterno.c_str(),
                        temp->genero ? "Hombre" : "Mujer");
                    int index = (int)SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
                    SendMessage(hListBox, LB_SETITEMDATA, index, temp->id);
                }

                temp = temp->sig;

            }
            limpiarDatosPaciente(hNum, hName, hApellidoP, hApellidoM, hEmail, hTelefono, hEdad, hGenero);
            MessageBox(hwnd,
                "Para mostrar todos los pacientes deje en blanco los campos y presione buscar.", // Mensaje a mostrar
                "Advertencia", // T�tulo del MessageBox
                MB_OK | MB_ICONWARNING); // Tipo de MessageBox (s�lo OK y un �cono de advertencia)
            delete filtro;
        }break;
        case PAC_BTN_regresar: {
            delete pacienteVacio;
            DestroyWindow(hwnd);
            ShowWindow(hVentanaPrincipal, SW_SHOW);
        } break;

        }
    } break;        
    case WM_CLOSE: {

        delete pacienteVacio;
        DestroyWindow(hwnd);
        ShowWindow(hVentanaPrincipal, SW_SHOW);
        break;
    }
    }

    
return FALSE;

}

LRESULT CALLBACK cVentanaMedicos(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){ 
    
    HWND hNum = GetDlgItem(hwnd, MED_CAP_cedulaMed);
    HWND hName = GetDlgItem(hwnd, MED_CAP_nombreMed);
    HWND hApellidoP = GetDlgItem(hwnd, MED_CAP_ApePatMed);
    HWND hApellidoM = GetDlgItem(hwnd, MED_CAP_ApeMatMed);
    HWND hEmail = GetDlgItem(hwnd, MED_CAP_email);
    HWND hTelefono = GetDlgItem(hwnd, MED_CAP_telefono);
    HWND hEspecialidad = GetDlgItem(hwnd, MED_COMBO_especialidad);
    

    HWND hListBox = GetDlgItem(hwnd, MED_LIST_ALLmed);
    HWND hbotonGuardar = GetDlgItem(hwnd, MED_BTN_agregar);

    medicos* medicoVacio = new medicos;
    medicoVacio->id = 0;  // ID especial para paciente vac�o
    medicoVacio->nombre = "Nuevo Paciente";
    medicoVacio->sig = nullptr;
    switch (msg) {
        case WM_INITDIALOG: {

            SendMessage(hEspecialidad, CB_RESETCONTENT, 0, 0);
            SendMessage(hEspecialidad, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Seleccione"));
            SendMessage(hEspecialidad
                , CB_SETCURSEL, 0, 0);
            especialidad*actual = espeIni;
            while (actual != nullptr) {

                SendMessage(hEspecialidad, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(actual->defEspecialidad.c_str()));
                actual = actual->sig;
            }


        } break;

        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
            case MED_BTN_agregar:{
            
            
            }break;
            case MED_BTN_Mod:{}break;
            case MED_BTN_borrar: {}break;
            case MED_BTN_masEspeci: {
                AbiertaDesdeMedicos = true;
                DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(DLG_ESPECIALIDAD),hwnd,cVentanaEspecialidades);
                AbiertaDesdeMedicos = false;
                SendMessage(hEspecialidad, CB_RESETCONTENT, 0, 0);
                SendMessage(hEspecialidad, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Seleccione"));
                SendMessage(hEspecialidad
                    , CB_SETCURSEL, 0, 0);
                especialidad* actual = espeIni;
                while (actual != nullptr) {

                    SendMessage(hEspecialidad, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(actual->defEspecialidad.c_str()));
                    actual = actual->sig;
                }

                

            
            }break;
            case MED_BTN_buscar:{}break;
            case MED_BTN_regresar: {
                delete medicoVacio;
                DestroyWindow(hwnd);
                //hVentanaPrincipal;
                ShowWindow(hVentanaPrincipal, SW_SHOW);

            }break;
             }
        }break;
        
        case WM_CLOSE: {
            delete medicoVacio;
            DestroyWindow(hwnd);
            ShowWindow(hVentanaPrincipal, SW_SHOW);
        }break;
    }    
    return FALSE;
}

LRESULT CALLBACK cVentanaConsultas(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
     
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
    HWND hClave = GetDlgItem(hwnd, ESP_CAP_clvEspecialidad);
    HWND hespecialidad= GetDlgItem(hwnd, ESP_CAP_especialidad);
    

    HWND hlistEsp = GetDlgItem(hwnd, ESP_LIST_Especialidades);
    HWND hlistAgregar = GetDlgItem(hwnd, ESP_BTN_agregarEsp);
    HWND hBtnEliminar = GetDlgItem(hwnd, ESP_BTN_elimiEsp);
    HWND hBtnPrinicpal= GetDlgItem(hwnd, ESP_BTN_regresarPrincipal);
    HWND hBtndoctor = GetDlgItem(hwnd, ESP_BTN_regresarDoctor);

    especialidad* vacio = new especialidad;
    strcpy_s(vacio->clave, "0");  // copiar "0" en clave
    vacio->defEspecialidad = "Nueva especialidad";
    vacio->sig = nullptr;
    vacio->ant = nullptr;


    switch (msg) {

    case WM_INITDIALOG: {
        LlenarListBoxEspecialidades(hlistEsp, espeIni, vacio);


        if (AbiertaDesdeMedicos) {

            EnableWindow(hBtnEliminar, FALSE);
            EnableWindow(hBtnPrinicpal, FALSE);
            EnableWindow(hBtndoctor, true);
        }
        else {
            EnableWindow(hBtnEliminar, true);
            EnableWindow(hBtnPrinicpal, true);
            EnableWindow(hBtndoctor, FALSE);
        }
        return TRUE;
    }break;

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case ESP_LIST_Especialidades: {
            if (HIWORD(wParam) == LBN_SELCHANGE) {
                int index = (int)SendMessage(hlistEsp, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR) {
                    especialidad* seleccionada = (especialidad*)SendMessage(hlistEsp, LB_GETITEMDATA, index, 0);

                    if (seleccionada != nullptr) {
                        // Verificamos si es la opci�n vac�a (clave "0" o cadena vac�a)
                        if (strcmp(seleccionada->clave, "0") == 0 || strlen(seleccionada->clave) == 0) {
                            SetWindowText(hClave, "");
                            SetWindowText(hespecialidad, "");
                            EnableWindow(hlistAgregar, TRUE);
                            EnableWindow(hClave, TRUE);
                            EnableWindow(hespecialidad, TRUE);
                        }
                        else {
                            SetWindowText(hClave, seleccionada->clave);
                            SetWindowText(hespecialidad, seleccionada->defEspecialidad.c_str());
                            EnableWindow(hlistAgregar, FALSE);
                            EnableWindow(hClave, FALSE);
                            
                        }
                    }
                }
            }
        } break;

        case ESP_BTN_agregarEsp: {
            espeActual = new especialidad;
            obtenerDatosEspecialidad(hClave, hespecialidad, espeActual);
            if (strcmp(espeActual->clave, "0") == 0) {
                MessageBox(hwnd, "No se puede agregar una especialidad con clave 0.", "Error", MB_OK | MB_ICONERROR);
                delete espeActual; // liberar memoria
                break;
            }
            if (claveEspecialidadRepetida(espeIni, espeActual->clave)) {
                MessageBox(hwnd, "Ya existe una especialidad con esa clave.", "Error", MB_ICONERROR);
                delete espeActual;
                break;
            }

            agregarNodo(espeIni, espeFin, espeActual);
            limpiarDatosEspecialidad(hClave, hespecialidad);

            SendMessage(hlistEsp, LB_RESETCONTENT, 0, 0);
            LlenarListBoxEspecialidades(hlistEsp, espeIni, vacio);
        
        }break;
        case ESP_BTN_modEsp: {
            especialidad* seleccion = new especialidad;
            obtenerDatosEspecialidad(hClave, hespecialidad, seleccion);

            // Buscar por clave
            especialidad* encontrada = espeIni;
            while (encontrada != nullptr && strcmp(encontrada->clave, seleccion->clave) != 0) {
                encontrada = encontrada->sig;
            }

            if (encontrada) {
                // Actualizar definici�n
                encontrada->defEspecialidad = seleccion->defEspecialidad;

                // Refrescar ListBox
                SendMessage(hlistEsp, LB_RESETCONTENT, 0, 0);
                LlenarListBoxEspecialidades(hlistEsp, espeIni, vacio);
                limpiarDatosEspecialidad(hClave, hespecialidad);
            }
            else {
                MessageBox(hwnd, "No se encontr� la especialidad para modificar.", "Error", MB_ICONERROR);
            }

            delete seleccion;
        } break;
        case ESP_BTN_elimiEsp: {
            int index = (int)SendMessage(hlistEsp, LB_GETCURSEL, 0, 0);
            if (index != LB_ERR) {
                especialidad* seleccionada = (especialidad*)SendMessage(hlistEsp, LB_GETITEMDATA, index, 0);

                // No eliminar si es la especialidad vac�a
                if (strcmp(seleccionada->clave, "0") == 0) {
                    MessageBox(hwnd, "No se puede eliminar la especialidad vac�a.", "Aviso", MB_ICONINFORMATION);
                    break;
                }

                eliminarNodo(espeIni, espeFin, seleccionada); // Aseg�rate de tener esta funci�n implementada

                SendMessage(hlistEsp, LB_RESETCONTENT, 0, 0);
                LlenarListBoxEspecialidades(hlistEsp, espeIni, vacio);
                limpiarDatosEspecialidad(hClave, hespecialidad);
            }
            else {
                MessageBox(hwnd, "Seleccione una especialidad para eliminar.", "Aviso", MB_ICONWARNING);
            }
        } break;
        case ESP_BTN_regresarDoctor: {
            EndDialog(hwnd, 0);
        }break;
        case ESP_BTN_regresarPrincipal: {
            DestroyWindow(hwnd);
            hVentanaPrincipal;
            ShowWindow(hVentanaPrincipal, SW_SHOW);
        } break;
        }
        
    }break;

    case WM_CLOSE: {
        if (AbiertaDesdeMedicos) {EndDialog(hwnd, 0);
    }
        else {
            DestroyWindow(hwnd);
            hVentanaPrincipal;
            ShowWindow(hVentanaPrincipal, SW_SHOW);
        }
        break;
    }
    }
    return FALSE; }

LRESULT CALLBACK cVentanaReporte(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) { 
     
    switch (msg) {
    case WM_CLOSE: {
        DestroyWindow(hwnd);
        hVentanaPrincipal;
        ShowWindow(hVentanaPrincipal, SW_SHOW);
        break;
    }
    }
    return FALSE; }