#include "output.h"
#include <string>
#include <iostream>

Output::Output(){
	value = 0;
	addr = "0";
}

Output::Output(double val, hash_t address){
	value = val;
	addr = address;
}

Output::~Output(){
}

double Output::getValue(){
	return value;
}

hash_t Output::getAddress(){
	return addr;
}

Output *obtenerOutput(std::string data){
	int i = 0;
	while (data[i] != ' ')					//incremento i hasta el próximo espacio
		i++;
	double value = stod(data.substr(0, i));

	hash_t address = data.substr(i + 1);
	if(address.length() != 64) return NULL;
	
	Output *output = new Output(value, address);

//	cout << '\n' << output << endl;
//	cout << output->getValue() << endl << output->getAddress() << endl;
	return output;
}
