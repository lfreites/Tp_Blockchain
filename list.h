#ifndef LIST_H
#define LIST_H

#include "node.h"

template <typename T>
class List{
protected:
	Node<T> *first;
	Node<T> *last;
	size_t n;

public:
	List();
	~List();
	
	Node <T> getFirst();
	//Devuelve un puntero al primer elemento de la lista

	Node<T> getLast();
	//Devuelve un puntero al último elemento de la lista
	
	Node<T> get(size_t index);
	//Devuelve un untero al elemento guardado en la posición index.
	//En caso de index desbordar el número de elementos devuelve NULL

	bool empty();
	//devuelve true si la lista está vacía (no contiene elementos), si no devuelve false
	
	void append(T data);
	//Agrega un elemento al final de la lista
	
	Node<T> popFirst();
	//saca el primer elemento de la lista y lo devuelve.
	
	Node<T> popLast();
	//saca el último elemento de la lista y lo devuelve.


};


template <typename T>
List<T> ::List(){
	first = NULL;
	last = NULL;
	n = 0;
}

template <typename T>
List<T> ::List(T data){
	first = new Node(data);
	last = first;
	n = 1;
}

template <typename T>
Node<T> *List<T> ::getFirst(){
	return fisrt;
}

template <typename T>
Node<T> *List<T> ::getLast(){
	return last;
}

template <typename T>
Node<T> * List<T> ::get(size_t index){
	if (index > n)
		return NULL;
	else if (index == n)
		return last;
	
	size_t i = 0
	Node<T> *element = fisrt;
	while (i != index){
		element = element->getNext();
		i++
	}
	return element;
}

template <typename T>
bool List<T> ::empty(){
	return first == NULL;
}

template <typename T>
void List<T> ::append(T data){
	Node<T> *newNode = new Node(data);
	last->setNext(newNode);
	last = newNode;
	n++;
}


template <typename T>
Node<T> *List<T> ::popFirst(){
	Node<T> *aux = first;
	fisrt = aux->getNext();
	n--;
	return aux; 
} 

template <typename T>
Node<T> *List<T> ::popLast(){
	Node<T> *aux = last;
	Node<T> *newLast = first;

	while(newLast->getNext() != last)	//Esto lo tengo que hacer porque es simplemente enlazada
		newLast = newLast->getNext();

	last = newLast;
	n--;
	return aux
}

template <typename T>
List<T> ::~List(){
	while(first != last){
		Node<T> *aux = popFirst()
		delete aux;
	}
	delete first;
}

#endif //LIST_H