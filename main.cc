#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "tnx.h"
#include "cmdline.h"
#include "input.h"
#include "output.h"
#include "bloque.h"
#include "sha256.h"
#include "proof_of_work.h"
#include "utils.h"


using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_difficulty(string const &);
static void opt_help(string const &);

// Tabla de opciones de l�nea de comando. El formato de la tabla
// consta de un elemento por cada opci�n a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opci�n lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opci�n.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opci�n en caso que no est� expl�citamente presente
//   en la l�nea de comandos del programa. Si la opci�n no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al m�todo de parseo de la opci�n,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La �ltima columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opci�n: cuando la
//   opci�n es obligatoria, deber� activarse OPT_MANDATORY.
//
// Adem�s, la �ltima entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "d", "difficulty", NULL, opt_difficulty, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static int difficulty;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)



/*****************************************************/

static void opt_input(string const &arg) {
	// Si el nombre del archivos es "-", usaremos la entrada
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_output(string const &arg){
	// Si el nombre del archivos es "-", usaremos la salida
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminaci�n del programa en su totalidad
	}
}

static void opt_difficulty(string const &arg){
	istringstream iss(arg);

	// Intentamos extraer el factor de la l�nea de comandos.
	// Para detectar argumentos que �nicamente consistan de
	// n�meros enteros, vamos a verificar que EOF llegue justo
	// despu�s de la lectura exitosa del escalar.
	//
	if (!(iss >> difficulty)
	    || !iss.eof()) {
		cerr << "non-integer factor: "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}

	if (iss.bad()) {
		cerr << "cannot read integer factor."
		     << endl;
		exit(1);
	}
}

static void opt_help(string const &arg) {
	cout << "cmdline -d difficulty [-i file] [-o file]"
	     << endl;
	exit(0);
}


int main(int argc, char * const argv[]){

	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver l�nea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

	size_t i, j;
	size_t capacidad = INIT_SIZE;
	hash_t prev = DEFAULT_PREV;
	hash_t ts;

	vector <transaccion_t *> tnes(capacidad);

	for(i = 0; !iss -> eof() ; i++) {
		if(i == capacidad){
			tnes.resize(capacidad + CHOP_SIZE);
			capacidad += CHOP_SIZE;
		}

		tnes[i] = transaccion_crear();

		if(!transaccion_leer(tnes[i], iss)){
			cerr << "error al leer" << endl;
			for(j= 0; j < i; j++)
				transaccion_destruir(tnes[i]);
			vector <transaccion_t *>().swap(tnes);
			exit(1);
		}
	}


	for(j = 0; j < i; j++)
		ts += transaccion_hash(tnes[j]);
	
	ts = sha256(sha256(ts));	

	Bloque * bloque = new Bloque(prev, ts, difficulty, difficulty, i, &tnes);

	if(proof_of_work(*bloque) != true) {
		for(j= 0; j < i; j++)
			transaccion_destruir(tnes[i]);
		vector <transaccion_t *>().swap(tnes);
		delete(bloque);
		exit(1);
	}

	bloque->bloque_escribir(oss, transaccion_escribir);


	if (oss->bad()) {
		cerr << "cannot write to output stream."
		     << endl;
		exit(1);
	}
	if (iss->bad()) {
		cerr << "cannot read from input stream."
		     << endl;
		exit(1);
	}
	if (!iss->eof()) {
		cerr << "cannot find EOF on input stream."
		     << endl;
		exit(1);
	}

	for(j= 0; j < i; j++)
		transaccion_destruir(tnes[j]);
	vector <transaccion_t *>().swap(tnes);

	delete(bloque);

	return 0;
}
