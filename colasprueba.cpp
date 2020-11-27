#include <iostream>
#include "queue.h"


using namespace std;

int main(int argc, char const *argv[]){
	
	Queue<int> *cola1 = new Queue<int>(10);
	Queue<int> cola2;

	cout << "El tamaño de la cola 1 es " << cola1->length() << endl;
	cout << "El tamaño de la cola 2 es " << cola2.length() << endl;

	if (!cola1->empty()){
		cout << "EL primer elemento de la cola 1 es <" << cola1->first() << '>' << endl;
		cout << "El último elemento de la cola 1 es <" << cola1->last() << '>' << endl;
	}	
	
	for (int i = 1; i <= 100; i++)
		cola2.enqueue(i);
	cout << "\nAhora el tamaño de la cola 2 es " << cola2.length() << endl << endl;

	if (!cola2.empty()){
		cout << "El primer elemento de la cola 1 es <" << cola2.first() << '>' << endl;
		cout << "El último elemento de la cola 1 es <" << cola2.last() << '>' << endl;
	}

	

	while (!cola2.empty()){
		cout << "Sacando el primer elemento de la cola 2: <" << cola2.dequeue() << '>' << endl;
	}
	cout << "Ahora la cola 2 está vacía." << endl;
	
	delete cola1;

	return 0;
}