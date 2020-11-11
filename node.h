#ifndef NODE_H
#define NODE_H


template <typename T>

class Node{
private:
	T data;
	Node<T> *next;

public:
	Node(T d);
	void setNext(Node *n);
	T getData();
	Node<T> *getNext();
	~Node();
};



template <typename T>
Node<T> ::Node(T d){
	data = d;
	next = NULL;
}

template <typename T>
void Node<T> ::setNext(Node<T> *n){
	next = n;
}

template <typename T>
T Node<T> ::getData(){
	return data;
}

template <typename T>
Node<T> *&Node<T> ::getNext(){
	return &next;
}

#endif //NODE_H

