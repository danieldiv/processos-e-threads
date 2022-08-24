#ifndef READ_HPP
#define READ_HPP

#include "util.hpp"

#include <fstream>

using namespace std;

template<typename T>
class Read {
private:
public:
	Read();
	~Read();
	void readFile(string file, T *valores, T *classes, bool control);
};

template<typename T>
Read<T>::Read() {}

template<typename T>
Read<T>::~Read() {}

/**
 * @brief realiza a leitura de um arquivo e salva em um mapeamento com vetores
 *
 * @tparam T
 * @brief realiza a leitura de um arquivo e salva em um mapeamento com vetores
 *
 * @param file nome do arquivo a ser aberto
 * @param valores map para armazenar os valores lidos e tokenizados
 * @param control controla a quantidade de colunas
 */
template<typename T>
void Read<T>::readFile(string file, T *itens, T *classes, bool control) {
	file.insert(0, "src/files/").append(".csv");

	ifstream myfile(file);
	string line;
	int contLinha = 0;

	Util<T> u;

	if (myfile.is_open()) {
		while (getline(myfile, line))
			u.tokenizar(line, itens, classes, ++contLinha, control);
	} else cout << "nao foi possivel abrir o arquivo" << endl;
}

#endif