#ifndef OPERACAO_HPP
#define OPERACAO_HPP

#include "./combination.hpp"
#include "./intersetion.hpp"
#include "./packages.hpp"
#include "./cache.hpp"
#include "./model.hpp"

#include <algorithm>

class Kernel: Packages {
private:
	int cont_cache_found;
	int cont_cache_not_found;

	unordered_map < string, int> class_model;
	unordered_map < string, Cache> cache;

	unordered_map < string, Cache>::iterator itr_cache;
	unordered_map < string, vector<int>>::iterator itr_classes;

	Dados dados;
	Combination combination;
	Intersection intersection;
public:
	/* Funcoes genericas */

	Kernel();
	~Kernel();

	void setDados(Dados dados);
	void setClassModel();

	void itensInComum(politicas politica);
	void fazCombinacoes(int key, vector<string> colunas);
	void printResult(unordered_map < int, unordered_map<string, int>> classes_aux);
	void printAnalize();

	/* Funcoes utilizadas com a politica do tipo FIFO, sem tratamento de tempo,
	funcionando como um processamento em lote */

	void fazIntersecoes();
	void checkCache(string chave, unordered_map<string, int> *classes_aux);
	void checkDados(string item, unordered_map<string, int> *classes_aux);
	void checkClasse(string chave, vector<int> vecA, unordered_map<string, int> *classes_aux);

	/* Funcoes utilizadas com a politica do tipo menor Job first, onde as combinacoes realizadas
	sao reorganizadas em um map para serem processadas primeiro as combinacoes menores */

	void fazIntersecoes2();
	void checkCache2(string chave, int linha, unordered_map < int, unordered_map<string, int>> *classes_res);
	void checkDados2(string chave, int linha, unordered_map < int, unordered_map<string, int>> *classes_res);

	/* Funcoes utilizadas com a politica do tipo maior Job first, onde as combinacoes realizadas
	sao reorganizadas em um map para serem processadas primeiro as combinacoes maiores, o que é possivel
	utilizar as funcoes do menor Job first, pois basta ler ao contrario */

	void fazIntersecoes3();
};

#endif