#include "node.h"

node::node(){
	terminal = false;
	sink = true;
}

node::node(int c){
	key = c;
	terminal = false;
	sink = true;
}

node* node::AddChild(int c){
	node* child = new node (c);
	children[c] = child;
	return child;
}

bool node::has(int c){
	if(children.find(c) != children.end())
		return true;
	else
		return false;
}
