#ifndef OPERACAO_HPP
#define OPERACAO_HPP

// #include "./template/util.hpp"
#include "./combination.hpp"
#include "./intersetion.hpp"
#include "./packages.hpp"

#include <algorithm>

class Kernel: Packages {
private:
	int cont_cache_found;
	int cont_cache_not_found;

	unordered_map < string, vector<int>> *itens;
	unordered_map < string, vector<int>> *classes;
	unordered_map < string, unordered_map<string, int>> cache;

	unordered_map < int, vector<string>> tarefaT_combinacoes;

	Combination combination;
	Intersection intersection;
public:
	/* Funcoes genericas */

	Kernel();
	~Kernel();

	void setItens(unordered_map < string, vector<int>> *itens);
	void setClasses(unordered_map < string, vector<int>> *classes);

	void itensInComum(
		politicas politica,
		unordered_map < int, vector<string>> *tarefaT,
		unordered_map < int, vector<string>> *tarefaT_processamento);

	void fazCombinacoes(int key, vector<string> colunas);
	void printResult(unordered_map < int, unordered_map<string, int>> classes_aux);

	/* Funcoes utilizadas com a politica do tipo FIFO, sem tratamento de tempo,
	funcionando como um processamento em lote */

	void fazIntersecoes();
	void checkCache(string chave, unordered_map<string, int> *classes_aux);
	void checkDados(string item, unordered_map<string, int> *classes_aux);
	void checkClasse(string chave, vector<int> vecA, unordered_map<string, int> *classes_aux);

	/* Funcoes utilizadas com a politica do tipo menor Job first, onde as combinacoes realizadas
	sao reorganizadas em um map para serem processadas primeiro as combinacoes menores */

	void fazIntersecoes2();

};

#endif