#pragma once
#include <string>
#include <fstream>
#include<iostream>
#include <commctrl.h>
// template<typename LL>
using namespace std;

#pragma region Listas ligadas

struct medicos {
	int id;
	string nombre;
	string apellidoPaterno;
	string apellidoMaterno;
	string email;
	int telefono;

	string especialidad;//creo que se podria hacer con algun entero y buscar en el archivo segun ese entero o con lista ligada de especialidades 
	medicos* ant;
	medicos* sig;
} *medicoIni= nullptr, *medicoFinal = nullptr, *MedicoActual = nullptr;

struct paciente {
	int id;
	string nombre;
	string apellidoPaterno;
	string apellidoMaterno;
	string correo;
	int telefono;
	bool genero;
	short edad;
	paciente* ant;
	paciente* sig;
} *pacienteIni, * pacienteFin,* pacienteActual;

enum estatus { completada, confirmada, cancelada, noLlego };

struct consultas {
	int id;
	SYSTEMTIME fechaConsulta;
	
	int numDeConusultorio;
	int cedula;
	string nombreMedico;
	// string apellidoPaternoMedico;
	string especialidad;
	estatus statusCita;
	int numPaciente;
	string nombrePaciente;
	// string apellidoPaternoPaciente;

	string resultado;
	string diagnostico;

	consultas *ant;
	consultas *sig;
} *consultasIni, *consultasFin, *consulActual;

///--- Lista extra de las sugeridas para el manejo de especialidades ---///
struct especialidad {
	
	char clave[4];
	string defEspecialidad;
	especialidad *sig;
	especialidad* ant;
} *espeIni, *espeFin, *espeActual;


#pragma endregion

#pragma region opLL
template<typename LL>
void agregarNodo(LL*& inicio, LL*& fin, LL* aux) {
	if (inicio!= nullptr) {	
		aux->ant = fin;
		fin->sig = aux;
		fin = aux;
		fin->sig = nullptr;
		
	}
	else {
		inicio = fin = aux;
		inicio->ant = nullptr;
		fin->sig = nullptr;
	}
} 
/* AGREGA AL FINAL DE LA LISTA------------FORMA DE USAR LA FUNCION AGREGAR NODO
agregarNodo(medicoIni, medicoFinal, MedicoActual);	agregarNodo(consultasIni, consultasFin, consulActual); agregarNodo(espeIni, espeFin, espeActual);
*/

template <typename LL>
void recorrerNodosCombobox(HWND hCOMBOBOX,LL* inicio) {
	LL* actual = inicio;
	SendMessage(hCOMBOBOX, CB_RESETCONTENT, 0, 0);

	while (actual != NULL) {
		SendMessage(hCOMBOBOX, CB_ADDSTRING, 0, (LPARAM)actual->dato.c_str());
		actual = actual->siguiente;
	}

}

template <typename LL>
void eliminarNodo(LL*& inicio, LL*& fin, LL* nodo) {
	if (!nodo) return;

	if (nodo == inicio)  // Si es el primer nodo
		inicio = nodo->sig;

	// Si es el último nodo
	if (nodo == fin)
		fin = nodo->ant;

	// Enlazar los nodos adyacentes
	if (nodo->ant)
		nodo->ant->sig = nodo->sig;
	if (nodo->sig)
		nodo->sig->ant = nodo->ant;

	delete nodo;
}

//-Modificar listas esta directamente en WIN API-//
#pragma endregion

#pragma region busquedaBinaria
template<typename LL>
int ContarNodos(LL* inicio) {
	int contador = 0;
	LL* aux = inicio;
	while (aux != nullptr) {
		contador++;
		aux = aux->sig;
	}
	return contador;
}
template<typename LL>
LL* obtenerNodoPorIndice(LL* inicio, int indice){
	LL* aux = inicio;
	int  i = 0;
	while (aux != nullptr && i < indice) {
		aux = aux -> sig;
		i++;
	}
	return aux;
}
template <typename LL>
LL* BusquedaBinariaID (LL* inicio, int idBuscado){
	int izquierda = 0, derecha = ContarNodos(inicio) - 1; 
	
	while (izquierda <= derecha) {
		int medio = (izquierda + derecha) / 2;

		LL* nodoMedio = obtenerNodoPorIndice(inicio, medio);

		if (nodoMedio == nullptr) return nullptr;

		if (nodoMedio->id == idBuscado) return nodoMedio;
		else if (idBuscado < nodoMedio->id) derecha = medio - 1;
		else izquierda = medio + 1;
	}
	return nullptr;
}
#pragma endregion

#pragma region quickSortPac_ID
void intercambiarDatosPaciente(paciente* a, paciente * b){
	swap(a->id, b->id);
	swap(a->nombre, b->nombre);
	swap(a->apellidoPaterno, b->apellidoPaterno);
	swap(a->apellidoMaterno, b->apellidoMaterno);
	swap(a->correo, b->correo);
	swap(a->telefono, b->telefono);
	swap(a->genero, b->genero);
	swap(a->edad, b->edad);
}
// Partición para quicksort (por ID)
paciente* partition(paciente* low, paciente* high) {
	int pivote = high->id;
	paciente* i = low->ant;

	for (paciente* j = low; j != high; j = j->sig) {
		if (j->id < pivote) {
			i = (i == nullptr) ? low : i->sig;
			intercambiarDatosPaciente(i, j);
		}
	}

	i = (i == nullptr) ? low : i->sig;
	intercambiarDatosPaciente(i, high);
	return i;
}

// Función recursiva de quicksort
void quicksortPacientes(paciente* low, paciente* high) {
	if (high != nullptr && low != high && low != high->sig) {
		paciente* p = partition(low, high);
		quicksortPacientes(low, p->ant);
		quicksortPacientes(p->sig, high);
	}
}
 
#pragma endregion

#pragma region mergeSortID
// Función para dividir la lista en dos mitades
medicos* mitadMedicos(medicos* cabeza) {
	if (!cabeza || !cabeza->sig)
		return cabeza;

	medicos* lento = cabeza;
	medicos* rapido = cabeza->sig;

	while (rapido && rapido->sig) {
		lento = lento->sig;
		rapido = rapido->sig->sig;
	}

	medicos* mitad = lento->sig;
	lento->sig = nullptr;   // Corta la lista en dos
	if (mitad) mitad->ant = nullptr;

	return mitad;
}

// Función para fusionar dos listas ordenadas (por id)
medicos* fusionarMedicos(medicos* lista1, medicos* lista2) {
	if (!lista1) return lista2;
	if (!lista2) return lista1;

	medicos* resultado = nullptr;

	if (lista1->id <= lista2->id) {
		resultado = lista1;
		resultado->sig = fusionarMedicos(lista1->sig, lista2);
		if (resultado->sig) resultado->sig->ant = resultado;
		resultado->ant = nullptr;
	}
	else {
		resultado = lista2;
		resultado->sig = fusionarMedicos(lista1, lista2->sig);
		if (resultado->sig) resultado->sig->ant = resultado;
		resultado->ant = nullptr;
	}

	return resultado;
}

// Función principal de merge sort
medicos* mergeSortMedicos(medicos* cabeza) {
	if (!cabeza || !cabeza->sig)
		return cabeza;

	medicos* segundaMitad = mitadMedicos(cabeza);

	cabeza = mergeSortMedicos(cabeza);
	segundaMitad = mergeSortMedicos(segundaMitad);

	return fusionarMedicos(cabeza, segundaMitad);
}

#pragma endregion



template <typename LL>
bool idBuscado(LL* tipoBusquedaIni,int idBuscado){
	LL* aux = tipoBusquedaIni;
	while (aux != NULL) {
		if (aux->id == idBuscado) return true;
		aux = aux->sig;
	}
	return false;
}

bool claveEspecialidadRepetida(especialidad* inicio, const char* claveBuscada) {
	especialidad* aux = inicio;
	while (aux != nullptr) {
		if (strcmp(aux->clave, claveBuscada) == 0)
			return true;
		aux = aux->sig;
	}
	return false;
}


#pragma region Implementar
template<typename LL>
LL buscarNombre_Lineal( LL*& inicio,LL* actual){

}

template<typename LL>
LL buscarApellido_Lineal(LL*& inicio, LL* actual) {}

//medicos y pacientes 
// citas 
void mergesort_ID() {}

//consultas* buscarFecha_Lineal() {}

#pragma endregion

void guardarPacienteBin(paciente* Ini, const string& nombreArchivo) {
	ofstream Archivo(nombreArchivo, ios::binary | ios::trunc);
	if (!Archivo.is_open()) { MessageBox(NULL, "Error al Abrir el archivo", "Error", MB_ICONERROR); return; }
	pacienteActual = Ini;
	while (pacienteActual != nullptr) {
		Archivo.write(reinterpret_cast<char*>(&pacienteActual->id), sizeof(pacienteActual->id));
		Archivo.write(reinterpret_cast<char*>(&pacienteActual->telefono), sizeof(pacienteActual->telefono));
		Archivo.write(reinterpret_cast<char*>(&pacienteActual->genero), sizeof(pacienteActual->genero));
		Archivo.write(reinterpret_cast<char*>(&pacienteActual->edad), sizeof(pacienteActual->edad));
		auto guardarString = [&](const string& str) {
			size_t len = str.size();
			Archivo.write(reinterpret_cast<char*>(&len), sizeof(len));
			Archivo.write(str.c_str(), len);
		};

		guardarString(pacienteActual->nombre);
		guardarString(pacienteActual->apellidoPaterno);
		guardarString(pacienteActual->apellidoMaterno);
		guardarString(pacienteActual->correo);

		pacienteActual = pacienteActual->sig;
	}

	Archivo.close();
}
void guardarMedicosBin(medicos* ini, const string& nombreArchivo) {
	ofstream Archivo(nombreArchivo, ios::binary | ios::trunc);
	if (!Archivo.is_open()) { MessageBox(NULL, "Error al abrir archivo", "Error", MB_ICONERROR); return; }

	medicos* actual = ini;
	while (actual != nullptr) {
		Archivo.write(reinterpret_cast<char*>(&actual->id), sizeof(actual->id));
		Archivo.write(reinterpret_cast<char*>(&actual->telefono), sizeof(actual->telefono));

		auto guardarString = [&](const string& str) {
			size_t len = str.size();
			Archivo.write(reinterpret_cast<char*>(&len), sizeof(len));
			Archivo.write(str.c_str(), len);
			};

		guardarString(actual->nombre);
		guardarString(actual->apellidoPaterno);
		guardarString(actual->apellidoMaterno);
		guardarString(actual->email);
		guardarString(actual->especialidad);

		actual = actual->sig;
	}
	Archivo.close();
}
void guardarConsultasBin(consultas* ini, const string& nombreArchivo) {
	ofstream Archivo(nombreArchivo, ios::binary | ios::trunc);
	if (!Archivo.is_open()) { MessageBox(NULL, "Error al abrir archivo", "Error", MB_ICONERROR); return; }

	consultas* actual = ini;
	while (actual != nullptr) {
		Archivo.write(reinterpret_cast<char*>(&actual->id), sizeof(actual->id));
		Archivo.write(reinterpret_cast<char*>(&actual->fechaConsulta), sizeof(actual->fechaConsulta));
		Archivo.write(reinterpret_cast<char*>(&actual->numDeConusultorio), sizeof(actual->numDeConusultorio));
		Archivo.write(reinterpret_cast<char*>(&actual->cedula), sizeof(actual->cedula));

		auto guardarString = [&](const string& str) {
			size_t len = str.size();
			Archivo.write(reinterpret_cast<char*>(&len), sizeof(len));
			Archivo.write(str.c_str(), len);
			};

		guardarString(actual->nombreMedico);
		guardarString(actual->especialidad);

		Archivo.write(reinterpret_cast<char*>(&actual->statusCita), sizeof(actual->statusCita));
		Archivo.write(reinterpret_cast<char*>(&actual->numPaciente), sizeof(actual->numPaciente));
		guardarString(actual->nombrePaciente);
		guardarString(actual->resultado);
		guardarString(actual->diagnostico);

		actual = actual->sig;
	}
	Archivo.close();
}
void guardarEspecialidadBin(especialidad* ini, const string& nombreArchivo) {
	ofstream Archivo(nombreArchivo, ios::binary | ios::trunc);
	if (!Archivo.is_open()) { MessageBox(NULL, "Error al abrir archivo", "Error", MB_ICONERROR); return; }

	espeActual= ini;
	while (espeActual != nullptr) {
		Archivo.write(reinterpret_cast<char*>(&espeActual->clave), sizeof(espeActual->clave)); // arreglo fijo 4 bytes

		size_t len = espeActual->defEspecialidad.size();
		Archivo.write(reinterpret_cast<char*>(&len), sizeof(len));
		Archivo.write(espeActual->defEspecialidad.c_str(), len);

		espeActual = espeActual->sig;
	}
	Archivo.close();
}






void leerPacienteBin(const string& nombreArchivo) {
	ifstream Archivo(nombreArchivo, ios::binary);
	if (!Archivo.is_open()) {
		MessageBox(NULL, "Error al abrir el archivo", "Error", MB_ICONERROR);
		return;
	}

	pacienteIni = nullptr;
	pacienteFin = nullptr;

	while (Archivo.peek() != EOF) {
		paciente* nuevo = new paciente;
		
		// Leer los campos básicos
		Archivo.read(reinterpret_cast<char*>(&nuevo->id), sizeof(nuevo->id));
		Archivo.read(reinterpret_cast<char*>(&nuevo->telefono), sizeof(nuevo->telefono));
		Archivo.read(reinterpret_cast<char*>(&nuevo->genero), sizeof(nuevo->genero));
		Archivo.read(reinterpret_cast<char*>(&nuevo->edad), sizeof(nuevo->edad));

		// Función auxiliar para leer strings
		auto leerString = [&](string& str) {
			size_t len;
			Archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
			char* buffer = new char[len + 1];
			Archivo.read(buffer, len);
			buffer[len] = '\0';
			str = buffer;
			delete[] buffer;
			};

		leerString(nuevo->nombre);
		leerString(nuevo->apellidoPaterno);
		leerString(nuevo->apellidoMaterno);
		leerString(nuevo->correo);
		agregarNodo(pacienteIni, pacienteFin, nuevo);
	}

	Archivo.close();
}
void leerMedicosBin(const string& nombreArchivo) {
	ifstream Archivo(nombreArchivo, ios::binary);
	if (!Archivo.is_open()) {
		MessageBox(NULL, "Error al abrir archivo", "Error", MB_ICONERROR);
		return;
	}

	medicoIni = medicoFinal = nullptr;

	while (Archivo.peek() != EOF) {
		medicos* nuevo = new medicos;

		Archivo.read(reinterpret_cast<char*>(&nuevo->id), sizeof(nuevo->id));
		Archivo.read(reinterpret_cast<char*>(&nuevo->telefono), sizeof(nuevo->telefono));

		auto leerString = [&](string& str) {
			size_t len;
			Archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
			char* buffer = new char[len + 1];
			Archivo.read(buffer, len);
			buffer[len] = '\0';
			str = buffer;
			delete[] buffer;
			};

		leerString(nuevo->nombre);
		leerString(nuevo->apellidoPaterno);
		leerString(nuevo->apellidoMaterno);
		leerString(nuevo->email);
		leerString(nuevo->especialidad);

		nuevo->ant = nullptr;
		nuevo->sig = nullptr;
		agregarNodo(medicoIni, medicoFinal, nuevo);
	}
	Archivo.close();
}
void leerConsultasBin(const string& nombreArchivo) {
	ifstream Archivo(nombreArchivo, ios::binary);
	if (!Archivo.is_open()) {
		MessageBox(NULL, "Error al abrir archivo", "Error", MB_ICONERROR);
		return;
	}

	consultasIni = consultasFin = nullptr;

	while (Archivo.peek() != EOF) {
		consultas* nuevo = new consultas;

		Archivo.read(reinterpret_cast<char*>(&nuevo->id), sizeof(nuevo->id));
		Archivo.read(reinterpret_cast<char*>(&nuevo->fechaConsulta), sizeof(nuevo->fechaConsulta));
		Archivo.read(reinterpret_cast<char*>(&nuevo->numDeConusultorio), sizeof(nuevo->numDeConusultorio));
		Archivo.read(reinterpret_cast<char*>(&nuevo->cedula), sizeof(nuevo->cedula));

		auto leerString = [&](string& str) {
			size_t len;
			Archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
			char* buffer = new char[len + 1];
			Archivo.read(buffer, len);
			buffer[len] = '\0';
			str = buffer;
			delete[] buffer;
			};

		leerString(nuevo->nombreMedico);
		leerString(nuevo->especialidad);

		Archivo.read(reinterpret_cast<char*>(&nuevo->statusCita), sizeof(nuevo->statusCita));
		Archivo.read(reinterpret_cast<char*>(&nuevo->numPaciente), sizeof(nuevo->numPaciente));
		leerString(nuevo->nombrePaciente);
		leerString(nuevo->resultado);
		leerString(nuevo->diagnostico);

		nuevo->ant = nullptr;
		nuevo->sig = nullptr;
		agregarNodo(consultasIni, consultasFin, nuevo);
	}
	Archivo.close();
}
void leerEspecialidadBin(const string& nombreArchivo) {
	ifstream Archivo(nombreArchivo, ios::binary);
	if (!Archivo.is_open()) {
		MessageBox(NULL, "Error al abrir archivo", "Error", MB_ICONERROR);
		return;
	}

	espeIni = espeFin = nullptr;

	while (Archivo.peek() != EOF) {
		especialidad* nuevo = new especialidad;

		Archivo.read(reinterpret_cast<char*>(&nuevo->clave), sizeof(nuevo->clave));

		size_t len;
		Archivo.read(reinterpret_cast<char*>(&len), sizeof(len));
		char* buffer = new char[len + 1];
		Archivo.read(buffer, len);
		buffer[len] = '\0';
		nuevo->defEspecialidad = buffer;
		delete[] buffer;

		nuevo->ant = nullptr;
		nuevo->sig = nullptr;
		agregarNodo(espeIni, espeFin, nuevo);
	}
	Archivo.close();
}


//-OBTENER DATOS DE WIN API-//
void obtenerDatosPaciente(HWND hNum, HWND hName, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEdad, HWND hGenero, paciente* pacienteActual) {
	char buffer[256] = { 0 }; // Variable local para evitar problemas de memoria
	
	GetWindowText(hNum, buffer, sizeof(buffer));
	pacienteActual->id = atoi(buffer);
	GetWindowText(hName, buffer, sizeof(buffer));
	pacienteActual->nombre = buffer;
	GetWindowText(hApellidoP, buffer, sizeof(buffer));
	pacienteActual->apellidoPaterno = buffer;
	GetWindowText(hApellidoM, buffer, sizeof(buffer));
	pacienteActual->apellidoMaterno = buffer;
	GetWindowText(hEmail, buffer, sizeof(buffer));
	pacienteActual->correo = buffer;
	GetWindowText(hTelefono, buffer, sizeof(buffer));
	pacienteActual->telefono = atoi(buffer);
	

	GetWindowText(hEdad, buffer, sizeof(buffer));
	pacienteActual->edad = (short)atoi(buffer);
#pragma region checar
	// Obtener el género seleccionado del ComboBox
	int generoIndex = SendMessage(hGenero, CB_GETCURSEL, 0, 0);
	pacienteActual->genero = (generoIndex == 0); // 0 = Hombre, 1 = Mujer
#pragma endregion


}
// algo asi debo agregar 
//HWND hNum, HWND hName, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEdad, HWND hGenero, ll* acutal
void obtenerDatosMedico(HWND hID, HWND hNombre, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEspecialidad, medicos* medicoActual) {
	char buffer[256] = { 0 };

	GetWindowText(hID, buffer, sizeof(buffer));
	medicoActual->id = atoi(buffer);

	GetWindowText(hNombre, buffer, sizeof(buffer));
	medicoActual->nombre = buffer;

	GetWindowText(hApellidoP, buffer, sizeof(buffer));
	medicoActual->apellidoPaterno = buffer;

	GetWindowText(hApellidoM, buffer, sizeof(buffer));
	medicoActual->apellidoMaterno = buffer;

	GetWindowText(hEmail, buffer, sizeof(buffer));
	medicoActual->email = buffer;

	GetWindowText(hTelefono, buffer, sizeof(buffer));
	medicoActual->telefono = atoi(buffer);

	// Leer especialidad como texto del ComboBox (si es texto)
	GetWindowText(hEspecialidad, buffer, sizeof(buffer));
	medicoActual->especialidad = buffer;
}
void obtenerDatosConsulta(HWND hID, HWND hFecha, HWND hConsultorio, HWND hCedula, HWND hMedico, HWND hEspecialidad,
	HWND hStatus, HWND hPaciente, HWND hNombrePaciente, HWND hResultado, HWND hDiagnostico, consultas* actual) {

	char buffer[256] = { 0 };

	GetWindowText(hID, buffer, sizeof(buffer));
	actual->id = atoi(buffer);

	// Fecha: suponiendo que usas SYSTEMTIME y controles DateTimePicker
	SYSTEMTIME st;
	SendMessage(hFecha, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
	actual->fechaConsulta = st;

	GetWindowText(hConsultorio, buffer, sizeof(buffer));
	actual->numDeConusultorio = atoi(buffer);

	GetWindowText(hCedula, buffer, sizeof(buffer));
	actual->cedula = atoi(buffer);

	GetWindowText(hMedico, buffer, sizeof(buffer));
	actual->nombreMedico = buffer;

	GetWindowText(hEspecialidad, buffer, sizeof(buffer));
	actual->especialidad = buffer;

	int index = SendMessage(hStatus, CB_GETCURSEL, 0, 0);
	actual->statusCita = (estatus)index;

	GetWindowText(hPaciente, buffer, sizeof(buffer));
	actual->numPaciente = atoi(buffer);

	GetWindowText(hNombrePaciente, buffer, sizeof(buffer));
	actual->nombrePaciente = buffer;

	GetWindowText(hResultado, buffer, sizeof(buffer));
	actual->resultado = buffer;

	GetWindowText(hDiagnostico, buffer, sizeof(buffer));
	actual->diagnostico = buffer;
}

void obtenerDatosEspecialidad(HWND hClave, HWND hDescripcion, especialidad* actual) {
	char buffer[256] = { 0 };

	GetWindowText(hClave, buffer, sizeof(buffer));
	strcpy_s(actual->clave, buffer);  

	GetWindowText(hDescripcion, buffer, sizeof(buffer));
	actual->defEspecialidad = buffer;
}


//-LIMPIAR DATOS-//
void limpiarDatosPaciente(HWND hNum, HWND hName, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEdad, HWND hGenero) {
	SetWindowText(hNum,"");
	SetWindowText(hName, "");
	SetWindowText(hApellidoP, "");
	SetWindowText(hApellidoM, "");
	SetWindowText(hEmail, "");
	SetWindowText(hTelefono, "");
	SetWindowText(hEdad, "");
	SendMessage(hGenero, CB_SETCURSEL, 2, 0);

}
//-PENDEIENTE MODIFICAR LAS DE ABAJO-//
void limpiarDatosMedico(HWND hID, HWND hNombre, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEspecialidad) {
	SetWindowText(hID, "");
	SetWindowText(hNombre, "");
	SetWindowText(hApellidoP, "");
	SetWindowText(hApellidoM, "");
	SetWindowText(hEmail, "");
	SetWindowText(hTelefono, "");
	SendMessage(hEspecialidad, CB_SETCURSEL, 40, 0);
}

void limpiarDatosEspecialidad(HWND hClave, HWND hDescripcion) {
	SetWindowText(hClave, "");
	SetWindowText(hDescripcion, "");
}

void limpiarDatosConsulta(HWND hID, HWND hFecha, HWND hConsultorio, HWND hCedula, HWND hMedico, HWND hEspecialidad,
	HWND hStatus, HWND hPaciente, HWND hNombrePaciente, HWND hResultado, HWND hDiagnostico) {

	SetWindowText(hID, "");

	// Limpiar DateTimePicker: establecer a fecha actual
	SYSTEMTIME st;
	GetLocalTime(&st);
	SendMessage(hFecha, DTM_SETSYSTEMTIME, (WPARAM)GDT_VALID, (LPARAM)&st);

	SetWindowText(hConsultorio, "");
	SetWindowText(hCedula, "");
	SetWindowText(hMedico, "");
	SetWindowText(hEspecialidad, "");

	SendMessage(hStatus, CB_SETCURSEL, 0, 0); // Asume que 0 es el valor por defecto

	SetWindowText(hPaciente, "");
	SetWindowText(hNombrePaciente, "");
	SetWindowText(hResultado, "");
	SetWindowText(hDiagnostico, "");
}


template <typename LB>
void LlenarlistBox(HWND hLis, LB* inicio, LB* vacio) {
	char msgBuffer[256];
	sprintf_s(msgBuffer, "%d - %s", vacio->id, vacio->nombre.c_str());
	int index = (int)SendMessage(hLis, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(msgBuffer));
	SendMessage(hLis, LB_SETITEMDATA, index, (LPARAM)vacio); // <--- GUARDA EL PUNTERO al paciente vacío

	LB* actual = inicio;
	while (actual != nullptr) {
		string texto = to_string(actual->id) + " - " + actual->nombre + " " + actual->apellidoPaterno;
		int index = (int)SendMessage(hLis, LB_ADDSTRING, 0, (LPARAM)texto.c_str());
		SendMessage(hLis, LB_SETITEMDATA, index, (LPARAM)actual); // <--- GUARDA EL PUNTERO al paciente real
		actual = actual->sig;
	}
}

void LlenarListBoxEspecialidades(HWND hListBox, especialidad* inicio, especialidad* vacio) {
	especialidad* aux = inicio;
	int index = 0;

	while (aux != nullptr) {
		std::string textoMostrar = std::string(aux->clave) + " - " + aux->defEspecialidad;
		index = (int)SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)textoMostrar.c_str());
		SendMessageA(hListBox, LB_SETITEMDATA, index, (LPARAM)aux);
		aux = aux->sig;
	}

	// Agregar el nodo vacío como última opción (opcional)
	index = (int)SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)"0 - Nueva especialidad");
	SendMessageA(hListBox, LB_SETITEMDATA, index, (LPARAM)vacio);
}


#pragma region Ventanas
//menu  (solo aparece en pantalla principal)
HMENU hMenuCitas;
///  ventanas
HWND hVentanaPrincipal;
HWND hVentanaPacientes;
HWND hVentanaMedicos;
HWND hVentanaConsultas;
HWND hVentanaEspecialidad;
HWND hVentanaReporte;
//HWND hVentanaLogIn;
//HWND hAlgoMas;

//declaracion de las ventana
//LRESULT CALLBACK cVentanaLogIn(HWND, UINT, WPARAM, LPARAM);			// ventanaLogin
LRESULT CALLBACK cVentanaPrincipal(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK cVentanaPaciente(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK cVentanaMedicos(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK cVentanaConsultas(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK cVentanaEspecialidades(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK cVentanaReporte(HWND, UINT, WPARAM, LPARAM);
// LRESULT CALLBACK cVentanaEasterEGG(HWND, UINT, WPARAM, LPARAM);		//Ventana de algo más?
bool AbiertaDesdeMedicos = false;

#pragma endregion

