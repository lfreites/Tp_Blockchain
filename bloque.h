#ifndef BLOQUE_H
#define BLOQUE_H
#include "utils.h"
#include "tnx.h"
#include <vector>

class Bloque{

private:
	hash_t prev_block;
	hash_t txns_hash;
	uint bits;
	uint nonce;
	size_t txn_count;
	vector <transaccion_t *> * tnes;
public:
	Bloque();
	Bloque(hash_t prev, hash_t ts_hash, uint d, uint n, size_t ts_count, vector <transaccion_t *> * ts);
	~Bloque();
	void bloque_escribir(ostream * os, void (*pf) (transaccion_t * tnx, ostream * os));
	hash_t bloque_hash(hash_t (*pf) (transaccion_t * tnx));
	void bloque_destruir(void (*pf) (transaccion_t * tnx));

	//getters
	hash_t getPrevHash();
	hash_t getTxnsHash();
	uint getBits();
	uint getNonce();
	size_t getCantidadTxns();
	vector <transaccion_t *> * getTnes();

	//setters
	void setNonce(uint & nonce);

	void txnsAppend(transaccion_t *tnx);
};

#endif //BLOQUE_H