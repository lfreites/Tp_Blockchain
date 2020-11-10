#include "bloque.h"


Bloque::Bloque(){

}

Bloque::~Bloque(){

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
	return txns_count
}

void Bloque::txnsAppend(transaccion_t *tnx){
	//Para que sea eficiente habría que implementar el campo transacciones como una lista enlazada
	//si no cada vez que queramos agregar una nueva transacción vamos a tener que crear un vector nuevo, 
	//copiar todas las transacciones del que ya existe en el nuevo, borrar el viejo y finalmente agregar tnx.
}