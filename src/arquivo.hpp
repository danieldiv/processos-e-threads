#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include "util.hpp"
#include <fstream>

// template <typename T>
class Arquivo {
public:
	void readFile(string file,
		unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes);

	void readFile(string file,
		unordered_map < int, set<string>> *itens,
		unordered_map < int, set<string>> *classes);
};

void Arquivo::readFile(string file,
	unordered_map < string, set<int>> *itens,
	unordered_map < string, set<int>> *classes) {

	file.insert(0, "src/files/").append(".csv");

	ifstream myfile(file);
	string line;
	int contLinha = 0;

	Util u;

	if (myfile.is_open()) {
		while (getline(myfile, line))
			u.tokenizar(line, ++contLinha, itens, classes);
	} else cout << "nao foi possivel abrir o arquivo" << endl;
}

void Arquivo::readFile(string file,
	unordered_map < int, set<string>> *itens,
	unordered_map < int, set<string>> *classes) {

	file.insert(0, "src/files/").append(".csv");

	ifstream myfile(file);
	string line;
	int contLinha = 0;

	Util u;

	if (myfile.is_open()) {
		while (getline(myfile, line))
			u.tokenizar(line, ++contLinha, itens, classes);
	} else cout << "nao foi possivel abrir o arquivo" << endl;
}

#endif