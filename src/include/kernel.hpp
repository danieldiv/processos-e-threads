#ifndef OPERACAO_HPP
#define OPERACAO_HPP

#include "./template/util.hpp"
#include "./combination.hpp"
#include "./intersetion.hpp"

#include <algorithm>

class Kernel {
private:
	int cont_cache_found;
	int cont_cache_not_found;

	unordered_map < string, vector<int>> *itens;
	unordered_map < string, vector<int>> *classes;
	unordered_map < string, unordered_map<string, int>> cache;

	Combination combination;
	Intersection intersection;
public:
	Kernel();
	~Kernel();

	void setItens(unordered_map < string, vector<int>> *itens);
	void setClasses(unordered_map < string, vector<int>> *classes);

	void itensInComum(
		unordered_map < int, vector<string>> *tarefaT,
		unordered_map < int, vector<string>> *tarefaT_processamento,
		unordered_map < int, vector<string>> *tarefaT_combinacoes);

	void fazCombinacoes(int key, vector<string> colunas,
		unordered_map < int, vector<string>> *tarefaT_combinacoes);

	void fazIntersecoes(unordered_map < int, vector<string>> *tarefaT_combinacoes);
	void checkCache(string chave, unordered_map<string, int> *classes_aux);
	void checkDados(string item, unordered_map<string, int> *classes_aux);
	void checkClasse(string chave, vector<int> vecA, unordered_map<string, int> *classes_aux);
	void printResult(unordered_map < int, unordered_map<string, int>> classes_aux);
};

#endif