#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "./combination.hpp"
#include "./intersetion.hpp"
#include "./packages.hpp"
#include "./cache.hpp"
#include "./model.hpp"

#include <queue>

enum class Politicas {
	FIFO, // round robin, fila
	LJF, // menor job primeiro
	BJF, // maior job primeiro
	PRIORITY, // prioridade
	NONE // nenhum
};

template<Politicas p>
class Kernel: Packages {
private:
	int cont_cache_found;

	unordered_map < string, int> class_model;

	unordered_map < string, Cache>::iterator itr_cache;
	unordered_map < string, vector<int>>::iterator itr_classes;

	Combination combination;
	Intersection intersection;
public:
	Dados *dados;
	unordered_map < string, Cache> cache;

	/* Funcoes genericas */

	Kernel() { this->cont_cache_found = 0; }
	~Kernel() {}

	void setDados(Dados *dados);
	void setClassModel();

	void itensInComum();
	void fazCombinacoes(int key, vector<string> colunas);
	void printResult(unordered_map < int, unordered_map<string, int>> classes_aux);
	void printAnalize();
	void fazIntersecoes();

	/* Funcoes utilizadas com a politica do tipo FIFO,
	funcionando como um processamento em lote */

	void checkCache(string chave, unordered_map<string, int> *classes_aux);
	void checkDados(string item, unordered_map<string, int> *classes_aux);
	void checkClasse(string chave, vector<int> vecA, unordered_map<string, int> *classes_aux);

	/* Funcoes utilizadas com a politica do tipo menor Job first ou maior job primeiro,
	onde as combinacoes realizadas sao reorganizadas em um map para serem processadas
	primeiro as combinacoes menores ou ao contrario*/

	void walkInPackage(queue<pair < string, int>> *new_packages);

	void checkCache(string chave, int linha,
		unordered_map < int, unordered_map<string, int>> *classes_res);

	void pre_checkDados(string chave, int linha,
		unordered_map < int, unordered_map<string, int>> *classes_res);
};

template<Politicas p>
void Kernel<p>::setDados(Dados *dados) {
	this->dados = dados;
	this->setClassModel();
}

// cria um map das classes com valor igual a 0
template<Politicas p>
void Kernel<p>::setClassModel() {
	this->class_model.clear();
	for (itr_classes = this->dados->classes.begin(); itr_classes != this->dados->classes.end(); ++itr_classes) {
		this->class_model.insert({ itr_classes->first, 0 });
	}
}

/**
 * @brief faz o processamento de cada linha do arquivo T e seleciona os itens em comum
 * com o mapeamento do arquivo D
 *
 * @tparam p
 */
template<Politicas p>
void Kernel<p>::itensInComum() {
	unordered_map < int, vector<string>>::iterator itr;
	unordered_map < int, vector<string>>::iterator foundLinha;
	unordered_map < string, vector<int>>::iterator foundItem;

	for (itr = this->dados->tarefaT.begin();itr != this->dados->tarefaT.end();++itr) {
		foundLinha = this->dados->tarefaT_processamento.find(itr->first);

		for (auto item : itr->second) {
			foundItem = this->dados->itens.find(item);
			if (foundItem != this->dados->itens.end()) foundLinha->second.push_back(item);
		}
	}

	for (itr = this->dados->tarefaT_processamento.begin();itr != this->dados->tarefaT_processamento.end();++itr) {
		fazCombinacoes(itr->first, itr->second);
	}
	this->dados->t_intercessao = 0;
}

/**
 * @brief realiza a combinacao dos elementos processados do arquivo T
 *
 * @tparam p
 * @param key chave para utilizar no map de tarefaT_combinacoes
 * @param colunas vetor da tarefaT
 *
 * utilizado pelo metodo itensInComum
 */
template<Politicas p>
void Kernel<p>::fazCombinacoes(int key, vector<string> colunas) {

	int perm[N] = { 0 };

	vector<string> vetor;
	vector<string> res;

	int cont = 1; // quantidade de combinacoes para fazer

	vetor.assign(colunas.begin(), colunas.end());

	for (auto item : colunas)
		this->combination.combinate(vetor, perm, 0, colunas.size(), cont++, key);
	this->combination.atribuiCombinations(&res);
	this->dados->tarefaT_combinacoes.insert({ key, res });
}

// chamado pelo metodo itensInComum
template<>
void Kernel<Politicas::FIFO>::fazIntersecoes() {
	unordered_map < int, unordered_map<string, int>> result;
	unordered_map < int, unordered_map<string, int>>::iterator foundResult;

	unordered_map < int, vector<string>>::iterator itr_combinacoes;
	printf("init: %ld\n", this->cache.size());

	for (itr_combinacoes = this->dados->tarefaT_combinacoes.begin(); itr_combinacoes != this->dados->tarefaT_combinacoes.end(); ++itr_combinacoes) {
		result.insert({ itr_combinacoes->first, this->class_model });
		foundResult = result.find(itr_combinacoes->first);

		for (auto item : itr_combinacoes->second) {
			checkCache(item, &foundResult->second);
		}
		printResult(result);
		result.clear();
	}
	printAnalize();
}

// chamado pelo metodo itensInComum
template<Politicas p>
void Kernel<p>::fazIntersecoes() {
	this->quebrarEmPacotes(this->dados->tarefaT_combinacoes);
	this->cache.clear();
}

// chamado pelo metodo init da classe Thread
template<>
void Kernel<Politicas::LJF>::walkInPackage(queue<pair < string, int>> *new_packages) {

	map < int, set < pair < string, int>>>::iterator it_pkg;

	for (it_pkg = packages.begin(); it_pkg != packages.end(); ++it_pkg) {
		for (auto value : it_pkg->second)  new_packages->push(value);
	}
}

// chamado pelo metodo init da classe Thread
template<>
void Kernel<Politicas::BJF>::walkInPackage(queue<pair < string, int>> *new_packages) {

	map < int, set < pair < string, int>>>::iterator it_pkg;

	for (it_pkg = --packages.end(); it_pkg != --packages.begin();--it_pkg) {
		for (auto value : it_pkg->second)  new_packages->push(value);
	}
}

/**
 * @brief pesquisa uma chave primeiro na cache antes de realizar as operacoes de intercessoes
 *
 * @tparam p
 * @param chave chave que sera pesquisa, que sao as combinacoes do arquivo T
 * @param classes_aux mapa para armazenar o resultado das intercessoes
 *
 * utilizada pela funcao fazIntercessoes na politica FIFO
 */
template<Politicas p>
void Kernel<p>::checkCache(string chave, unordered_map<string, int> *classes_aux) {

	unordered_map < string, int>::iterator itr_aux;
	unordered_map < string, int>::iterator itr;

	this->itr_cache = cache.find(chave);

	if (itr_cache != cache.end()) {
		for (itr = itr_cache->second.class_model.begin();itr != itr_cache->second.class_model.end();++itr) {
			itr_aux = classes_aux->find(itr->first);

			if (itr_aux != classes_aux->end()) {
				itr_aux->second = itr_aux->second + itr->second;
			}
		}
		this->cont_cache_found++;
	} else {
		Cache cache_aux;
		cache_aux.class_model.clear();
		cache_aux.class_model = this->class_model;

		this->cache.insert({ chave, cache_aux });
		checkDados(chave, classes_aux);
	}
}

/**
 * @brief pesquisa uma chave primeiro na cache antes de realizar as operacoes de intercessoes
 *
 * @tparam p
 * @param chave chave que sera pesquisa, que sao as combinacoes do arquivo T
 * @param linha linha do arquivo T
 * @param classes_res
 *
 * utilizada pela funcao processaValue da classe Thread
 */
template<Politicas p>
void Kernel<p>::checkCache(string chave, int linha,
	unordered_map < int, unordered_map<string, int>> *classes_res) {

	unordered_map < int, unordered_map<string, int>>::iterator found_classes_res;
	unordered_map < string, int>::iterator itr;
	unordered_map < string, int>::iterator itr_aux;

	this->itr_cache = this->cache.find(chave);

	if (itr_cache != this->cache.end()) {
		found_classes_res = classes_res->find(linha);
		this->cont_cache_found++;

		if (found_classes_res == classes_res->end()) {
			classes_res->insert({ linha, this->class_model });
			found_classes_res = classes_res->find(linha);
		}

		for (itr = itr_cache->second.class_model.begin(); itr != itr_cache->second.class_model.end(); ++itr) {
			itr_aux = found_classes_res->second.find(itr->first);

			if (itr_aux != found_classes_res->second.end())
				itr_aux->second = itr_aux->second + itr->second;
		}
	} else {
		pre_checkDados(chave, linha, classes_res);
	}
}

/**
 * @brief inicializa o valor da classe res para verificar os dados com a classe principal
 *
 * @tparam p
 * @param chave chave que sera pesquisada, que sao as combinacoes do arquivo T
 * @param linha numero da linha do processo
 * @param classes_res mapa para armazenar o resultado das intercessoes de cada linha(processo)
 *
 * utilizada pela funcao checkCache na politica LJF e BJF
 */
template<Politicas p>
void Kernel<p>::pre_checkDados(string chave, int linha,
	unordered_map < int, unordered_map<string, int>> *classes_res) {

	unordered_map < int, unordered_map<string, int>>::iterator found_classes_res;
	Cache cache_aux;

	cache_aux.class_model.clear();
	cache_aux.class_model = this->class_model;

	this->cache.insert({ chave, cache_aux });

	found_classes_res = classes_res->find(linha);

	if (found_classes_res == classes_res->end()) {
		classes_res->insert({ linha, this->class_model });
		found_classes_res = classes_res->find(linha);
	}
	checkDados(chave, &found_classes_res->second);
}

/**
 * @brief caso a chave pesquisada em checkCache nao existir, esta funcao eh chamada
 * sendo executada a verificacao das combinacoes geradas
 *
 * @tparam p
 * @param chave chave que sera pesquisa, que sao as combinacoes do arquivo T
 * @param classes_aux mapa para armazenar o resultado das intercessoes
 *
 * utilizada pelas funcoes checkCache e pre_checkDados
 */
template<Politicas p>
void Kernel<p>::checkDados(string chave, unordered_map<string, int> *classes_aux) {
	steady_clock::time_point init = steady_clock::now();

	vector<string>::iterator it_vec;

	Tokenizar<string> u;
	vector<string> dados;

	vector<int> v1, v2, aux, res;

	dados.clear();
	u.tokenizar(chave, &dados);

	if (dados.size() > 1) {
		it_vec = dados.begin();
		v1.clear();
		v1 = this->dados->itens.find(*it_vec)->second;

		++it_vec;
		res.clear();
		res.push_back(0); // apenas para inicializar

		for (; it_vec != dados.end() && res.size() > 0; ++it_vec) {
			v2 = this->dados->itens.find(*it_vec)->second;
			this->intersection.intersecaoVetores(v1, v2, &res);

			v1.clear();
			v2.clear();
			res.clear();

			v1.assign(res.begin(), res.end());
		}
		aux.clear();
		aux.assign(res.begin(), res.end());

		if (aux.size() > 0) {
			checkClasse(chave, aux, classes_aux);
		}
	} else {
		v1 = this->dados->itens.find(chave)->second;
		checkClasse(chave, v1, classes_aux);
	}
	steady_clock::time_point end = steady_clock::now();
	this->dados->t_intercessao +=
		duration_cast<duration<double>>(end - init).count();
}

/**
 * @brief realiza a intercao do vetor vecA com cada vetor de classe
 * e armazena o resultado no map classes_aux
 *
 * @tparam p
 * @param chave chave que sera pesquisa, que sao as combinacoes do arquivo T
 * @param vecA
 * @param classes_aux
 *
 * utilizada pelo metodo checkDados
 */
template<Politicas p>
void Kernel<p>::checkClasse(string chave, vector<int> vecA, unordered_map<string, int> *classes_aux) {

	unordered_map < string, vector<int>>::iterator itr;
	unordered_map<string, int>::iterator itr_aux;

	vector<int> res;
	string classe;

	Cache cache_aux;
	cache_aux.setZero(false);

	for (itr = this->dados->classes.begin(); itr != this->dados->classes.end();++itr) {
		this->intersection.intersecaoVetores(vecA, itr->second, &res);
		itr_aux = classes_aux->find(itr->first);

		if (itr_aux != classes_aux->end()) {
			itr_aux->second = itr_aux->second + res.size();
			cache_aux.class_model.insert({ itr->first, res.size() });
		}
	}
	this->itr_cache = this->cache.find(chave);

	if (itr_cache != this->cache.end()) {
		itr_cache->second = cache_aux;
	} else {
		this->cache.insert({ chave, cache_aux });
	}
}

/**
 * @brief imprime a classe de maior ocorrencia do processo passado,
 * em caso de empate o primeiro a ser econtrado sera o resultado final

 * @tparam p
 * @param classes_aux
 *
 * utilizada pelo metodo fazIntersecoes
 */
template<Politicas p>
void Kernel<p>::printResult(unordered_map < int, unordered_map<string, int>> classes_aux) {

	unordered_map < int, unordered_map<string, int>>::iterator itr_aux;
	unordered_map < string, int>::iterator itr_aux_values;

	int maior = 0;
	string classe;

	for (itr_aux = classes_aux.begin();itr_aux != classes_aux.end();++itr_aux) {
		printf("[ %2d ] ", itr_aux->first);

		maior = 0;
		for (itr_aux_values = itr_aux->second.begin();
			itr_aux_values != itr_aux->second.end();
			++itr_aux_values) {

			if (itr_aux_values->second > maior) {
				classe.assign(itr_aux_values->first);
				maior = itr_aux_values->second;

			}
		}
		printf("----> ");
		printf("%s\n", classe.c_str());
	}
}

template<Politicas p>
void Kernel<p>::printAnalize() {
	int quant = 0;

	for (this->itr_cache = this->cache.begin(); itr_cache != this->cache.end(); ++itr_cache)
		if (!itr_cache->second.getZero()) quant++;

	printf("\nCache com valor {0}: %ld\n", this->cache.size() - quant);
	printf("Cache com valor != {0}: %d\n", quant);
	printf("Computacoes realizadas: %ld\n", this->cache.size());
	printf("Combinacoes encontrada na cache: %d\n", this->cont_cache_found);
	printf("\nTotal de iteracoes: %ld + %d :: %ld\n", this->cache.size(), this->cont_cache_found, this->cont_cache_found + this->cache.size());
}

#endif