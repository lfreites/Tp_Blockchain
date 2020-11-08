//Modelos de estructuras básicas de Algochain

typedef std::string hash_t;



typedef struct bloque{
	header_t header;
	body_t body;
}bloque_t;


class Header{
	hash_t prev_block;		//hash del bloque anterior en la blockchain ( = SHA256(SHA256(bloque anterior)) )
	hash120_t txns_hash;	//hash de todas las transacciones incluidas en el bloque de este header
	int bits;					//dificultad (cantidad de 0s necesarios)
	string nonce;
};
//prev_block se inicializa en ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff

typedef struct body{
	size_t tnxs_count;			//cantidad de transacciones del bloque
	transaccion_t *tnxs;		//secuencia con dichas transacciones
}body_t;

typedef struct transaccion{
	size_t n_tx_in;
	input_t *inputs;
	size_t n_tx_out;
	output_t *outputs;
}transaccion_t;
//Esto en realidad sería el formato del archivo tnxs.txt, repetido tantas veces como transacciones almacene

class Output{
	int value;
	hash_t addr;	
}

class Input{
	typedef struct outpoint{
		hash_t tx_id;
		int idx;
	}outpoint_t;
	hash_t addr;
}


//sirve para identificar el origen de los fondos del input correspondiente



////////////////////////////////////////////////////////////////
