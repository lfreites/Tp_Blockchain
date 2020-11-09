#include "tnx.h"
#include <iostream>
#include <fstream>
#include <string>


transaccion_t *transaccion_crear(){
	transaccion_t *nueva = new transaccion_t;
	nueva->n_tx_in = 0;
	Input **lista_i = new Input*[10];
	nueva->inputs = lista_i;

	nueva->n_tx_out = 0;
	Output **lista_o = new Output*[10];
	nueva->outputs = lista_o;

	return nueva;
}

bool transaccion_leer(transaccion_t * tnx, ifstream &tnx_in){
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
	std::string aux;

	//inputs
	getline(tnx_in, aux);
	tnx->n_tx_in = stoi(aux);
	for (size_t i = 0; i < tnx->n_tx_in; i++){
		std::string input_data;
		getline(tnx_in, input_data);				//guardo la línea donde está parado tnx_in

		tnx->inputs[i] = obtenerInput(input_data);	//parseo la cadena y creo un puntero a input y lo meto en la lista
		if (tnx->inputs[i] == NULL){
			cout << "la direccion del input " << i << "me dio NULL" << endl;
			return false;
		}
	}

	//outputs
	aux = "0";
	getline(tnx_in, aux);
	tnx->n_tx_out = stoi(aux);
	for (size_t i = 0; i < tnx->n_tx_out; i++){
		std::string output_data;
		getline(tnx_in, output_data);				//guardo la línea donde está parado tnx_in

		tnx->outputs[i] = obtenerOutput(output_data);//parseo la cadena y creo un puntero a input y lo meto en la lista
		if (tnx->outputs[i] == NULL)
			return false;
	}

//	transaccion_mostrar(tnx);

	cout << "\n\n";
	return true;
}



void transaccion_escribir(transaccion_t *tnx, ofstream &tnx_out){
	tnx_out << tnx->n_tx_in << endl;
	for (size_t i = 0; i < tnx->n_tx_in; i++){
		tnx_out << tnx->inputs[i]->getTnxId() << " " \
				<< tnx->inputs[i]->getIndex() << " " \
				<< tnx->inputs[i]->getAddress() << endl;			
	}

	tnx_out << tnx->n_tx_out << endl;
	for (size_t i = 0; i < tnx->n_tx_out; i++)
		tnx_out << tnx->outputs[i]->getValue() << " " << tnx->outputs[i]->getAddress() << endl;
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

void transaccion_destruir(transaccion_t *tnx){
	for (size_t i = 0; i < tnx->n_tx_in; i++)
		delete tnx->inputs[i];
	delete[] tnx->inputs;

	for (size_t i = 0; i < tnx->n_tx_out; i++)
		delete tnx->outputs[i];
	delete[] tnx->outputs;

	delete tnx;
}