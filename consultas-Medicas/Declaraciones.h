#pragma once
#include <string>
template <typename LL>
struct miembroLista {
	LL tipoLista;
	miembroLista<LL>* sig;
	miembroLista<LL>* ant;
};

template <typename LL>
class listaLigadaDoble{};

struct medicos {
	int numCedula;
	string nombre;
	string email;
	string especialidad;//creo que se podria hacer con algun entero
	// y buscar en el archivo segun ese entero o con lista ligada
};

struct paciente {
	int numPaciente;
	string nombrePaciente;
	string apellidoP_Paciente;
	string apellidoM_Paciente;
	string correo;
	int telefono;
	bool genero;
	short edad;
};
/////////////////////////////
///--- Lista extra ---///
struct especialidad {
	char clave[3];
	string defEspecialidad;
};
//////////////////////

struct consultas {
/*
  ID de cita
fecha
dia de la semana
hora
horario
status
#consultorio
///
Numero de paciente
nombrePaciente
///
cedula
nombreMedico
Especialidad

status de la cita
Diagnostico
*/
};

///  ventanas
HWND hVentanaPrincipal;
HWND hVentanaPacientes;
HWND hVentanaMedicos;
HWND hVentanaConsultas;
HWND hVentanaEspecialidad;
HWND hVentanaReporte;
//HWND hAlgoMas;

//menu
HMENU hMenuCitas;

//cargade la ventana
//LRESULT CALLBACK cVentanaLogIn(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaPrincipal(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaPaciente(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaMedicos(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaConsultas(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaEspecialidades(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaReporte(HWND, UINT, WPARAM, LPARAM);

//Ventana de algo más?
// LRESULT CALLBACK cVentanaEasterEGG(HWND, UINT, WPARAM, LPARAM);







/////////////////////////////////////
