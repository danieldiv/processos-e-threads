#include "./class/combination.hpp"

Combination::Combination() {}
Combination::~Combination() {}

/**
 * @brief Realiza a combinacao dos valores do vetor passado
 *
 * @param vetor
 * @param perm vetor auxiliar para fazer permutacoes
 * @param index indice do inicio da posicao do vetor, 0 -> inicial, 1 -> segunda posicao ...
 * @param n tamanho do vetor
 * @param k numero de permutacoes a serem feitas
 */
void Combination::combinate(vector<string> vetor, int perm[], int index, int n, int k) {
	// void Combination::combinate(vector<string> vetor, int perm[], int index, int n, int k) {
	static int count = 0;

	if (count == k) {
		temp.assign("");
		for (int i = 0; i < n; i++)
			if (perm[i])
				temp.append(vetor.at(i)).append("-");
		// if (perm.at(i))

		if (!temp.empty()) {
			temp.erase(temp.end() - 1);
			combinations.push_back(temp);
		}

	} else if ((n - index) >= (k - count)) {
		// perm.at(index) = true;
		perm[index] = 1;
		count++;
		combinate(vetor, perm, index + 1, n, k);

		// perm.at(index) = false;
		perm[index] = 0;
		count--;
		combinate(vetor, perm, index + 1, n, k);
	}
}

void Combination::atribuiCombinations(vector<string> *combinations) {
	combinations->assign(this->combinations.begin(), this->combinations.end());
}

void Combination::printCombinations() {
	for (auto item : combinations)
		cout << "[" << item << "] ";
	cout << endl;
}