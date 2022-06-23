#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include <string>
#include <map>
#include <set>

#include "node.h"

class L_automaton{
	public:
		L_automaton(std::vector<int> &alphabet, std::set<std::vector<int>> &fb_words);
		bool accept(std::vector<int> &q);
		std::vector<int> A;
		int a;
		std::vector<std::vector<int>> M;
		int m;
		node *initial;
		std::map<node*, bool> visited;
		void BFS(node* v);
};

#endif
