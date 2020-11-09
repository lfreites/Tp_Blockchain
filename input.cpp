#include "input.h"
#include <string>

Input::Input(hash_t id, int index, hash_t adress){
	outpoint.tx_id = id;
	outpoint.idx = index;
	addr = adress;
}

Input::~Input(){
}


Input *obtenerInput(std::string data){
	int i = 0;	

	hash_t id = data.substr(0, 64);			//guardo el hash de la tnx de la que el input toma fondos
	if (id.lenght() < 64) return NULL;

	while (data[i] != " ")					//incremento i hasta el próximo espacio
		i++;
	int index = stoi(data.substr(65, i));	//guardo el indice 
	
	hash_t address = data.substr(65 + i);	//guardo el hash de la addr del output que referencia este input
	if (adress.lenght() < 64) return NULL;
	
	Input *input = new Input(id, index, address);
	return input;
}

