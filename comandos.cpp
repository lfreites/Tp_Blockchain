#include <iostream>
#include <string>
#include "utils.h"
#include "input.h"

using namespace std;

template <typename T>;

typedef T (*function_t) (/*parámetros*/);


typedef struct {
	string user_name;
	Bloque *block;
}userblock_t;


typedef struct commands{
	string name;
	function_t function;
}commands_t;

const commands_t commands[] = {
	{"init",	init},
	{"transfer",transfer},
	{"mine",	mine},
	{"balance", balance},
	{"block",	block},
	{"txn",		txn},
	{"load",	load},
	{"save",	save}
};




hash_t init(List<Bloque> *blockchain, string user, int value, uint bits){

	while (!blockchain->empty()){
		//limpia la lista en caso de no estar vacía
		//
		blockchain->pop();
	}

	transaccion_t *init_txn = transaccion_genesis_crear(value);
	vector<transaccion_t*> *vec_init = &init_txn;

	Bloque genesis = new Bloque(DEFAULT_PREV, 0, bits, /*nonce*/, 1, vec_init);
	blockchain->append(genesis);

	return genesis->getTxnsHash();
}


hash_t transfer(string src, string dest[], int values[], size_t dest_n, size_t values_n){

}


hash_t mine(List<Bloque> *blockchain, mempool_t &mempool, uint bits){
	//
	//Tiene que ir sacando las transacciones de la mempool (es una cola), agregarlas a un nuevo bloque
	//y calcular el hash a partir de todas ellas con la dificultad dada por bits.
	//Luego, el nuevo bloque debe ser agregado a la blockchain
	//
	vector<transaccion_t> utxos = new vector<transaccion_t>[mempool.length()]; 
	size_t i = 0;
	while (!mempool.empty()){
		utxos[i] = mempool.dequeue();
	}
	/*
	Hashing, ensamblado y return si todo ok
	*/
	return "FAIL";
}

uint balance(stirng user){
	return ;
}