#ifndef PACKAGES
#define PACKAGES

#include <map>
#include <set>
#include <vector>
#include <utility>

#include "./template/util.hpp"

/**
 * @brief descricao do map package
 *
 * pair <string, int> -> string = coluna, int = linha
 * set <pair> -> ordena pelo pair, no caso por coluna
 * map <int, set> -> int = quantidade de combinacao
 *
 */

class Packages {
private:
	Util<string> util;
public:
	map < int, set < pair < string, int>>> packages;
	void quebrarEmPacotes(unordered_map < int, vector<string>> combinacoes);

	void insertDado(int _N, string chave, int linha);
	void updateDado(int _N, string chave, int linha);
	void printPackage();
};

#endif