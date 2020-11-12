#ifndef BLOQUE_H
#define BLOQUE_H

#include "utils.h"

class Bloque{

private:
	hash_t prev_block;
	hash_t txns_hash;
	uint bits;
	uint nonce;
	size_t txn_count;
	List<transaccion_t> *transacciones;
public:
	Bloque();
	~Bloque();

	//getters
	hash_t prevHash();
	hash_t txnsHash();
	uint bits();
	uint nonce();
	size_t cantidadTxns();

	void txnsAppend(transaccion_t &tnx);
}

#endif //BLOQUE_H