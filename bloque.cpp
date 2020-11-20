#include "bloque.h"


Bloque::Bloque(){

}

Bloque::Bloque(hash_t prev, hash_t ts_hash, uint d, uint n, size_t ts_count, vector <transaccion_t *> * ts) {
	prev_block = prev;
	txns_hash = ts_hash;
	bits = d;
	nonce = n;
	txn_count = ts_count;
	tnes = ts;

}

Bloque::~Bloque(){

}

void Bloque::bloque_escribir(ostream * os, void (*pf) (transaccion_t * tnx, ostream * os)){

	size_t i;

	*os << prev_block << '\n' << txns_hash << '\n' << bits << '\n' << nonce << '\n' << txn_count << '\n';
	for(i = 0; i < txn_count; i++){

		(*pf)((*tnes)[i], os);
	}
}



//getters
hash_t Bloque::getPrevHash(){
	return prev_block;
}

hash_t Bloque::getTxnsHash(){
	return txns_hash;
}

uint Bloque::getBits(){
	return bits;
}

uint Bloque::getNonce(){
	return nonce;
}

size_t Bloque::getCantidadTxns(){
	return txn_count;
}

//setters

void Bloque::setNonce(uint & n){

	nonce = n;
}

void Bloque::txnsAppend(transaccion_t *tnx){
	//Para que sea eficiente habría que implementar el campo transacciones como una lista enlazada
	//si no cada vez que queramos agregar una nueva transacción vamos a tener que crear un vector nuevo, 
	//copiar todas las transacciones del que ya existe en el nuevo, borrar el viejo y finalmente agregar tnx.
}