#include "./kernel/packages.hpp"

void Packages::quebrarEmPacotes(unordered_map < int, vector<string>> combinacoes) {
	unordered_map < int, vector<string>>::iterator itr;
	map < int, set < pair < string, int>>>::iterator it_pkg;

	int tam;
	vector<string> vec;

	for (itr = combinacoes.begin(); itr != combinacoes.end();++itr) {
		for (auto combinacao : itr->second) {
			util.tokenizar(combinacao, &vec);

			tam = vec.size();
			it_pkg = packages.find(tam);

			if (it_pkg != packages.end())
				updateDado(tam, combinacao, itr->first);
			else
				insertDado(tam, combinacao, itr->first);
		}
	}
}

/**
 * @brief insere combinacoes no package de acordo com o tamanho de combinacoes
 *
 * @param _N tamanho das combinacoes que sera utilizada para a chave do map
 * @param chave chave do pair que sera inserida em um set para adicionar no map de acordo com o tamanho _N
 * @param linha valor do pair
 */
void Packages::insertDado(int _N, string chave, int linha) {
	pair<string, int> dado;
	set<pair<string, int>> valores;

	dado = make_pair(chave, linha);
	valores.insert(dado);

	this->packages.insert({ _N, valores });
}

void Packages::updateDado(int _N, string chave, int linha) {
	map < int, set < pair < string, int>>>::iterator it_pkg;

	pair<string, int> dado;

	dado = make_pair(chave, linha);

	it_pkg = this->packages.find(_N);
	it_pkg->second.insert(dado);
}