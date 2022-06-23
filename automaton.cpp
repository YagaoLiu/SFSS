#include <iostream>
#include <list>
#include <set>
#include <algorithm>

#include "node.h"
#include "automaton.h"

using namespace std;

L_automaton::L_automaton(vector<int> &alphabet, set<vector<int>> &fb_words){
	A = alphabet;
	copy(fb_words.begin(),fb_words.end(), back_inserter(M));
	a = A.size();
	m = M.size();
	initial = new node;
	//build trie
	for(int i = 0; i < m; i++){
		node* iter = initial;
		vector<int>& s = M[i];
		int l = s.size();
		for(int j = 0; j < l; j++){
		       if(iter->has(s[j]))
			       iter = iter->children[s[j]];
		       else
			       iter = iter->AddChild(s[j]);
		       if(j == l-1)
			       iter->terminal = true;
		}	       
	}
	//initial failure function
	for(int i = 0; i < a; i++){
		if(initial->has(A[i])){
			initial->children[A[i]]->failure = initial;
		}else{
			initial->children[A[i]] = initial;
		}
	}
	//width-first search
	BFS(initial);
}

void L_automaton::BFS(node* v){
	visited[v] = true;
	list<node*> queue;
	queue.push_back(v);
	map<int, node*>::iterator it;
	while(!queue.empty()){
		node* u = queue.front();
		queue.pop_front();
		for(it = u->children.begin(); it != u->children.end(); it++){
			node* w = it->second;
			if(!visited[w]){
				visited[w] = true;
				queue.push_back(w);
				for(int i = 0; i < a; i++){
					if(w->has(A[i])){
						w->children[A[i]]->failure = w->failure->children[A[i]];
					}else if(w->terminal){
						w->children[A[i]] = w;
					}else{
						w->children[A[i]] = w->failure->children[A[i]];
					}
				}
			}
		}
	}
}

bool L_automaton::accept(vector<int>& q){
	int l = q.size();
	node * iter = initial;
	for(int i = 0; i < l; i++){
		cout << q[i] << endl;
		if(!iter->has(q[i])){
			cout << "Letter " << q[i] << " not in alphabet" << endl;
			return false;
		}
		iter = iter->children[q[i]];
		if(iter->terminal)
			return false;
	}
	return true;
}

