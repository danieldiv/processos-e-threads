#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include "util.hpp"
#include <fstream>

template <typename T>
class Arquivo {
public:
	Arquivo();
	~Arquivo();

	void readFile(string file, T *itens, T *classes);
};

template <typename T>
Arquivo<T>::Arquivo() {}

template <typename T>
Arquivo<T>::~Arquivo() {}

template <typename T>
void Arquivo<T>::readFile(string file, T *itens, T *classes) {
	file.insert(0, "src/files/").append(".csv");

	ifstream myfile(file);
	string line;
	int contLinha = 0;

	Util<T> u;

	if (myfile.is_open() && myfile.good()) {
		while (getline(myfile, line))
			u.tokenizar(line, ++contLinha, itens, classes);
	} else cout << "nao foi possivel abrir o arquivo" << endl;
}

#endif