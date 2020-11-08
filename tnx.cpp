#include "tnx.h"
#include <ifstream>

struct transaccion{
	size_t n_tx_in;
	input_t **inputs;
	size_t n_tx_out;
	output_t **outputs;
};


bool transaccion_leer(transaccion_t * tnx, ifstream *tnx_in){
	//
	//
	//Lee primero la cantidad n_tx_in de inpunts de la transacción y luego procesa y guarda los n_tx_in inputs
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
	int inputs_n, outputs_n;

	//inputs
	getline(tnx_in, aux);
	inputs_n = stoi(aux);
	for (int i = 0; i < inputs_n; i++){
		std::string input_data;
		getline(tnx_in, input_data);				//guardo la línea donde está parado tnx_in
		tnx->inputs[i] = obtenerInput(input_data);	//parseo la cadena y creo un puntero a input y lo meto en la lista
		if (tnx->inputs[i] == NULL)
			return false;
	}

	//outputs
	aux = "0";
	getline(tnx_in, aux);
	outputs_n = stoi(aux);
	for (int i = 0; i < outputs_n; i++){
		std::string output_data;
		getline(tnx_in, output_data);				//guardo la línea donde está parado tnx_in
		tnx->inputs[i] = obtenerOutput(output_data);//parseo la cadena y creo un puntero a input y lo meto en la lista
		if (tnx->inputs[i] == NULL)
			return false;
	}

	return true;
}



FILE * transaccion_escribir(transaccion_t *tnx){

}