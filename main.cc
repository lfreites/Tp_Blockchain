#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "tnx.h"
#include "cmdline.h"
#include "input.h"
#include "output.h"
#include "bloque.h"
#include "sha256.h"
#include "proof_of_work.h"
#include "utils.h"


using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_help(string const &);

// Tabla de opciones de línea de comando. El formato de la tabla
// consta de un elemento por cada opción a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opción lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opción.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opción en caso que no esté explícitamente presente
//   en la línea de comandos del programa. Si la opción no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al método de parseo de la opción,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La última columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opción: cuando la
//   opción es obligatoria, deberá activarse OPT_MANDATORY.
//
// Además, la última entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//

/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

struct utxos{

	hash_t id_user;
	hash_t transaccion;
	double balance;
	size_t n_output;
};

typedef struct utxos utxos_t;

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)
static fstream fs;



/*****************************************************/

static void opt_input(string const &arg) {
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_output(string const &arg){
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void opt_help(string const &arg) {
	cout << "cmdline [-i file] [-o file]"
	     << endl;
	exit(0);
}

hash_t sha256_merkle(vector <transaccion_t *> * tnes, size_t l){

	size_t i;
	vector <hash_t> hashes(l+1);


	if((l % 2) == 1){

		for(i = 0; i < l; i++)
			hashes[i] = sha256(sha256(transaccion_hash((*tnes)[i])));

		hashes[i] = hashes[i-1];

		l++;

	}

	else {

		for(i = 0; i < l; i++)
			hashes[i] = sha256(sha256(transaccion_hash((*tnes)[i])));

	}	

	while(l != 1){

		if((l % 2) == 0) {

			for(i = 0; i < l; i+=2)
				hashes[i/2] = sha256(sha256(hashes[i]+hashes[i+1]));
	
			l = l/2;
		}

		else {

			hashes[l] = hashes[l-1];
			l++;

		}
	}

	return hashes[0];

}




int main(int argc, char * const argv[]) {

	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

	size_t i, j, k, difficulty, nonce;
	double value;
	size_t capacidad_mempool = INIT_SIZE, capacidad_algochain = INIT_SIZE, capacidad_users = INIT_SIZE;
	size_t utilizado_mempool = 0, utilizado_algochain = 0, utilizado_users = 0;
	string line;
	hash_t prev = DEFAULT_PREV, genesis = GENESIS_PREV;
	hash_t ts = "", ts2, ts3, user, dst;

	vector <Bloque *> algochain(capacidad_algochain);
	vector <transaccion_t *> mempool(capacidad_mempool);
	vector <utxos_t> users(capacidad_users);


	while(!iss -> eof()) {

		(*iss) >> line;

		if(line.compare("transfer") == 0){

			double suma = 0, suma2 = 0;

			if(utilizado_mempool == capacidad_mempool){
				mempool.resize(capacidad_mempool + CHOP_SIZE);
				capacidad_mempool += CHOP_SIZE;
			}

			transaccion_t * tran = new transaccion_t;
			tran -> n_tx_in = 0;
			tran -> n_tx_out = 0;
			getline((*iss), line);
			istringstream in(line);

			in >> user;

			user = sha256(sha256(user));
			i = utilizado_users;

			while(in >> dst >> value){

				if(i == capacidad_users){
					users.resize(capacidad_users + CHOP_SIZE);
					capacidad_users += CHOP_SIZE;
				}

				dst = sha256(sha256(dst));

				users[i].id_user = dst;
				users[i].balance = value;
				i++;

			}

			for(j = utilizado_users; j < i; j++)
				suma += users[j].balance;

			for(j = 0; j < utilizado_users; j++){
				if(users[j].id_user == user && suma > suma2){
					suma2 += users[j].balance;
					tran -> n_tx_in++;
				}
			}	

			if(suma <= suma2){

				tran -> inputs = new Input*[tran->n_tx_in];
				for (j = 0; j < tran->n_tx_in; j++){

					for(k = 0; k < utilizado_users;k++){

						if(users[k].id_user == user){
							tran->inputs[j] = new Input(users[k].transaccion, users[k].n_output, user);
							users[k].id_user = "";
							users[k]. transaccion = "";
							k = utilizado_users;
						}
					}
				}

				tran -> n_tx_out = i - utilizado_users;
				tran -> outputs = new Output * [tran->n_tx_out+1];
				j = utilizado_users;
				for(k = 0; utilizado_users < i; utilizado_users++, k++){

					tran->outputs[k] = new Output(users[utilizado_users].balance, users[utilizado_users].id_user);
					users[utilizado_users].n_output = k;

				}

				if(suma != suma2){

					tran -> n_tx_out += 1;
					tran->outputs[k] = new Output(suma2 - suma, user);
					users[utilizado_users].balance = suma2 - suma;
					users[utilizado_users].n_output = k;
					users[utilizado_users].id_user = user;
					utilizado_users++;
				}

				ts = sha256(sha256(transaccion_hash(tran)));

				mempool[utilizado_mempool] = tran;
				utilizado_mempool++;

				while(j < utilizado_users){
					users[j].transaccion = ts;
					j++;
				}

				(*oss) << ts << endl;

			}
			else{
				delete(tran);
				(*oss) << "FAIL" << endl;
			}

		}

		else if(line.compare("balance") == 0){

			(*iss) >> line;
			user = sha256(sha256(line));
			value = 0;

			for(i = 0; i < utilizado_users; i++){

				if(users[i].id_user == user)
					value += users[i].balance;
			}

			(*oss) << value << '\n';

		}
		else if(line.compare("block") == 0){

			(*iss) >> line;

			for(i = 0; i < utilizado_algochain; i++){

				if(line == sha256(sha256((algochain[i])->bloque_hash(transaccion_hash)))){

					(algochain[i])->bloque_escribir(oss, transaccion_escribir);
					i = utilizado_algochain;
				}

			}

			if(i == utilizado_algochain)
				(*oss) << "FAIL" << endl;

		}
		else if(line.compare("txn") == 0 || line.compare("transaction") == 0 ){

			(*iss) >> line;

			for(i = 0; i < utilizado_mempool; i++){

				if(line == sha256(sha256(transaccion_hash(mempool[i])))){

					transaccion_escribir(mempool[i],oss);
					i = utilizado_mempool;
				}
			}

			if(i == utilizado_mempool){

				for(i = 0; i < utilizado_algochain; i++){

					size_t txnes = algochain[i]->getCantidadTxns();
					for(j = 0; j < txnes; j++){

						if(line == sha256(sha256(transaccion_hash((*(algochain[i]->getTnes()))[j])))) {

							transaccion_escribir((*(algochain[i]->getTnes()))[j], oss);
							j = txnes;
							i = utilizado_algochain;

						}
					}
				}

				if(i == utilizado_algochain)
					(*oss) << "FAIL" << endl;
			}

		}
		else if(line.compare("mine") == 0){

			if(utilizado_algochain == capacidad_algochain){
				algochain.resize(capacidad_algochain + CHOP_SIZE);
				capacidad_algochain += CHOP_SIZE;
			}

			(*iss) >> line;
			stringstream aux(line);
			aux >> difficulty;

			if(utilizado_mempool != 0){

				vector <transaccion_t *> * tnes;
				tnes = new vector <transaccion_t *> (capacidad_mempool);
				(*tnes).swap(mempool);

				ts = sha256(sha256((algochain[utilizado_algochain-1])->bloque_hash(transaccion_hash)));
				ts2 = sha256_merkle(tnes, utilizado_mempool);

				algochain[utilizado_algochain] = new Bloque(ts, ts2, difficulty, difficulty, utilizado_mempool, tnes);

				if(proof_of_work(*(algochain[utilizado_algochain])) != true){
					(*oss) << "FAIL" << endl;
					mempool.swap(*tnes);
					delete(tnes);
					delete(algochain[utilizado_algochain]);
				}

				else{

				utilizado_algochain++;
				utilizado_mempool = 0;

				(*oss) << sha256(sha256((algochain[utilizado_algochain-1])->bloque_hash(transaccion_hash))) << '\n';

				}
			}
			else
				(*oss) << "FAIL" << endl;
		}
		else if(line.compare("init") == 0){

			if(utilizado_algochain != 0){

				for(j= 0; j < utilizado_algochain; j++){
					algochain[j]->bloque_destruir(transaccion_destruir);
					delete(algochain[j]);
				}
				for(j = 0; j < utilizado_mempool; j++)
					transaccion_destruir(mempool[j]);

				utilizado_users = 0;	
				utilizado_mempool = 0;
				utilizado_algochain = 0;

			}

			(*iss) >> line;
			user = sha256(sha256(line));
			(*iss) >> line;
			stringstream aux(line);
			aux >> value;
			(*iss) >> line;
			stringstream aux2(line);
			aux2 >> difficulty;

			vector <transaccion_t *> * tn_genesis;
			tn_genesis = new vector <transaccion_t *> (1);
	
			(*tn_genesis)[0] = transaccion_genesis_crear(value, user, genesis);
			ts = sha256_merkle(tn_genesis, 1);

			algochain[utilizado_algochain] = new Bloque(genesis, ts, difficulty, difficulty, 1, tn_genesis);
			utilizado_algochain++;

			proof_of_work(*(algochain[0]));

			users[utilizado_users].id_user = user;
			users[utilizado_users].balance = value;
			users[utilizado_users].n_output = 0;
			users[utilizado_users].transaccion = sha256(sha256(transaccion_hash((*tn_genesis)[0])));
			utilizado_users++;


			(*oss) << sha256(sha256((algochain[0])->bloque_hash(transaccion_hash))) << '\n';

		}
		else if(line.compare("save") == 0){

			(*iss) >> line;
			fs.open(line, ios::out);
		
			if (!(&fs)->good()) {
				cerr << "FAIL"
				     << endl;
				fs.close();
			}

			else{

				for(i = 0; i < utilizado_algochain; i++){

					algochain[i]->bloque_escribir(&fs, transaccion_escribir);
				}

				if ((&fs)->bad()) {
					cerr << "FAIL"
				    	 << endl;
				    fs.close();	 
				}

				else{

					fs.close();
					(*oss) << "OK" << endl;
				}
			}
		}
		else if(line.compare("load") == 0){

			size_t num_tnes;
			bool do_block = true;

			if(utilizado_algochain != 0){

				for(j= 0; j < utilizado_algochain; j++){
					algochain[j]->bloque_destruir(transaccion_destruir);
					delete(algochain[j]);
				}
				for(j = 0; j < utilizado_mempool; j++)
					transaccion_destruir(mempool[j]);

				utilizado_users = 0;	
				utilizado_mempool = 0;
				utilizado_algochain = 0;

			}

			(*iss) >> line;
			fs.open(line, ios::in);
		
			if (!(&fs)->good()) {
				cerr << "FAIL"
				     << endl;
				fs.close();
			}

			else{

				for(utilizado_algochain = 0; !(&fs) -> eof() ; utilizado_algochain++) {
					if(utilizado_algochain == capacidad_algochain){
						algochain.resize(capacidad_algochain + CHOP_SIZE);
						capacidad_algochain += CHOP_SIZE;
					}

					(fs) >> ts;
					(fs) >> ts2;
					(fs) >> line;
					stringstream aux(line);
					aux >> difficulty;
					(fs) >> line;
					stringstream aux2(line);
					aux2 >> nonce;
					(fs) >> line;
					stringstream aux3(line);
					aux3 >> num_tnes;
					vector <transaccion_t *> * tnes;
					tnes = new vector <transaccion_t *> (num_tnes);

					for(i = 0; i < num_tnes; i++){
				
						(*tnes)[i] = transaccion_crear();

						if(transaccion_leer((*tnes)[i], &fs) != true){
							if((*tnes)[i]->n_tx_in != 0) {
								cerr << "FAIL" << endl;
								fs.close();
								for(j= 0; j < utilizado_algochain; j++){
									algochain[j]->bloque_destruir(transaccion_destruir);
									delete(algochain[j]);
								}
								
								utilizado_users = 0;	
								utilizado_algochain = 0;
								delete(tnes);
							}

							else{

								delete(tnes);
								utilizado_algochain--;
								i = num_tnes;
								do_block = false;
							}

						}
						else {
							for(j = 0; j < (*tnes)[i]->n_tx_in; j++){

								if((*tnes)[i]->inputs[j]->getTnxId() != genesis){

									for(k = 0; k < utilizado_users;k++){
										if((*tnes)[i]->inputs[j]->getTnxId() == users[k].transaccion && (*tnes)[i]->inputs[j]->getAddress() == users[k].id_user){
											users[k].id_user = "";
											users[k].transaccion = "";
											users[k].balance = 0;
											users[k].n_output = 0;
											k = utilizado_users;
										}
									}
								}
							}

							ts3 = sha256(sha256(transaccion_hash((*tnes)[i])));

							for(j = 0; j < (*tnes)[i]->n_tx_out; j++){

								if(utilizado_users == capacidad_users){
									users.resize(capacidad_users + CHOP_SIZE);
									capacidad_users += CHOP_SIZE;
								}

								users[utilizado_users].transaccion = ts3;
								users[utilizado_users].id_user = (*tnes)[i]->outputs[j]->getAddress();
								users[utilizado_users].balance = (*tnes)[i]->outputs[j]->getValue();
								users[utilizado_users].n_output = j;
								utilizado_users++;
							}
								
						}
					}
						if(do_block == true)
							algochain[utilizado_algochain] = new Bloque(ts,ts2, difficulty, nonce,num_tnes,tnes);
					}

				if ((&fs)->bad()) {
					cerr << "FAIL"
					     << endl;
					fs.close();
				}

				else if (!(&fs)->eof()) {
					cerr << "FAIL"
					     << endl;
					fs.close();
				}

				else{
					fs.close();
					(*oss) << sha256(sha256((algochain[utilizado_algochain-1])->bloque_hash(transaccion_hash))) << '\n';
				}

			}

		}

	}

	for(i = 0; i < utilizado_mempool; i++)
		transaccion_destruir(mempool[i]);
	vector <transaccion_t *>().swap(mempool);

	vector <utxos_t>().swap(users);

	for(i = 0; i < utilizado_algochain; i++){
		algochain[i]->bloque_destruir(transaccion_destruir);
		delete(algochain[i]);
	}
	vector <Bloque *>().swap(algochain);

	if (oss->bad()) {
		cerr << "cannot write to output stream."
		     << endl;
		exit(1);
	}
	if (iss->bad()) {
		cerr << "cannot read from input stream."
		     << endl;
		exit(1);
	}
	if (!iss->eof()) {
		cerr << "cannot find EOF on input stream."
		     << endl;
		exit(1);
	}

	return 0;
}
