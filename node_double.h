#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H

#include "node.h"


template <typename T>
class NodeD : public Node<T>{
private:
	NodeD<T> *prev;

public:
	NodeD(T data);
	void setPrev(NodeD<T> *n);
	NodeD<T> *getPrev();
	~NodeD();
};



template <typename T>
NodeD<T> ::NodeD(T data) : Node <T>(data) {prev = NULL;}

template <typename T>
void NodeD<T> ::setPrev(NodeD<T> *n){
	prev = n;
}

template <typename T>
NodeD<T> *NodeD<T> ::getPrev(){
	return prev;
}

template <typename T>
NodeD<T>::~NodeD(){

}



#endif	//DOUBLE_NODE_H