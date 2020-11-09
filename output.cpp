#include "output.h"
#include <string>

Input::Output(int val, hash_t adress){
	value = val;
	addr = adress;
}

Input::~Output(){
}

double Output::getValue(){
	return value;
}

hash_t Output::getAdress(){
	return addr;
}

Output *obtenerOutput(std::string data){
	int i = 0;
	while (data[i] != " ")					//incremento i hasta el próximo espacio
		i++;
	double value = stod(data.substr(0, i));
	
	hash_t address = data.substr(i + 1);
	if(adress.lenght() != 64) return NULL;

	Output *output = new Input(value, address);
	return output;
}
