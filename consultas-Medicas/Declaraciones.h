#pragma once
#include <string>
#include <fstream>

struct medicos {
	int numCedula;
	string nombre;
	string apellidoPaterno;
	string apellidoMaterno;
	string email;
	int telefono;
	string especialidad;//creo que se podria hacer con algun entero y buscar en el archivo segun ese entero o con lista ligada
	medicos* ant;
	medicos* sig;
} *medicoIni, *medicoFinal, *MedicoActual;

struct paciente {
	int numPaciente;
	string nombrePaciente;
	string apellidoPaterno;
	string apellidoMaterno;
	string correo;
	int telefono;
	bool genero;
	short edad;
	paciente *ant;
	paciente *sig;
} *pacienteIni,*pacienteFin, *pacienteActual;

enum status { completada, confirmada, cancelada, noLlego };
struct consultas {
	int folioCita;
	//fecha ///char fecha[11]; // formmato: yyyy-mm-dd
	//hora  ///char hora[6];   // formato : HH:MM
	
	int numDeConusultorio;
	int cedula;
	string nombreMedico;
	// string apellidoPaternoMedico;
	string especialidad;
	status statusCita;

	int numPaciente;
	string nombrePaciente;
	// string apellidoPaternoPaciente;
	status coso;
	string resultado;
	string diagnostico;

	consultas *ant;
	consultas *sig;
} *consultasIni, *consultasFin, *consulActual;
///--- Lista extra ---///
struct especialidad {
	//int idEspecialidad;
	char clave[3];
	string defEspecialidad;
	especialidad *sig;
	especialidad* ant;
} *espeIni, *espeFin, *espeActual;
enum statusCita{};

enum tipoBusqueda {bPaciente, bMedico,bConsulta,bEspecialidad};
 
template <typename LL>
void agregarNodo(LL*& inicio, LL*& fin, LL* aux) {
	if (inicio == nullptr) inicio = fin = aux;
	else {
		fin->sig = aux;
		aux->ant = fin;
		fin = aux;
	}
}
/* AGREGA AL FINAL DE LA LISTA------------FORMA DE USAR LA FUNCION AGREGAR NODO
agregarNodo(medicoIni, medicoFinal, MedicoActual);
agregarNodo(pacienteIni, pacienteFin, pacienteActual);
agregarNodo(consultasIni, consultasFin, consulActual);
agregarNodo(espeIni, espeFin, espeActual);

*/
/*
template <typename LL>
void modificarNodo(LL*& inicio, LL*& fin, LL* aux) {}

template<typename LL>
void eliminarNodo() {}

template <typename LL>
void mostrarNodo(LL*& inicio, LL*& fin, LL* aux) {}
*/
#pragma region BusquedaLoca
/*
enum TipoBusqueda { CEDULA, PACIENTE, FOLIO };

template <typename T>
T* buscarNodo(T* inicio, int clave, TipoBusqueda tipo) {
	T* aux = inicio;
	while (aux != nullptr) {
		switch (tipo) {
		case CEDULA:
			if (aux->numCedula == clave) return aux;
			break;
		case PACIENTE:
			if (aux->numPaciente == clave) return aux;
			break;
		case FOLIO:
			if (aux->folioCita == clave) return aux;
			break;
		}
		aux = aux->sig;
	}
	return nullptr;
}
*/
#pragma endregion

void obtenerDatosPaciente(HWND hNum, HWND hName, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEdad, HWND hGenero, paciente* pacienteActual) {
	char buffer[256] = { 0 }; // Variable local para evitar problemas de memoria

	GetWindowText(hNum, buffer, sizeof(buffer));
	pacienteActual->numPaciente = atoi(buffer);
	GetWindowText(hName, buffer, sizeof(buffer));
	pacienteActual->nombrePaciente = buffer;
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
void limpiarDatosPaciente(HWND hNum, HWND hName, HWND hApellidoP, HWND hApellidoM, HWND hEmail, HWND hTelefono, HWND hEdad, HWND hGenero) {
	SetWindowText(hNum,"");
	SetWindowText(hName, "");
	SetWindowText(hApellidoP, "");
	SetWindowText(hApellidoM, "");
	SetWindowText(hEmail, "");
	SetWindowText(hTelefono, "");
	SetWindowText(hEdad, "");
	SendMessage(hGenero, CB_SETCURSEL, -1, 0);
}

/*void guardarArchivo() {
	tipoBusqueda busqueda;
	switch (busqueda) {
		case bPaciente:{
			break;
		}
		case bMedico: {
			break;
		}
		case bConsulta: {
			break;
		}
		case bEspecialidad: {
			break;
		}
	}
}*/
//prueba 
template <typename LL>
 LL buscar() {};
 // fin de prueba, no se termino 
///



/*-----WINAPI------*/

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





#pragma region intentoTemplate
/*
template <typename  LL>
struct miembroLista {
	LL tipoLista;
	miembroLista<LL>* sig;
	miembroLista<LL>* ant;
	miembroLista(const LL& valor) : tipoLista(valor), sig(nullptr), ant(nullptr) {}
};  // la estructura anterior es como hacer una estructura (medico,paciente,etc) anidada en miembro list

struct coso {

	int x;
} *vamos;

template <typename LL>
class listaLigadaDoble{
	miembroLista<LL>* cabeza;
	miembroLista<LL>* cola;
public:
	listaLigadaDoble() : cabeza(nullptr), cola(nullptr) {}


	void insertar(const LL& valor) {
		miembroLista<LL>* nuevo = new miembroLista<LL>(valor);
		if (!cabeza) {
			cabeza = cola = nuevo;
		}
		else {
			cola->sig = nuevo;
			nuevo->ant = cola;
			cola = nuevo;
		}
	}

	void mostrar() {
		miembroLista<LL>* actual = cabeza;
		while (actual) {
			cout << actual->dato << " ";
			actual = actual->sig;
		}
		cout << endl;
	}




	// Guardar lista en archivo binario
	void guardarEnArchivo(const string& nombreArchivo) {
		ofstream archivo(nombreArchivo, ios::binary);
		if (!archivo) {
			cerr << "Error al abrir el archivo para escritura: " << nombreArchivo << endl;
			return;
		}

		Nodo<LL>* actual = cabeza;
		while (actual) {
			archivo.write(reinterpret_cast<char*>(&actual->dato), sizeof(T));
			actual = actual->sig;
		}
		archivo.close();
		cout << "Datos guardados en " << nombreArchivo << endl;
	}

	// Cargar lista desde archivo binario
	void cargarDesdeArchivo(const string& nombreArchivo) {
		ifstream archivo(nombreArchivo, ios::binary);
		if (!archivo) {
			cerr << "Error al abrir el archivo para lectura: " << nombreArchivo << endl;
			return;
		}

		T valor;
		while (archivo.read(reinterpret_cast<char*>(&valor), sizeof(T))) {
			insertar(valor);
		}
		archivo.close();
		cout << "Datos cargados desde " << nombreArchivo << endl;
	}

	~listaLigadaDoble() {
		miembroLista<LL>* actual = cabeza;
		while (actual) {
			miembroLista<LL>* temp = actual;
			actual = actual->sig;
			delete temp;
		}
	}
};*/
#pragma endregion
