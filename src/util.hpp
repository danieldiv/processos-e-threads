#ifndef UTIL_HPP
#define UTIL_HPP

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

template <typename T>
class Util {
private:
public:
	Util();
	~Util();

	void tokenizar(string text, T *itens, T *classes, int linha, bool control);
	// void tokenizar(string text, map<tuple<int, string>, vector<int>> *valores, int linha);

	void printMap(T *valores);
	// void printMap(map<tuple<int, string>, vector<int>> *valores);
};

template <typename T>
Util<T>::Util() {}

template <typename T>
Util<T>::~Util() {}

/**
* @brief recebe uma string e tokeniza pelos espacos
 *
 * @param text string que sera tokenizada
 * @param valores map para armazenar os valores tokenizados
 * @param linha linha atual do arquivo
 * @param control utilizado para reduzir a ultima coluna a ser tokenizada
 *
 * utilizado pela funcao readFile
 */
template <typename T>
void Util<T>::tokenizar(string text, T *itens, T *classes, int linha, bool control) {
	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	set<int> vec;
	typename T::iterator itr;

	while (getline(sstream, word, del)) {
		if (cont == 4 && control) return;
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

/**
 * @brief imprime o map passado
 *
 * @param valores map que sera impresso possuindo string como chave
 */
template <typename T>
void Util<T>::printMap(T *valores) {
	typename T::iterator itr;

	for (itr = valores->begin(); itr != valores->end();++itr) {
		cout << itr->first << endl << "-> ";
		for (int i : itr->second) cout << i << " ";
		cout << endl << endl;
	}
}

#endif