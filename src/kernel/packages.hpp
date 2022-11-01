#ifndef PACKAGES
#define PACKAGES

#include <map>
#include <set>
#include <utility>

#include "../include/util/tokenizar.hpp"

// transforma as combinacoes realizadas pelo kernel em pacotes
class Packages {
private:
	Tokenizar<string> util;
public:
	map < int, set < pair < string, int>>> packages;
	void quebrarEmPacotes(unordered_map < int, vector<string>> combinacoes);

	void insertDado(int _N, string chave, int linha);
	void updateDado(int _N, string chave, int linha);
	void printPackage();
};

#endif

// #ifndef PACKAGES_HPP
// #define PACKAGES_HPP

// #include <map>
// #include <set>
// #include <stack>
// #include <utility>

// #include "./util/tokenizar.hpp"

// // transforma as combinacoes realizadas pelo kernel em pacotes
// class Packages {
// private:
// 	Tokenizar<string> util;
// public:
// 	set < pair < string, int>> packages;
// 	void quebrarEmPacotes(unordered_map < int, vector<string>> combinacoes);

// 	void insertDado(int _N, string chave, int linha);
// 	void updateDado(int _N, string chave, int linha);
// 	void printPackage();
// };

// #endif