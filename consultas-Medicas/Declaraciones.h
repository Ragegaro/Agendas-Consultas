#pragma once
#include <string>
#include <fstream>
#include<iostream>
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

	string especialidad;//creo que se podria hacer con algun entero y buscar en el archivo segun ese entero o con lista ligada
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


template <typename LL>
bool idBuscado(LL* tipoBusquedaIni,int idBuscado){
	LL* aux = tipoBusquedaIni;
	while (aux != NULL) {
		if (aux->id == idBuscado) return true;
		aux = aux->sig;
	}
	return false;
}

template<typename LL>
LL buscarNombre_Lineal( LL*& inicio,LL* actual){

}

template<typename LL>
LL buscarApellido_Lineal(LL*& inicio, LL* actual) {}

//consultas* buscarFecha_Lineal() {}

//medicos y pacientes 
template <typename LL>

// citas 
void mergesort_ID(){}

void ASASguardarEnArchivos(paciente* Ini) {

	
	ofstream archivo("prueba de lsita ligada.txt",ios::app);
	if (!archivo.is_open()) {
		cout << " archivo no se pudo abrir \n"; return;
	}
	if (Ini == nullptr) {
		archivo << "No hay pacientes registrados." << endl;
		archivo.close();
		return;
	}

	while (Ini != nullptr) {

		archivo << Ini->id << endl;
		archivo << Ini->nombre << " " << Ini->apellidoPaterno << " " << Ini->apellidoMaterno << endl;
		archivo << Ini->correo << endl;
		archivo << Ini->telefono << endl;
		archivo <<(Ini->genero == 0 ? "Mujer" : "Hombre") << endl;
		archivo << "Edad: " << Ini->edad << endl;
		
		archivo << "----------------------------------------" << endl;
		
		

		Ini = Ini->sig;

	}
	archivo.close();

}

void guardarPacienteBin(paciente* Ini, const string& nombreArchivo) {
	ofstream Archivo(nombreArchivo, ios::binary | ios::trunc);
	if (!Archivo.is_open()) { MessageBox(NULL, "Error al Abrir el archivo", "Error", MB_ICONERROR); return; }
	pacienteActual = Ini;

}

void guardarEnArchivosMedicos(medicos* Ini) {
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
void obtenerDatosMedicos(){}
void obtenerDatosConsulta() {}
void obtenerDatosEspecialidad() {}

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
void limpiarDatosMedicos(HWND hNum, HWND hName, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEdad, HWND hGenero) {}
void limpiarDatosCitas(HWND hNum, HWND hName, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEdad, HWND hGenero) {}
void limpiarDatosEspecialidad(HWND hNum, HWND hName, HWND hApellidoP, HWND hApellidoM) {}

//-LIBERAR MEMORIAS -//

void liberarpunteros(){

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
void centrarVentana(HWND hwnd) {
	RECT rectVentana, rectPantalla;
	// Obtener el tamaño de la ventana
	GetWindowRect(hwnd, &rectVentana);
	// Obtener el tamaño de la pantalla
	GetWindowRect(GetDesktopWindow(), &rectPantalla);
	// Calcular la posición centrada
	int anchoVentana = rectVentana.right - rectVentana.left;
	int altoVentana = rectVentana.bottom - rectVentana.top;
	int posX = (rectPantalla.right - anchoVentana) / 2;
	int posY = (rectPantalla.bottom - altoVentana) / 2;
	// Establecer la nueva posición de la ventana
	SetWindowPos(hwnd, nullptr, posX, posY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

//LOGICA DIAGNOSTICO
/*
*
int len = GetWindowTextLength(hDiagnostico) + 1;  // +1 para el '\0'
std::vector<char> buffer(len);  // Usamos vector en vez de arreglo estático
GetWindowText(hDiagnostico, buffer.data(), len);  // buffer.data() obtiene el puntero a los datos internos
// esto usando vectory faltaria ver como convertir a string para la estructura o directamente en la estructura usarlo como
//vector <char> diagnositco
// aunque lo mejor sra usar char
*
*
*
*
TIENE MEJOR ADAPTACION STRING CON WN API GRTACIAS AL CHAR*  es probable que de error con textos muy largos,
pero por el momento parece que sera un texto razonable
// parece que 1024 puede ser un buen diagnostico, pero mejor dejar dinamico
	int le = GetWindowTextLength(hName)+1;
	char* pbuffer= new char[le];
	GetWindowText(hName, pbuffer, le);
	pacienteActual->nombre = string(pbuffer);


----------------------
codigo
-*------------
	delete[] pbuffer;


	///////////////////////////////////////////////

	//Sin embargo, si el texto es muy largo (varios megabytes o más),
es posible que debas considerar estrategias de manejo de memoria más robustas
(como cargar el texto por partes o usar otro tipo de contenedores,
como std::vector<char> o std::string, que gestionan la memoria de manera más eficiente).

	Por ejemplo, en lugar de:
	char* buffer = new char[len];
	Puedes usar:
	td::vector<char> buffer(len);
	*/

#pragma endregion
