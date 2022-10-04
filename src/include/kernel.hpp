#ifndef OPERACAO_HPP
#define OPERACAO_HPP

#include "./template/util.hpp"
#include "./combination.hpp"

#include <algorithm>

class Kernel {
private:
	unordered_map < string, vector<int>> *itens;
	unordered_map < string, vector<int>> *classes;
	unordered_map < string, vector<int>> *cache;
public:
	Kernel();
	~Kernel();

	void setItens(unordered_map < string, vector<int>> *itens);
	void setClasses(unordered_map < string, vector<int>> *classes);

	void itensInComum(
		unordered_map < int, vector<string>> *tarefaT,
		unordered_map < int, vector<string>> *tarefaT_processamento,
		unordered_map < int, vector<string>> *tarefaT_combinacoes
	);

	void fazCombinacoes(int key, vector<string> colunas,
		unordered_map < int, vector<string>> *tarefaT_combinacoes);

	void fazIntersecoes(unordered_map < int, vector<string>> *tarefaT_combinacoes);
	void checkClasse(vector<int> vecA, unordered_map<string, int> *classes_aux);
	void intersecaoVetores(vector<int> v1, vector<int>v2, vector<int> *res);
	void printResult(unordered_map < int, unordered_map<string, int>> classes_aux);
};

#endif