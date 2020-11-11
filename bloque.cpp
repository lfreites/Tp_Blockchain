#include "bloque.h"
#include "utils.h"

Bloque::Bloque(uint d){
	prev_block = DEFAULT_PREV;
	txns_hash = /*Completar con el doble sha256(...*/;
	bits = d;
	nonce = ;
	txns_count = 0;
	transacciones = new List<transaccion_t>;
}

Bloque::~Bloque(){
	delete transacciones
}



//getters
hash_t Bloque::prevHash(){
	return prev_block;
}

hash_t Bloque::txnsHash(){
	return txns_hash;
}

uint Bloque::bits(){
	return bits;
}

uint Bloque::nonce(){
	return nonce;
}

size_t Bloque::cantidadTxns(){
	return txns_count;
}

void Bloque::txnsAppend(transaccion_t &tnx){
	transacciones->append(txn);
	txns_count++;
}