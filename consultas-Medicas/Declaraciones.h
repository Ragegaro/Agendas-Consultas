#pragma once
#include <string>
#include <fstream>
//

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

struct medicos {
	int numCedula;
	char nombre[50];
	char apellidoPaterno[50];
	char apellidoMaterno[50];
	char email[50];
	int telefono;
	char especialidad[50];
	medicos* ant;
	medicos *sig;
	
	//creo que se podria hacer con algun entero
	// y buscar en el archivo segun ese entero o con lista ligada
};

struct paciente {
	int numPaciente;
	string nombrePaciente;
	string apellidoPaterno;
	string apellidoMmaterno;
	string correo;
	int telefono;
	bool genero;
	short edad;
	paciente *ant;
	paciente *sig;
};

struct consultas {
	int folioCita;
	//fecha ///char fecha[11]; // formmato: yyyy-mm-dd
	//hora  ///char hora[6];   // formato : HH:MM
	enum status {completada, confirmada, cancelada, noLlego};
	int numDeConusultorio;
	int cedula;
	string nombreMedico;
	// string apellidoPaternoMedico;
	string especialidad;


	int numPaciente;
	string nombrePaciente;
	// string apellidoPaternoPaciente;

	string resultado;
	string diagnostico;

	consultas *ant;
	consultas *sig;
};

///--- Lista extra ---///
struct especialidad {
	//int idEspecialidad;
	char clave[3];
	string defEspecialidad;
	especialidad *sig;
	especialidad* ant;
};
//////////////////////

/*
void insertarMedico(){}
void modificarMedico() {}
void eliminarMedico() {}


void insertarMedico() {}
void insertarMedico() {}

///
//void mostrarLista(){}
///
*/
/*-----WINAPI------*/
//menu  (solo aparece en pantalla principal)
HMENU hMenuCitas;
///  ventanas
//HWND hVentanaLogIn;
HWND hVentanaPrincipal;
HWND hVentanaPacientes;
HWND hVentanaMedicos;
HWND hVentanaConsultas;
HWND hVentanaEspecialidad;
HWND hVentanaReporte;
//HWND hAlgoMas;

//declaracion de las ventana
//LRESULT CALLBACK cVentanaLogIn(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaPrincipal(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaPaciente(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaMedicos(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaConsultas(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaEspecialidades(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK cVentanaReporte(HWND, UINT, WPARAM, LPARAM);
//Ventana de algo más?
// LRESULT CALLBACK cVentanaEasterEGG(HWND, UINT, WPARAM, LPARAM);

