#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>

struct node{
	int key;
	std::map<int, node*> children;
	node* failure;
	bool terminal;
	bool sink;
	node();
	node(int c);
	node* AddChild(int c);
	bool has(int c);
};

#endif
