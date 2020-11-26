#include "output.h"
#include <string>
#include <iostream>

Output::Output(){
	value = 0;
	addr = "0";
}

Output::Output(double val, hash_t address){
	value = val;
	addr = address;
}

Output::~Output(){
}

double Output::getValue(){
	return value;
}

hash_t Output::getAddress(){
	return addr;
}

