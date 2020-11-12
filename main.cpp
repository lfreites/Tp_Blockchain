#include <iostream>
#include <fstream>
#include <string>
#include "tnx.h"
#include "input.h"
#include "output.h"
#include "cmdline.h"

#define MSG_ERR_OPEN_FILE "Error al abrir el archivo "
#define DEFAULT_DIFICULTY 2

using namespace std;

static void opt_input(string const &arg);
static void opt_input_d(string const &arg);
 
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "d", "dificulty", "-", opt_input_d, OPT_DEFAULT},
	{0, }
};

static string input;
//static ifstream input;

static int dificulty;

static void opt_input(string const &arg)
{
	if(arg == "-") {
		cin >> input;
	}
	else{
		std::stringstream in(arg);
	    if(!in.good()){
		    cerr << MSG_ERR_OPEN_FILE << arg << endl;
		    exit(1);
	    }
		//std::cout << "el sstringstream in es bueno..... hace in >> input...    arg es: " << arg << std::endl;
		in >> input;
	}
}

static void opt_input_d(string const &arg)
{
	if(arg == "-") {
		dificulty = DEFAULT_DIFICULTY;
	}
	else{

		dificulty = atoi(arg.c_str());
		
		if(dificulty <= 0)
		{
			cout << "Dificulty must be positive!!" << arg << endl;
		}
	}

	cout << "Dificulty set to : " << dificulty << endl;
}



//
//Prueba de funcionamiento de lectura de archivo con transacciones, almacenamiento de la información de dichas
//transacciones y posterior escritura de esa información.
//
//En principio sólo aplica a un archivo con una única transacción, habría que modificarlo (algo tipo while (!EOF))
//para que opere a lo largo de todo el archivo y guarde cuantas transacciones haya en él.
//
int main(int argc, char *argv[]){
	
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	//ifstream entrada(input);
	ifstream entrada;
	entrada.open(input);

	transaccion_t *transaccion = transaccion_crear();

	if (!transaccion_leer(transaccion, entrada)){
		entrada.close();
		cerr << "error al leer" << endl;
		transaccion_destruir(transaccion);
		return -1;
	}
	transaccion_mostrar(transaccion);

	ofstream salida;
	salida.open("salida.txt", ios::app);
	if(salida.fail()){
		entrada.close();
		cerr << "no se pudo abrir el archivo de salida" << endl;
		transaccion_destruir(transaccion);
		return -1;
	}
	transaccion_escribir(transaccion, salida);

	salida.close();
	entrada.close();

	transaccion_destruir(transaccion);

	return 0;
}