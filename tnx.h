
#ifndef TRANSACCION_H
#define TRANSACCION_H
#include <fstream>
#include "input.h"
#include "output.h"
#include "utils.h"
#include <string>
#include <vector>


using namespace std;

struct transaccion{
	size_t n_tx_in; // Cantidad de inputs
	Input **inputs;
	size_t n_tx_out;
	Output **outputs;
};

typedef struct transaccion transaccion_t;

transaccion_t *transaccion_crear();

hash_t transaccion_hash(transaccion_t * tn);

transaccion_t * transaccion_genesis_crear(double value, hash_t user, hash_t genesis);

bool transaccion_leer(transaccion_t * tnx, istream * tnx_in);
//Recibe un puntero a una transacción y un puntero a un fichero de entrada con la informacion de la transacción
//y guarda toda su data en la transaccion. En caso de que no esté bien definido el archivo devuelve false,
//si todo sale ok (los inputs, outputs y las cantidades de ambos son correctos) devuelve true

void transaccion_escribir(transaccion_t *tnx, ostream * tnx_out);
//Vuelca en un archivo de salida apuntado por tnx_out los datos correspondientes a la transacción apuntada
//por tnx en el formato correspondiente

void transaccion_mostrar(transaccion_t *tnx);


void transaccion_destruir(transaccion_t *tnx);


#endif	//TRANSACCION_H