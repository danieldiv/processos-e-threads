#include "util.hpp"

Util::Util() {}
Util::~Util() {}

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
void Util::tokenizar(string text, unordered_map<string, vector<int>> *valores, int linha, bool control) {
	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	vector<int> vec;
	unordered_map<string, vector<int>>::iterator itr;

	while (getline(sstream, word, del)) {
		if (cont == 4 && control) return;
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

void Util::tokenizar(string text, map<tuple<int, string>, vector<int>> *valores, int linha) {
	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	tuple<int, string> tp;

	vector<int> vec;
	map<tuple<int, string>, vector<int>>::iterator itr;

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
void Util::printMap(unordered_map<string, vector<int>> *valores) {
	unordered_map<string, vector<int>>::iterator itr;

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
void Util::printMap(map<tuple<int, string>, vector<int>> *valores) {
	map<tuple<int, string>, vector<int>>::iterator itr;

	for (itr = valores->begin(); itr != valores->end();++itr) {
		cout << get<0>(itr->first) << " " << get<1>(itr->first) << endl << "-> ";
		for (int i : itr->second) cout << i << " ";
		cout << endl << endl;
	}
}