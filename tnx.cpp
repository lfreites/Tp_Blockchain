#include "tnx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "utils.h"


transaccion_t *transaccion_crear(){
	transaccion_t *nueva = new transaccion_t;

	nueva->n_tx_in = 0;
	nueva->n_tx_out = 0;

	return nueva;
}

transaccion_t * transaccion_genesis_crear(double value, hash_t user, hash_t genesis){

	transaccion_t *nueva = new transaccion_t;

	nueva->n_tx_in = 1;
	nueva->n_tx_out = 1;

	nueva -> inputs = new Input*[nueva->n_tx_in];
	nueva -> outputs = new Output*[nueva->n_tx_out];

	(nueva -> inputs)[0] = new Input(genesis, 0, genesis);
	(nueva -> outputs)[0] = new Output(value, user);

	return nueva;

}


bool transaccion_leer(transaccion_t * tnx, istream * tnx_in){
	//
	//
	//Lee primero la cantidad n_tx_in de inputs de la transacción y luego procesa y guarda los n_tx_in inputs
	//válidos en el vector inputs (en realidad los guarda como punteros a input)
	//terminados de procesar los n_tx_in inputs repite el proceso pero con los n_tx_out siguientes
	//
	//En caso de que algún input u output no esté descripto correctamente, devuelve false (por definición,
	//esto incluye el caso de que haya menos líneas de in/outputs que las indicadas por n_tx_xx ).
	//Que falle no implica que la transacción tnx que estamos seteando (ya que la recibimos creada por parámetro)
	//sea "borrada". En todo caso, que si se incluya o no en el bloque se decidirá dentro del aḿbito del flujo
	//desde donde la llamamos, (básicaente para eso devuelve un booleano).
	//
	std::string line;

	//inputs
	(*tnx_in) >> line;
	stringstream aux(line);
	aux >> tnx->n_tx_in;
	if(tnx->n_tx_in == 0)
		return false;
	Input **lista_i = new Input*[tnx->n_tx_in];
	tnx->inputs = lista_i;

	for (size_t i = 0; i < tnx->n_tx_in; i++){
		int index_data;
		std::string hash_data;
		std::string addr_data;

		(*tnx_in) >> hash_data;				//guardo la línea donde está parado tnx_in

		(*tnx_in) >> line;
		stringstream aux2(line);
		aux2 >> index_data;

		(*tnx_in) >> addr_data;	

		tnx->inputs[i] = new Input(hash_data, index_data, addr_data);
	
		}

	//outputs
	(*tnx_in) >> line;
	stringstream aux3(line);
	aux3 >> tnx->n_tx_out;

	if(tnx->n_tx_out == 0)
		return false;

	Output **lista_o = new Output*[tnx->n_tx_out];
	tnx->outputs = lista_o;

	for (size_t i = 0; i < tnx->n_tx_out; i++){
		double value_data;
		std::string addr_data;

		(*tnx_in) >> line;
		stringstream aux4(line);
		aux4 >> value_data;

		(*tnx_in) >> addr_data;			

		tnx->outputs[i] = new Output(value_data, addr_data);
		
	}
	return true;
}



void transaccion_escribir(transaccion_t *tnx, ostream * tnx_out){
	*tnx_out << tnx->n_tx_in << endl;
	for (size_t i = 0; i < tnx->n_tx_in; i++){
		*tnx_out << tnx->inputs[i]->getTnxId() << " " \
				<< tnx->inputs[i]->getIndex() << " " \
				<< tnx->inputs[i]->getAddress() << endl;			
	}

	*tnx_out << tnx->n_tx_out << endl;
	for (size_t i = 0; i < tnx->n_tx_out; i++)
		*tnx_out << tnx->outputs[i]->getValue() << " " << tnx->outputs[i]->getAddress() << endl;
}

void transaccion_mostrar(transaccion_t *tnx){
	cout << "transacción guardada: " << endl;
	cout << tnx->n_tx_in << endl;
	for (size_t i = 0; i < tnx->n_tx_in; i++)
		cout << tnx->inputs[i]->getTnxId() << ' ' << tnx->inputs[i]->getIndex() << ' ' << tnx->inputs[i]->getAddress() << endl;
	cout << tnx->n_tx_out << endl;
	for(size_t i = 0; i < tnx->n_tx_out; i++)
		cout << tnx->outputs[i]->getValue() << ' ' << tnx->outputs[i]->getAddress() << endl; 
	cout << endl;
}

hash_t transaccion_hash(transaccion_t * tn){

	size_t i;
	hash_t ts;

	ts = to_string(tn->n_tx_in) + '\n';
		for(i = 0; i < tn->n_tx_in; i++){
			ts = ts + tn->inputs[i]->getTnxId() + " " + to_string(tn->inputs[i]->getIndex()) + " " + tn->inputs[i]->getAddress() + '\n';	
		}

		ts = ts + to_string(tn->n_tx_out) + '\n';
		for(i = 0; i < tn->n_tx_out; i++){
			ts = ts + to_string(tn->outputs[i]->getValue()) + " " + tn->outputs[i]->getAddress() + '\n';
		}

	return ts;	
}



void transaccion_destruir(transaccion_t *tnx){

	if(tnx->n_tx_in == 0){
		delete tnx;
		return;
	}
	for (size_t i = 0; i < tnx->n_tx_in; i++)
		delete tnx->inputs[i];
	delete[] tnx->inputs;

	for (size_t i = 0; i < tnx->n_tx_out; i++)
		delete tnx->outputs[i];
	delete[] tnx->outputs;

	delete tnx;
}