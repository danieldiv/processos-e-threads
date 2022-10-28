#include "./include/kernel.hpp"

Dados::Dados() {}
Dados::~Dados() {}

Kernel::Kernel() { this->cont_cache_found = 0; }
Kernel::~Kernel() {}

void Kernel::setDados(Dados dados) {
	this->dados = dados;
	this->setClassModel();
}

// cria um map das classes com valor igual a 0
void Kernel::setClassModel() {
	this->class_model.clear();
	for (itr_classes = this->dados.classes.begin(); itr_classes != this->dados.classes.end(); ++itr_classes) {
		this->class_model.insert({ itr_classes->first, 0 });
	}
}

/**
 * @brief faz o processamento de cada linha do arquivo T e seleciona os itens em comum com o mapeamento do arquivo D
 *
 * @param itens mapeamento do arquivo D
 * @param tarefaT mapeamento do arquivo T
 * @param tarefaT_processamento mapa para armazenar o processamento
 * @param tarefaT_combinacoes mapa para armazenar as permutacoes do itens processados em tarefaT_processamento
 *
 * chamado no main
 */
void Kernel::itensInComum(politicas politica) {
	unordered_map < int, vector<string>>::iterator itr;
	unordered_map < int, vector<string>>::iterator foundLinha;
	unordered_map < string, vector<int>>::iterator foundItem;

	for (itr = this->dados.tarefaT.begin();itr != this->dados.tarefaT.end();++itr) {
		foundLinha = this->dados.tarefaT_processamento.find(itr->first);

		for (auto item : itr->second) {
			foundItem = this->dados.itens.find(item);
			if (foundItem != this->dados.itens.end()) foundLinha->second.push_back(item);
		}
	}

	for (itr = this->dados.tarefaT_processamento.begin();itr != this->dados.tarefaT_processamento.end();++itr)
		fazCombinacoes(itr->first, itr->second);

	if (politica == fifo) {
		this->fazIntersecoes();
	} else if (politica == lowest_job_first) {
		this->quebrarEmPacotes(this->dados.tarefaT_combinacoes);
		this->fazIntersecoes2();
	} else if (politica == biggest_job_first) {
		this->quebrarEmPacotes(this->dados.tarefaT_combinacoes);
		this->fazIntersecoes3();
	}
}

/**
 * @brief realiza a combinacao dos elementos processados do arquivo T
 *
 * @param key chave para utilizar no map de tarefaT_combinacoes
 * @param colunas vetor da tarefaT
 * @param tarefaT_combinacoes
 *
 * utilizada pelo metodo itenInComum
 */
void Kernel::fazCombinacoes(int key, vector<string> colunas) {

	int perm[N] = { 0 };

	vector<string> vetor;
	vector<string> res;

	int cont = 1; // quantidade de combinacoes para fazer

	vetor.assign(colunas.begin(), colunas.end());

	for (auto item : colunas)
		this->combination.combinate(vetor, perm, 0, colunas.size(), cont++, key);
	this->combination.atribuiCombinations(&res);
	this->dados.tarefaT_combinacoes.insert({ key, res });
}

/**
 * @brief realiza a intercessao das combinacoes realizadas
 *
 * Se uma tarefa T possui todas a N colunas existentes, sera feita a intercessao
 * inicialmente de cada elemento, depois de dois em dois elementos, tres em tres
 * ate N, para cada intercessao eh impresso o resultado a qual classe pertence a
 * tarefa T
 *
 * chamado no main quando a politica fifo for escolhida
 */
void Kernel::fazIntersecoes() {
	unordered_map < int, unordered_map<string, int>> classes_aux;
	unordered_map < int, unordered_map<string, int>>::iterator foundClasses_aux;

	unordered_map < int, vector<int>>::iterator found_cache;
	unordered_map < int, vector<string>>::iterator itr_combinacoes;

	for (itr_combinacoes = this->dados.tarefaT_combinacoes.begin(); itr_combinacoes != this->dados.tarefaT_combinacoes.end(); ++itr_combinacoes) {
		classes_aux.insert({ itr_combinacoes->first, this->class_model });
		foundClasses_aux = classes_aux.find(itr_combinacoes->first);

		for (auto item : itr_combinacoes->second) {
			checkCache(item, &foundClasses_aux->second);
		}
		printResult(classes_aux);
		classes_aux.clear();
	}
	printAnalize();
}

/**
 * @brief eh chamado quando a politica lowest_job_first for escolhida no main
 *
 * nesta funcao o map dos resultados inicialmente estao todos separados, logo
 * nao eh possivel imprimir a possivel classe da tarefa T em cada for pois
 * eh necessario percorrer todos os pacotes
 */
void Kernel::fazIntersecoes2() {
	this->cache.clear();

	map < int, set < pair < string, int>>>::iterator it_pkg;
	unordered_map < int, unordered_map<string, int>> classes_res;

	for (it_pkg = packages.begin(); it_pkg != packages.end(); ++it_pkg) {
		for (auto value : it_pkg->second) {
			checkCache2(value.first, value.second, &classes_res);
		}
	}
	printResult(classes_res);
	printAnalize();
}

void Kernel::fazIntersecoes3() {
	this->cache.clear();

	map < int, set < pair < string, int>>> pkg_aux;

	map < int, set < pair < string, int>>>::iterator it_pkg;
	unordered_map < int, unordered_map<string, int>> classes_res;

	it_pkg = packages.end();
	it_pkg--;

	for (; it_pkg != --packages.begin();--it_pkg) {
		for (auto value : it_pkg->second) {
			// cout << value.first << endl;
			checkCache2(value.first, value.second, &classes_res);
		}

	}
	printResult(classes_res);
	printAnalize();
}

/**
 * @brief pesquisa uma chave primeiro na cache antes de realizar as operacoes de intercessoes
 *
 * @param chave chave que sera pesquisa, que sao as combinacoes do arquivo T
 * @param dados vetor que contem as chaves tokenizadas
 * @param classes_aux mapa para armazenar o resultado das intercessoes
 *
 * utilizada pela funcao fazIntercessoes
 */
void Kernel::checkCache(string chave, unordered_map<string, int> *classes_aux) {

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
 * @param chave chave que sera pesquisa, que sao as combinacoes do arquivo T
 *
 * utilizada pela funcao fazIntercessoes2
 */
void Kernel::checkCache2(string chave, int linha,
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
		checkDados2(chave, linha, classes_res);
	}
}

/**
 * @brief o mesmo que o checkDados
 *
 * @param chave chave que sera pesquisa, que sao as combinacoes do arquivo T
 * @param linha numero da linha do processo
 * @param classes_res mapa para armazenar o resultado das intercessoes
 *
 * utilizada pela funcao checkCache2
 */
void Kernel::checkDados2(string chave, int linha,
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
 * caso uma conbinacao tenha um tamanho maior do que 1, primeiro deve ser feita
 * a intercessao de todos os vetores da combinacao em questao para depois verificar com a classe
 *
 * caso o tamanho seja apenas 1, o check da classe eh chamado
 *
 * @param dados vetor que contem as chaves tokenizadas
 * @param chave chave que sera pesquisa, que sao as combinacoes do arquivo T
 * @param classes_aux mapa para armazenar o resultado das intercessoes
 *
 * utilizada pela funcao checkCache
 */
void Kernel::checkDados(string chave, unordered_map<string, int> *classes_aux) {

	vector<string>::iterator it_vec;

	vector<int> v1;
	vector<int> v2;
	vector<int> aux;
	vector<int> res;

	Util <string> u;
	vector<string> dados;

	dados.clear();
	u.tokenizar(chave, &dados);

	if (dados.size() > 1) {
		it_vec = dados.begin();
		v1.clear();
		v1 = this->dados.itens.find(*it_vec)->second;

		++it_vec;
		res.clear();
		res.push_back(0); // apenas para inicializar

		for (; it_vec != dados.end() && res.size() > 0; ++it_vec) {
			v2 = this->dados.itens.find(*it_vec)->second;
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
		v1 = this->dados.itens.find(chave)->second;
		checkClasse(chave, v1, classes_aux);
	}
}

/**
 * @brief realiza a intercao do vetor vecA com cada vetor de classe
 * e armazena o resultado no map classes_aux
 *
 * @param vecA
 * @param classes_aux
 *
 * utilizada pelo metodo fazIntersecoes
 */
void Kernel::checkClasse(string chave, vector<int> vecA, unordered_map<string, int> *classes_aux) {

	unordered_map < string, vector<int>>::iterator itr;
	unordered_map<string, int>::iterator itr_aux;

	vector<int> res;
	string classe;

	Cache cache_aux;
	cache_aux.setZero(false);

	for (itr = this->dados.classes.begin(); itr != this->dados.classes.end();++itr) {
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
 * @brief imprime a classe de maior ocorrencia do processo passado
 * em caso de empate, o primeiro a ser econtrado sera o resultado final
 *
 * @param classes_aux
 *
 * utilizada pelo metodo fazIntersecoes
 */
void Kernel::printResult(unordered_map < int, unordered_map<string, int>> classes_aux) {

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
		cout << "----> " << ((maior > 0) ? classe : "NULL") << endl;
	}
}

/**
 * @brief imprime as analizes de chamadas realizadas ou nao na chache
 *
 * chamado pelo metodo fazIntercessao e fazIntercessao2
 */
void Kernel::printAnalize() {
	int quant = 0;

	for (this->itr_cache = this->cache.begin(); itr_cache != this->cache.end(); ++itr_cache)
		if (!itr_cache->second.getZero()) quant++;

	cout << endl << "Cache com valor {0}: " << this->cache.size() - quant << endl;
	cout << "Cache com valor != {0}: " << quant << endl;
	cout << "Computacoes realizadas: " << this->cache.size() << endl;
	cout << "Combinacoes encontrada na cache: " << this->cont_cache_found << endl;
	cout << endl << "Total de iteracoes: "
		<< this->cache.size() << " + "
		<< this->cont_cache_found << " = "
		<< this->cont_cache_found + this->cache.size() << endl;
}