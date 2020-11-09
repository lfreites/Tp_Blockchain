
#ifndef TRANSACCION_H
#define TRANSACCION_H
#include <fstream>

using namespace std;


typedef struct transaccion transaccion_t;


bool transaccion_leer(transaccion_t * tnx, ifstream tnx_in);
//Recibe un puntero a una transacción y un puntero a un fichero de entrada con la informacion de la transacción
//y guarda toda su data en la transaccion. En caso de que no esté bien definido el archivo devuelve false,
//si todo sale ok (los inputs, outputs y las cantidades de ambos son correctos) devuelve true

void transaccion_escribir(transaccion_t *tnx, ofstream tnx_out);
//Vuelca en un archivo de salida apuntado por tnx_out los datos correspondientes a la transacción apuntada
//por tnx en el formato correspondiente

#endif	//TRANSACCION_H