#ifndef READ_HPP
#define READ_HPP

#include <util.hpp>

#include <fstream>

using namespace std;

template<typename T>
class Read {
private:
public:
	Read();
	~Read();
	// void readFile(string file, unordered_map<string, vector<int>> *valores);
	// void readFile(string file, map<tuple<int, string>, vector<int>> *valores);
	void readFile(string file, T *valores);
};

template<typename T>
Read<T>::Read() {}

template<typename T>
Read<T>::~Read() {}

/**
 * @brief realiza a leitura de um arquivo e salva em um vetor
 *
 * @param file nome do arquivo a ser aberto
 */
template<typename T>
void Read<T>::readFile(string file, T *valores) {
	file.insert(0, "files/").append(".csv");

	ifstream myfile(file);
	string line;
	int contLinha = 0;

	Util u = Util();

	if (myfile.is_open()) {
		while (getline(myfile, line))
			u.tokenizar(line, valores, ++contLinha);
	} else cout << "nao foi possivel abrir o arquivo" << endl;
}

// /**
//  * @brief realiza a leitura de um arquivo e salva em um vetor
//  *
//  * @param file nome do arquivo a ser aberto
//  */
// template<typename T>
// void Read<T>::readFile(string file, unordered_map<string, vector<int>> *valores) {
// 	file.insert(0, "files/").append(".csv");

// 	ifstream myfile(file);
// 	string line;
// 	int contLinha = 0;

// 	Util u = Util();

// 	if (myfile.is_open()) {
// 		while (getline(myfile, line))
// 			u.tokenizar(line, valores, ++contLinha);
// 	} else cout << "nao foi possivel abrir o arquivo" << endl;
// }

// template<typename T>
// void Read<T>::readFile(string file, map<tuple<int, string>, vector<int>> *valores) {
// 	file.insert(0, "files/").append(".csv");

// 	ifstream myfile(file);
// 	string line;
// 	int contLinha = 0;

// 	Util u = Util();

// 	if (myfile.is_open()) {
// 		while (getline(myfile, line))
// 			u.tokenizar(line, valores, ++contLinha);
// 	} else cout << "nao foi possivel abrir o arquivo" << endl;
// }

#endif