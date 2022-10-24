#ifndef PACKAGES
#define PACKAGES

#include <map>
#include <set>
#include <string>
#include <utility>

/**
 * @brief descricao do map pacotes
 *
 * pair <string, int> -> string = coluna, int = linha
 * set <pair> -> ordena pelo pair, no caso por coluna
 * map <int, set> -> int = quantidade de combinacao
 *
 */

class Packages {
protected:
	std::map < int, std::set < std::pair < std::string, int>>> package;
public:
	void insertDado(int _N, std::string chave, int linha);
	void updateDado(int _N, std::string chave, int linha);

	std::map < int, std::set < std::pair < std::string, int>>> getPackage();
};

#endif