#ifndef OPERACAO_HPP
#define OPERACAO_HPP

#include "./utils/util.hpp"

#include <algorithm>

class Operacao {
public:
	Operacao();
	~Operacao();

	void itensInComum(
		unordered_map < string, set<int>> *itens,
		unordered_map < int, set<string>> *tarefaT,
		unordered_map < int, set<string>> *tarefaT_processamento,
		unordered_map < int, vector<string>> *tarefaT_permutacoes);

	void fazPermutacoes(int key, set<string> vetor,
		unordered_map < int, vector<string>> *tarefaT_permutacoes);

	void fazIntersecoes(
		unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *tarefaT_processamento);

	void checkClasse(set<int> vecA,
		unordered_map < string, set<int>> *classes,
		unordered_map<string, int> *classes_aux);

	void faz1(unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *tarefaT_processamento,
		unordered_map<int, unordered_map<string, int>> *classes_aux);

	void faz2(unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *tarefaT_processamento,
		unordered_map<int, unordered_map<string, int>> *classes_aux);

	void faz3(unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *tarefaT_processamento,
		unordered_map<int, unordered_map<string, int>> *classes_aux);

	void intersecaoVetores(set<int> v1, set<int>v2, vector<int> *res);
};

#endif