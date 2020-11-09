#ifndef OUTPUT_H
#define OUTPUT_H 

#include "utils.h"


class Output{	
private:
	double value; //Como el outpoint es algo propio del input, no abstraigo sus campos de la interfaz del input
	hash_t addr;

public:
	Output();
	Output(double val, hash_t address);
	~Output();

	//getters
	double getValue();
	hash_t getAddress();
};


Output *obtenerOutput(std::string data);
//devuelve un puntero a output a partir del parseo de una cadena de texto (data) con los parámetros del output.
//En caso de la cadena ser errónea devuelve puntero a NULL.
//

#endif	//OUTPUT_H