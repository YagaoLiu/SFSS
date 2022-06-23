#include <iostream>
#include <set>

#include "automaton.h"

using namespace std;

class SSFS: public L_automaton{
	public:
		SSFS(vector<int> &alphabet, set<vector<int>> &fb_words);
		void trim_terminal(node *v);
		int border(vector<int> &str1, vector<int> &str2);
		bool BFS(vector<int> &prefix, vector<int> &suffix, vector<int>& replace);
		void BFT();
	private:
		int tr = 0;
};

SSFS::SSFS(vector<int> &alphabet, set<vector<int>> &fb_words) : L_automaton(alphabet, fb_words){
	visited.clear();
}


void SSFS::trim_terminal(node *v){
	list<node*> queue;
	visited[v] = true;
	queue.push_back(v);
	map<int, node*>::iterator it;
	while(!queue.empty()){
		node* u = queue.front();
		queue.pop_front();
		vector<int> need_to_trim;
		for(it = u->children.begin(); it != u->children.end(); it++){
			if(it->second->terminal){
				need_to_trim.push_back(it->first);
			}else if(!visited[it->second]){
				visited[it->second] = true;
				queue.push_back(it->second);
			}
		}
		if(need_to_trim.size() > 0){
			for(int i = 0; i < need_to_trim.size(); i++){
				u->children.erase(need_to_trim[i]);
			}
		}
	}
}

void SSFS::BFT(){
	node* v = initial;
	visited.clear();
	list<node*> queue;
	queue.push_back(v);
	while(!queue.empty()){
		node* u = queue.front();
		queue.pop_front();
		for(auto it = u->children.begin(); it != u->children.end(); it++){
			if(!visited[it->second]){
				visited[it->second] = true;
				u->sink = true;
				queue.push_back(it->second);
			}
		}
	}
	visited.clear();
}

int SSFS::border(vector<int> &str1, vector<int> &str2){
	int lim = str1.size() < str2.size() ? str1.size() : str2.size();
	vector<int> str(str1);
	str.insert(str.end(), str2.begin(),str2.end());
	int i = 1;
	int len = 0;
	while( i < str.size() ){
		if(str[i] == str[len]){
			len ++;
			i ++;
		}
		else{
			i = i - len + 1;
			len = 0;
		}
	}
	return len>lim ? lim:len;
}

bool SSFS::BFS(vector<int> &prefix, vector<int> &suffix, vector<int>& replace){
	BFT();
	visited.clear();
	vector<vector<int>> danger;
//	int check[] = {16,33,16,29,1,31,19};
//	vector<int> checkp(check, check+sizeof(check)/sizeof(int));
//	bool flag = false;
	for(int i = 0; i < m; i++){
		int k = border(suffix, M[i]);
		if(k>0){
			vector<int> tmp(M[i].begin(), M[i].begin()+M[i].size()-k-1);
			danger.push_back(tmp);
		}
	}
	for(int i = 0; i < danger.size(); i++){
		node * iter = initial;
		vector<int>& s = danger[i];
		for(int j = 0; j < s.size(); j++){
			iter = iter->children[s[j]];
		}
		iter->sink = false;
	}
	node* start = initial;
	for(int i = 0; i < prefix.size(); i++){
		if(start->has(prefix[i])){
			start = start->children[prefix[i]];
		}else{
			cout << "Prefix cannot spell!" << endl;
			return false;
		}	
	}
	node* v = start;
	list<node*> queue;
	map<node*, node*> p;
	map<node*, int> path;
	visited[v] = true;
	node* end = NULL;
	
	p[v] = NULL;
	queue.push_back(v);
	map<int, node*>::iterator it;
	while(!queue.empty()){
		bool flag = false;
		node* u = queue.front();
		queue.pop_front();
		for(it = u->children.begin(); it != u->children.end(); it++){
			if(!visited[it->second]){
				visited[it->second] = true;
				queue.push_back(it->second);
				p[it->second] = u;
				path[it->second] = it->first;
				if(it->second->sink){
					end = it->second;
					flag = true;
				}
			}
		}
		if(flag) break;
	}

	if(end == NULL){
		cout << "No found" << endl;
		string path = "";
		visited.clear();
		return false;
	}
	vector<node*> result;
	node* track = end;
	result.push_back(track);
	while(p[track] != NULL){
		result.push_back(p[track]);
		track = p[track];
	}
	for(int i = result.size()-2; i >= 0; i--)
		replace.push_back(path[result[i]]);
	visited.clear();
	return true;
}	

