#include "input.h"
#include <string>
#include <iostream>

Input::Input(){
	outpoint.tx_id = "0";
	outpoint.idx = 0;
	addr = "0";
}

Input::Input(hash_t id, int index, hash_t adress){
	outpoint.tx_id = id;
	outpoint.idx = index;
	addr = adress;
}

Input::~Input(){
}

outpoint_t *Input::getOutpoint(){
	outpoint_t *outpnt = new outpoint_t;
	outpnt->tx_id = this->outpoint.tx_id;
	outpnt->idx = this->outpoint.idx;

	return outpnt;
}

hash_t Input::getTnxId(){
	return outpoint.tx_id;
}

int Input::getIndex(){
	return outpoint.idx;
}

hash_t Input::getAddress(){
	return addr;
}


Input *obtenerInput(std::string data){
	int i = 0;	
	int c = 65;
	
	hash_t id = data.substr(0, 64);			//guardo el hash de la tnx de la que el input toma fondos
	if (id.length() < 64) return NULL;

	while (data[c] != ' '){					//incremento i hasta el próximo espacio
		i++;
		c++;
	}
	int index = stoi(data.substr(65, i));	//guardo el indice 
	
	hash_t address = data.substr(65 + i + 1);	//guardo el hash de la addr del output que referencia este input
	
	if (address.length() < 64) return NULL;
	Input *input = new Input(id, index, address);

	//
	//chequeo que se cree el puntero al objeto y a continuación que el objeto se haya instanciado correctamente
//	cout << '\n' << input << endl;
//	cout << input->getTnxId() << endl << input->getIndex() << endl << input->getAddress() << endl;

	return input;
}

