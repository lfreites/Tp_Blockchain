
#ifndef TRANSACCION_H
#define TRANSACCION_H


typedef struct transaccion transaccion_t;


bool transaccion_leer(transaccion_t * tnx, ifstream *tnx_in);
//Recibe un puntero a una transacción y un puntero a un fichero de entrada con la informacion de la transacción
//y guarda toda su data en la transaccion. En caso de que no esté bien definido el archivo devuelve false,
//si todo sale ok (los inputs, outputs y las cantidades de ambos son correctos) devuelve true

FILE * transaccion_escribir(transaccion_t *tnx);

#endif	//TRANSACCION_H