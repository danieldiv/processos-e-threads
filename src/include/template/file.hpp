#ifndef FILE_HPP
#define FILE_HPP

#include "util.hpp"
#include <fstream>

#define PATH "src/resource/"

template <typename T>
class File {
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
	file.insert(0, PATH).append(".csv");

	ifstream myfile(file);
	string line;
	int contLinha = 0;

	Util<T> u;

	if (myfile.is_open() && myfile.good()) {
		while (getline(myfile, line))
			u.tokenizar(line, ++contLinha, itens, classes);
	} else cout << "nao foi possivel abrir o File" << endl;
}

#endif