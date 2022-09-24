#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>

#define N 4

using namespace std;

class Combination {
private:
	vector<string> combinations;
	string temp;
public:
	Combination();
	~Combination();

	void combinate(vector<string> *vetor, vector<bool> *perm, int index, int n, int k);
	void printCombinations();
};

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
void Combination::combinate(vector<string> *vetor, vector<bool> *perm, int index, int n, int k) {
	static int count = 0;

	if (count == k) {
		temp.assign("");
		for (int i = 0; i < n; i++)
			if (perm->at(i))
				temp.append(vetor->at(i));

		if (!temp.empty())
			combinations.push_back(temp);

	} else if ((n - index) >= (k - count)) {
		perm->at(index) = true;
		count++;
		combinate(vetor, perm, index + 1, n, k);

		perm->at(index) = false;
		count--;
		combinate(vetor, perm, index + 1, n, k);
	}
}

void Combination::printCombinations() {
	for (auto item : combinations)
		cout << item << " ";
	cout << endl;
}

#endif