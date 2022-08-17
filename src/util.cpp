#include "util.hpp"

Util::Util() {}
Util::~Util() {}

/**
 * @brief recebe uma string e tokeniza pelos espacos
 *
 * @param text string que sera tokenizada
 * @param map
 * @param linha linha atual do arquivo
 */
void Util::tokenizar(string text, unordered_map<string, vector<string>> *valores, int linha) {
	char del = ',';
	int cont = 1;

	stringstream sstream(text);
	string word;

	unordered_map<string, vector<string>>::iterator itr;

	// std::map<std::string, Dado>::iterator itr;

	// while (std::getline(sstream, word, del)) {
	// 	itr = palavras->find(word);
	// 	if (itr != palavras->end()) {
	// 		itr->second.setQuant(itr->second.getQuant() + 1);
	// 	} else
	// 		palavras->insert({ word, d });
	// }

	while (getline(sstream, word, del) && cont < 5) {
		word.assign(to_string(cont++).append("-").append(word));
		cout << word << endl;

		itr = valores->find(word);

		if (itr != valores->end()) {
			itr->second.push_back(linha);
		} else
			valores->insert({ word, d });

		map->insert({ word, })
	}
	cout << endl;
}