#pragma once
#include <string>
#include <fstream>
#include<iostream>

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
} *pacienteIni, * pacienteFin, * pacienteActual;

enum status { completada, confirmada, cancelada, noLlego };
struct consultas {
	int id;
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

///--- Lista extra de las sugeridas para el manejo de especialidades ---///
struct especialidad {
	
	char clave[3];
	string defEspecialidad;
	especialidad *sig;
	especialidad* ant;
} *espeIni, *espeFin, *espeActual;
#pragma endregion

enum tipoBusqueda {bPaciente, bMedico,bConsulta,bEspecialidad};
 
template <typename LL>
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
agregarNodo(medicoIni, medicoFinal, MedicoActual);
agregarNodo(pacienteIni, pacienteFin, pacienteActual);
agregarNodo(consultasIni, consultasFin, consulActual);
agregarNodo(espeIni, espeFin, espeActual);

*/
/*
template<typename LL>
LL buscarID( LL*& inicio, int id){
	if (inicio == 0) {
		while (inicio != nullptr) {


		}

		return LL // mesasgge box ( no hayt donde buscar)
	}

	return LL;
}


template<typename LL>
void leerArchivos(const string  nombreArchivo) {
	ifstream archivo("prueba de lsita ligada.txt");
	if (!archivo.is_open()) {
		cout << " archivo no se pudo abrir \n"; return;
	}
	string linea;
	while (archivo != NULL) {
		getline(archivo, linea);
		agregarNodo(LL,LL,LL);


	}


}


void leerArchivos() {

	ifstream archivo("prueba de lsita ligada.txt");
	if (!archivo.is_open()) {
		cout << " archivo no se pudo abrir \n"; return;
	}

	string linea;
	while (getline(archivo, linea)) {
		cout << linea << endl;
	}
	archivo.close();
}

*/
void guardarEnArchivos(paciente* Ini) {
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

void guardarEnArchivosMedicos(medicos* Ini) {
	ofstream archivo("prueba de lsita ligada.txt", ios::app);
	if (!archivo.is_open()) {
		cout << " archivo no se pudo abrir \n"; return;
	}
	if (Ini == nullptr) {
		archivo << "No hay pacientes registrados." << endl;
		archivo.close();
		return;
	}
	while (Ini != nullptr) {
		archivo << "ID: " << Ini->id << endl;
		archivo << "Nombre: " << Ini->nombre << " " << Ini->apellidoPaterno << " " << Ini->apellidoMaterno << endl;
		archivo << "Correo: " << Ini->email << endl;
		archivo << "Teléfono: " << Ini->telefono << endl;
		archivo << "Especialidad: " << Ini->especialidad << endl;
		archivo << "----------------------------------------" << endl;
		Ini = Ini->sig;
	}
	archivo.close();
}






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
TIENE MEJOR ADAPTACION STRING CON WN API GRTACIAS AL CHAR*
// parece que 1024 puede ser un buen diagnostico, pero mejor dejar dinamico
	int le = GetWindowTextLength(hName)+1;
	char* pbuffer= new char[le];
	GetWindowText(hName, pbuffer, le);
	pacienteActual->nombre = string(pbuffer);


----------------------
codigo
-*------------
	delete[] pbuffer;
	*/

void modificarPaciente() {}

void eliminarPaciente() {}

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









//SUGRERENCIA LOCAAAAAAAAAA


/*
#include <iostream>
#include <string>
using namespace std;

// Estructura para médicos
struct medicos {
	int id;
	string nombre;
	string apellidoPaterno;
	string apellidoMaterno;
	string email;
	int telefono;
	string especialidad;  // Este campo es específico de los médicos
	medicos* ant;
	medicos* sig;
} *medicoIni = nullptr, *medicoFinal = nullptr, *MedicoActual = nullptr;

// Estructura para pacientes
struct paciente {
	int id;
	string nombre;
	string apellidoPaterno;
	string apellidoMaterno;
	string correo;
	int telefono;
	bool genero;  // Este campo es específico de los pacientes
	short edad;
	paciente* ant;
	paciente* sig;
} *pacienteIni = nullptr, *pacienteFin = nullptr, *pacienteActual = nullptr;

// Función para verificar campos nulos en médicos
void verificarMedicos() {
	MedicoActual = medicoIni;
	while (MedicoActual != nullptr) {
		cout << "ID: " << MedicoActual->id << endl;
		cout << "Nombre: " << MedicoActual->nombre << " " << MedicoActual->apellidoPaterno << " " << MedicoActual->apellidoMaterno << endl;
		cout << "Email: " << MedicoActual->email << endl;
		cout << "Telefono: " << MedicoActual->telefono << endl;

		// Verificar si especialidad es vacía (nulo)
		if (MedicoActual->especialidad.empty()) {
			cout << "Especialidad: No definida" << endl;
		} else {
			cout << "Especialidad: " << MedicoActual->especialidad << endl;
		}

		MedicoActual = MedicoActual->sig;
	}
}

// Función para verificar campos nulos en pacientes
void verificarPacientes() {
	pacienteActual = pacienteIni;
	while (pacienteActual != nullptr) {
		cout << "ID: " << pacienteActual->id << endl;
		cout << "Nombre: " << pacienteActual->nombre << " " << pacienteActual->apellidoPaterno << " " << pacienteActual->apellidoMaterno << endl;
		cout << "Correo: " << pacienteActual->correo << endl;
		cout << "Telefono: " << pacienteActual->telefono << endl;

		// Verificar si genero es falso (nulo)
		if (!pacienteActual->genero) {
			cout << "Genero: No definido" << endl;
		} else {
			cout << "Genero: " << (pacienteActual->genero ? "Masculino" : "Femenino") << endl;
		}

		pacienteActual = pacienteActual->sig;
	}
}

int main() {
	// Crear médicos
	medicos* medico1 = new medicos{1, "Juan", "Perez", "Gomez", "juan@example.com", 1234567890, "", nullptr, nullptr};
	medicos* medico2 = new medicos{2, "Maria", "Lopez", "Martinez", "maria@example.com", 9876543210, "Cardiologia", nullptr, nullptr};

	// Agregar médicos a la lista ligada
	medicoIni = medico1;
	medico1->sig = medico2;
	medico2->ant = medico1;

	// Crear pacientes
	paciente* paciente1 = new paciente{1, "Carlos", "Hernandez", "Diaz", "carlos@example.com", 1234567890, false, 30, nullptr, nullptr};
	paciente* paciente2 = new paciente{2, "Laura", "Gonzalez", "Perez", "laura@example.com", 9876543210, true, 25, nullptr, nullptr};

	// Agregar pacientes a la lista ligada
	pacienteIni = paciente1;
	paciente1->sig = paciente2;
	paciente2->ant = paciente1;

	// Verificar médicos
	cout << "Lista de Médicos:" << endl;
	verificarMedicos();

	cout << endl;

	// Verificar pacientes
	cout << "Lista de Pacientes:" << endl;
	verificarPacientes();

	return 0;
}

*/


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
