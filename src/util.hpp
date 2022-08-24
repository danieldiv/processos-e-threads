#ifndef UTIL_HPP
#define UTIL_HPP

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Util {
public:
	void tokenizar(string text, int linha,
		unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes);

	void tokenizar(string text, int linha,
		unordered_map < int, set<string>> *itens,
		unordered_map < int, set<string>> *classes);

	void printMap(unordered_map < string, set<int>> *itens);
	void printMap(unordered_map < int, set<string>> *itens);
};

void Util::tokenizar(string text, int linha,
	unordered_map < string, set<int>> *itens,
	unordered_map < string, set<int>> *classes) {

	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	set<int> vec;
	unordered_map < string, set<int>>::iterator itr;

	while (getline(sstream, word, del)) {
		if (cont < 5) {
			word.assign(to_string(cont++).append(",").append(word));

			itr = itens->find(word);

			if (itr != itens->end()) itr->second.insert(linha);
			else {
				vec.clear();
				vec.insert(linha);
				itens->insert({ word, vec });
			}
		} else {
			itr = classes->find(word);

			if (itr != classes->end()) itr->second.insert(linha);
			else {
				vec.clear();
				vec.insert(linha);
				classes->insert({ word, vec });
			}
		}
	}
}

void Util::tokenizar(string text, int linha,
	unordered_map < int, set<string>> *itens,
	unordered_map < int, set<string>> *classes) {

	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	set<string> vec;
	unordered_map < int, set<string>>::iterator itr;

	while (getline(sstream, word, del)) {
		if (cont < 5) {
			word.assign(to_string(cont++).append(",").append(word));
			vec.insert(word);
		}
	}
	itens->insert({ linha, vec });
}

void Util::printMap(unordered_map < string, set<int>> *itens) {
	unordered_map < string, set<int>>::iterator itr;

	for (itr = itens->begin();itr != itens->end();itr++) {
		cout << itr->first << endl << "-> ";

		for (auto v : itr->second) cout << v << " ";
		cout << endl << endl;
	}
}

void Util::printMap(unordered_map < int, set<string>> *itens) {
	unordered_map < int, set<string>>::iterator itr;

	for (itr = itens->begin();itr != itens->end();itr++) {
		cout << itr->first << endl << "-> ";

		for (auto v : itr->second) cout << v << " ";
		cout << endl << endl;
	}
}

#endif