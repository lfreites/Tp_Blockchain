
#ifndef OUTPUT_H
#define OUTPUT_H 


class Output{	
private:
	double value; //Como el outpoint es algo propio del input, no abstraigo sus campos de la interfaz del input
	hash_t addr;

public:
	Output(double val, hash_t adress);
	~Output();
	Output *obtenerOutput(std::string data)
	//devuelve un puntero a output a partir de de una cadena de texto (data) con los parámetros del output.
	//En caso de la cadena ser errónea devuelve puntero a NULL.
	//

	/*
	getters
	*/

};

#endif	//OUTPUT_H