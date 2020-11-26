#ifndef INPUT_H
#define INPUT_H 

#include "utils.h"



struct outpoint{
	hash_t tx_id;
	int idx;
};

typedef struct outpoint outpoint_t;


class Input{	
private:
	outpoint_t outpoint; //Como el outpoint es algo propio del input, no abstraigo sus campos de la interfaz del input
	hash_t addr;

public:
	Input();
	Input(hash_t id, int index, hash_t adress);
	~Input();

	//getters
	outpoint_t *getOutpoint();
	hash_t getTnxId();
	int getIndex();
	hash_t getAddress();
};

#endif	//INPUT_H