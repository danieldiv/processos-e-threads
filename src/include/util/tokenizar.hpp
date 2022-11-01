#ifndef UTIL_HPP
#define UTIL_HPP

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>

#define N 5

#define RED 	"\x1b[31m"
#define GREEN	"\x1b[32m"
#define BLUE	"\x1b[34m"
#define RESET	"\x1b[0m"

using namespace std;

template<typename T>
class Tokenizar {
public:
	Tokenizar();
	~Tokenizar();

	void tokenizar(string text, int linha,
		unordered_map < string, vector<int>> *itens,
		unordered_map < string, vector<int>> *classes);

	void tokenizar(string text, int linha,
		unordered_map < int, vector<string>> *itens,
		unordered_map < int, vector<string>> *classes);

	void tokenizar(string text, vector<string> *tokens);
};

template<typename T>
Tokenizar<T>::Tokenizar() {}

template<typename T>
Tokenizar<T>::~Tokenizar() {}

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
void Tokenizar<T>::tokenizar(string text, int linha,
	unordered_map < string, vector<int>> *itens,
	unordered_map < string, vector<int>> *classes) {

	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	vector<int> vec;
	typename T::iterator itr;

	while (getline(sstream, word, del)) {
		if (cont < N) {
			word.assign(to_string(cont++).append(",").append(word));
			itr = itens->find(word);

			if (itr != itens->end()) itr->second.push_back(linha);
			else {
				vec.clear();
				vec.push_back(linha);
				itens->insert({ word, vec });
			}
		} else {
			itr = classes->find(word);

			if (itr != classes->end()) itr->second.push_back(linha);
			else {
				vec.clear();
				vec.push_back(linha);
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
void Tokenizar<T>::tokenizar(string text, int linha,
	unordered_map < int, vector<string>> *itens,
	unordered_map < int, vector<string>> *classes) {

	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	vector<string> vec;
	typename T::iterator itr;

	classes->insert({ linha, vec });

	while (getline(sstream, word, del)) {
		if (cont < N) {
			word.assign(to_string(cont++).append(",").append(word));
			vec.push_back(word);
		}
	}
	itens->insert({ linha, vec });
}

template<typename T>
void Tokenizar<T>::tokenizar(string text, vector<string> *tokens) {
	tokens->clear();
	char del = '-';

	stringstream sstream(text);
	string token;

	while (getline(sstream, token, del)) tokens->push_back(token);
}

#endif