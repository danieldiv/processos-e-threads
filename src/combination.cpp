#include "./include/combination.hpp"

Combination::Combination() {}
Combination::~Combination() {}

/**
 * @brief Realiza a combinacao dos valores do vetor passado
 *
 * @param vetor
 * @param perm vetor auxiliar para fazer combinacoes
 * @param index indice do inicio da posicao do vetor, 0 -> inicial, 1 -> segunda posicao ...
 * @param n tamanho do vetor
 * @param k numero de combinacoes a serem feitas
 * @param linha numero da linha do tarefa T
 */
void Combination::combinate(vector<string> vetor,
	int perm[], int index, int n, int k, int linha) {

	static int count = 0;

	if (count == k) {
		temp.assign("");
		for (int i = 0; i < n; i++) {
			if (perm[i])
				temp.append(vetor.at(i)).append("-");
		}

		if (!temp.empty()) {
			temp.erase(temp.end() - 1);

			this->it_pkg = this->package.find(k);

			if (this->it_pkg != this->package.end()) {
				this->updateDado(k, temp, linha);
			} else {
				this->insertDado(k, temp, linha);
			}

			combinations.push_back(temp);
		}

	} else if ((n - index) >= (k - count)) {
		perm[index] = 1;
		count++;
		combinate(vetor, perm, index + 1, n, k, linha);

		perm[index] = 0;
		count--;
		combinate(vetor, perm, index + 1, n, k, linha);
	}
}

void Combination::atribuiCombinations(vector<string> *combinations) {
	combinations->assign(this->combinations.begin(), this->combinations.end());
	this->combinations.clear();
}

void Combination::printCombinations() {
	for (auto item : combinations)
		cout << "[" << item << "] ";
	cout << endl;
}

void Packages::insertDado(int _N, std::string chave, int linha) {
	pair<string, int> dado;
	set<pair<string, int>> valores;

	dado = make_pair(chave, linha);
	valores.insert(dado);

	this->package.insert({ _N, valores });
}

void Packages::updateDado(int _N, std::string chave, int linha) {
	map < int, set < pair < string, int>>>::iterator it_pkg;

	pair<string, int> dado;

	dado = make_pair(chave, linha);

	it_pkg = this->package.find(_N);
	it_pkg->second.insert(dado);
}

std::map < int, std::set < std::pair < std::string, int>>> Packages::getPackage() {
	map < int, std::set < std::pair < std::string, int>>> m;

	map < int, set < pair < string, int>>>::iterator it_pkg;

	for (it_pkg = this->package.begin();
		it_pkg != this->package.end();
		++it_pkg) {

		cout << it_pkg->first << endl;

		for (auto value : it_pkg->second) {
			cout << value.first << " " << value.second << endl;
		}
		cout << endl;
	}
	cout << endl;

	return m;
}