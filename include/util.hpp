#ifndef UTIL_HPP
#define UTIL_HPP

#include <map>
#include <tuple>

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class Util {
private:
public:
	Util();
	~Util();

	void tokenizar(string text, unordered_map<string, vector<int>> *valores, int linha);
	void tokenizar(string text, map<tuple<int, string>, vector<int>> *valores, int linha);

	void printMap(unordered_map<string, vector<int>> *valores);
	void printMap(map<tuple<int, string>, vector<int>> *valores);
};

template<typename T>
Util<T>::Util() {}

template<typename T>
Util<T>::~Util() {}

/**
 * @brief recebe uma string e tokeniza pelos espacos
 *
 * @param text string que sera tokenizada
 * @param valores map para armazenar os valores tokenizados
 * @param linha linha atual do arquivo
 *
 * utilizado pela funcao readFile
 */
template<typename T>
void Util<T>::tokenizar(string text, unordered_map<string, vector<int>> *valores, int linha) {
	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	vector<int> vec;
	typename T::iterator itr;

	while (getline(sstream, word, del)) {
		if (cont < 5) word.assign(to_string(cont++).append("-").append(word));
		itr = valores->find(word);

		if (itr != valores->end()) itr->second.push_back(linha);
		else {
			vec.clear();
			vec.push_back(linha);
			valores->insert({ word, vec });
		}
	}
}

template<typename T>
void Util<T>::tokenizar(string text, map<tuple<int, string>, vector<int>> *valores, int linha) {
	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	tuple<int, string> tp;

	vector<int> vec;
	typename T::iterator itr;

	while (getline(sstream, word, del)) {
		tp = make_tuple(cont++, word);
		itr = valores->find(tp);

		if (itr != valores->end()) itr->second.push_back(linha);
		else {
			vec.clear();
			vec.push_back(linha);
			valores->insert({ tp, vec });
		}
	}
}

/**
 * @brief imprime o map passado
 *
 * @param valores map que sera impresso possuindo string como chave
 */
template<typename T>
void Util<T>::printMap(unordered_map<string, vector<int>> *valores) {
	typename T::iterator itr;

	for (itr = valores->begin(); itr != valores->end();++itr) {
		cout << itr->first << endl << "-> ";
		for (int i : itr->second) cout << i << " ";
		cout << endl << endl;
	}
}

/**
 * @brief imprime o map passado
 *
 * @param valores map que sera impresso possuindo tupla como chave
 */
template<typename T>
void Util<T>::printMap(map<tuple<int, string>, vector<int>> *valores) {
	typename T::iterator itr;

	for (itr = valores->begin(); itr != valores->end();++itr) {
		cout << get<0>(itr->first) << " " << get<1>(itr->first) << endl << "-> ";
		for (int i : itr->second) cout << i << " ";
		cout << endl << endl;
	}
}

#endif