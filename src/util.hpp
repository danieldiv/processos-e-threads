#ifndef UTIL_HPP
#define UTIL_HPP

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#define N 5

#define RED 	"\x1b[31m"
#define GREEN	"\x1b[32m"
#define BLUE	"\x1b[34m"
#define RESET	"\x1b[0m"

using namespace std;

template<typename T>
class Util {
public:
	Util();
	~Util();

	void tokenizar(string text, int linha,
		unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes);

	void tokenizar(string text, int linha,
		unordered_map < int, set<string>> *itens,
		unordered_map < int, set<string>> *classes);

	void printMap(T *itens);
};

template<typename T>
Util<T>::Util() {}

template<typename T>
Util<T>::~Util() {}

/**
 * @brief realiza a tokenizacao do texto passado e armazena nos mapas itens e classes
 *
 * @tparam T
 * @param text linha lida do arquivo D
 * @param linha numero da linha atual que sera inserido em um vector de itens
 * @param itens mapa para armazenar a coluna como chave
 * @param classes mapa para armazenar a coluna da classe do arquivo D
 */
template<typename T>
void Util<T>::tokenizar(string text, int linha,
	unordered_map < string, set<int>> *itens,
	unordered_map < string, set<int>> *classes) {

	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	set<int> vec;
	typename T::iterator itr;

	while (getline(sstream, word, del)) {
		if (cont < N) {
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
 * @brief realiza a tokenizacao do texto passado e armazena nos mapas itens e classes
 *
 * @tparam T
 * @param text linha lida do arquivo T
 * @param linha numero da linha atual do arquivo T
 * @param itens mapa que ira armazenar cada linha como chave e as colunas como valores
 * @param classes mapa para inicializar o processamento
 */
template<typename T>
void Util<T>::tokenizar(string text, int linha,
	unordered_map < int, set<string>> *itens,
	unordered_map < int, set<string>> *classes) {

	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	set<string> vec;
	typename T::iterator itr;

	classes->insert({ linha, vec });

	while (getline(sstream, word, del)) {
		if (cont < N) {
			word.assign(to_string(cont++).append(",").append(word));
			vec.insert(word);
		}
	}
	itens->insert({ linha, vec });
}

template<typename T>
void Util<T>::printMap(T *itens) {
	typename T::iterator itr;

	for (itr = itens->begin();itr != itens->end();itr++) {
		cout << itr->first << "-> ";

		for (auto v : itr->second) cout << v << " ";
		cout << endl;
	}
}

#endif