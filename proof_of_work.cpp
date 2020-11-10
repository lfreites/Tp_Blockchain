map<char,uint> hexa = {

{'0', 4}, {'1', 3}, {'2', 2}, {'3', 2}, {'4', 1}, {'5', 1}, {'6', 1}, {'7', 1}, {'8', 0},
	{'9', 0}, {'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0}
};

bool proof_of_work(header_t * header){

	uint i;
	string hash;
	uint bits_nulos_hash = 0;

	while(bits_nulos_hash < header -> bits) {

		header -> nonce += 1;
		hash = sha256(sha256((header->prev_block)+'\n'+(header->txns_hash)+'\n'+(to_string((header->bits)))+'\n'+(to_string(header->nonce))+'\n'));
		bits_nulos_hash = 0;
	
		for(i = 0; hash[i] == '0' ; i++) {

			bits_nulos_hash += hexa[hash[i]];
		}

		bits_nulos_hash += hexa[hash[i]];

	}

	return true;
}