#include "bloque.h"
#include "utils.h"
#include "sha256.h"
#include "proof_of_work.h"

map<char,uint> hexa = { {'0', 4},
						{'1', 3},
						{'2', 2}, 
						{'3', 2}, 
						{'4', 1}, 
						{'5', 1}, 
						{'6', 1}, 
						{'7', 1}, 
						{'8', 0},
						{'9', 0}, 
						{'a', 0}, 
						{'b', 0}, 
						{'c', 0}, 
						{'d', 0}, 
						{'e', 0}, 
						{'f', 0} };


bool proof_of_work(Bloque &bloque){

	uint i, nonce;
	hash_t hash;
	uint bits_nulos_hash = 0;
	nonce = bloque.getNonce();

	while(bits_nulos_hash < bloque.getBits()) {

		nonce += 1;
		hash = sha256(sha256((bloque.getPrevHash())+'\n'+(bloque.getTxnsHash())+'\n'+(to_string((bloque.getBits())))+'\n'+(to_string(nonce))+'\n'));
		bits_nulos_hash = 0;
	
		for(i = 0; hash[i] == '0' ; i++) {

			bits_nulos_hash += hexa[hash[i]];
		}

		bits_nulos_hash += hexa[hash[i]];

	}

	bloque.setNonce(nonce);

	return true;
}