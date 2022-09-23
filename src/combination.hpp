#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Combination {
private:
	unordered_map<string, vector<string>> combinations;
public:
	Combination();
	~Combination();

	void doCombination(
		unordered_map<int, set<string>> processo, string key, bool controle);
};

void Combination::doCombination(
	unordered_map<int, set<string>> processo, string key, bool controle) {

	set<string> aux;
	unordered_map<int, set<string>>::iterator itr;


	for (itr = processo.begin();itr != processo.end();++itr) {
		key = itr->first;
		aux = itr->second;
	}
}

#endif