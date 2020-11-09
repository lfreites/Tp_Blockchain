#include <iostream>
#include <fstream>
#include <string>
#include "tnx.h"
#include "input.h"
#include "output.h"



//
//Prueba de funcionamiento de lectura de archivo con transacciones, almacenamiento de la información de dichas
//transacciones y posterior escritura de esa información.
//
//En principio sólo aplica a un archivo con una única transacción, habría que modificarlo (algo tipo while (!EOF))
//para que opere a lo largo de todo el archivo y guarde cuantas transacciones haya en él.
//
int main(int argc, char const *argv[]){
	

	ifstream entrada;
	entrada.open("tnx.txt");

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