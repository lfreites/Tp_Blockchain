#include <iostream>
#include <fstream>
#include <string>
#include "tnx.h"
#include "input.h"
#include "output.h"




int main(int argc, char const *argv[]){
	

	ifstream aux;
	aux.open("tnx.txt");

	transaccion_t *transaccion = NULL;

	if (!transaccion_leer(transaccion, aux)){
		aux.close();
		cerr << "error al leer" << endl;
		return -1;
	}

	ofstream salida;
	salida.open("salida.txt");
	transaccion_escribir(transaccion, salida);

	salida.close();
	aux.close();

	return 0;
}