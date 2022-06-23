#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <set>
#include <list>

#include "automaton.h"
#include "ssfs.h"
#include "function.h"

using namespace std;
using namespace std::chrono;

void str2int(string str, vector<int>& s)
{
    stringstream ss;    
    /* Storing the whole string into string stream */
    ss << str;
  
    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {
  
        /* extracting word by word from stream */
        ss >> temp;
  
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
            s.push_back(found);
  
        /* To save from space at the end of string */
        temp = "";
    }
}

int main(int argc, char* argv[]){
	auto start = high_resolution_clock::now();
	int alphabet_size = atoi(argv[1]);
	string dataset = argv[2];	
	int N = atoi(argv[3]);
	string input = argv[4];
	int M = atoi(argv[5]);
	int k = atoi(argv[6]);
	vector<int> alphabet(alphabet_size,0);
	for(int i = 0; i < alphabet_size; i++){
		alphabet[i] = i+1;
	}
//	ifstream occ_file(input + "_occ.txt");
//	ifstream pattern_file(input+"_patterns.txt");
	ifstream pattern_file(input);
	ifstream text_file(dataset);
	vector<vector<int>> S(N);
	cout << input << endl;
	for(int i = 0; i < N; i++){
		string str;
		getline(text_file, str);
		str2int(str, S[i]);
	}
	set<vector<int>> patterns;
	for(int i = 0; i < M; i++){
		string str;
		getline(pattern_file, str);
		vector<int> tmp;
		str2int(str, tmp);
		patterns.insert(tmp);
	}
	SSFS Q(alphabet, patterns);
	vector<vector<int>> Occ(N);
	vector<vector<int>> resS(N);
	ofstream ssfs_results;
	ofstream time_record;
	int occ = 0;
	time_record.open("sut_time.txt", std::ios::app);
	ssfs_results.open(argv[7]);
	for(int i = 0; i < N; i++){
		int n = S[i].size();
		if(n < k){
			resS[i] = S[i];
		}else{
			int* C;
			C = (int*) calloc(n, sizeof(int));
			bool flag = false;
			for(int j = 0; j < n-k+1; j++){
				vector<int> window(S[i].begin()+j, S[i].begin()+j+k);
				if(patterns.count(window)){
					C[j] = 1;	
					flag = true;
					occ++;
				}
			}
			
			if(n>=k){
				for(int j= n-1; j >= n-k+1; j--){
					C[j] = C[n-k];
				}
			}
			if(flag){
				vector<int> y(ceil(double(n-k+1)/2)*k+floor((double)(n-k+1)/2), 0);
				int hash = alphabet_size+50;
				int l = sut( S[i], C, k, hash, y);
				y.erase(remove(y.begin(), y.end(), 0),y.end());
				for(auto it = 0; it < y.size(); it++){
					cout << y[it] << " ";
				}
				cout << endl;
				vector<int> s(y);
				vector<int>::iterator found;
				found = find(s.begin(), s.end(), hash);
				while(found != s.end()){
					int location = found - s.begin();
					if(found == s.begin()){
						s.erase(s.begin());
						found = find(s.begin(),s.end(),hash);
					}else if(found == s.end()-1 ){
						s.erase(s.end()-1);;
						break;
					}else{
						vector<int> prefix( (found-k+1) < s.begin()? s.begin(): (found-k+1),found);
						vector<int> suffix( found+1, (found+k)>s.end()?(s.end()):(found+k) );
						vector<int> replace;
						if(Q.BFS(prefix,suffix, replace)){
							s.erase(found);
							s.insert(found, replace.begin(), replace.end());
						}
						for(auto it = prefix.begin(); it != prefix.end(); it++){
							cout << *it << " ";
						}
						cout << endl;
						
						for(auto it = suffix.begin(); it != suffix.end(); it++){
							cout << *it << " ";
						}
						cout << endl;
						for(auto it = replace.begin(); it != replace.end(); it++){
							cout << *it << " ";
						}
						cout << endl;

						found = find(s.begin()+location, s.end(),hash);
					}
				}
				resS[i] = s;
			}else{
				resS[i] = S[i];
			}
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	for(int i = 0; i < N; i++){
		for(int j =0; j < resS[i].size(); j++){
			ssfs_results << resS[i][j] << ' ';
		}
		ssfs_results << endl;
	}
	ssfs_results.close();
	time_record << duration.count() << endl;
}		



