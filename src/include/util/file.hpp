#ifndef FILE_HPP
#define FILE_HPP

#include "tokenizar.hpp"
#include <fstream>

template <typename T>
class File {
private:
	Tokenizar<T> util;
public:
	File();
	~File();

	void readFile(string file, T *itens, T *classes);
};

template <typename T>
File<T>::File() {}

template <typename T>
File<T>::~File() {}

template <typename T>
void File<T>::readFile(string file, T *itens, T *classes) {
	file.insert(0, "src/resource/").append(".csv");

	ifstream myfile(file);
	string line;
	int contLinha = 0;

	if (myfile.is_open() && myfile.good()) {
		while (getline(myfile, line))
			this->util.tokenizar(line, ++contLinha, itens, classes);
	} else cout << "Nao foi possivel abrir o arquivo" << endl;
}

#endif