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
	// for (auto item : combinations)
	// 	cout << "[" << item << "] ";
	// cout << endl;
}