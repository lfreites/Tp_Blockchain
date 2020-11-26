#include "input.h"
#include <string>
#include <iostream>

Input::Input(){
	outpoint.tx_id = "0";
	outpoint.idx = 0;
	addr = "0";
}

Input::Input(hash_t id, int index, hash_t adress){
	outpoint.tx_id = id;
	outpoint.idx = index;
	addr = adress;
}

Input::~Input(){
}

outpoint_t *Input::getOutpoint(){
	outpoint_t *outpnt = new outpoint_t;
	outpnt->tx_id = this->outpoint.tx_id;
	outpnt->idx = this->outpoint.idx;

	return outpnt;
}

hash_t Input::getTnxId(){
	return outpoint.tx_id;
}

int Input::getIndex(){
	return outpoint.idx;
}

hash_t Input::getAddress(){
	return addr;
}


