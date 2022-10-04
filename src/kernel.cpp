#include "./include/kernel.hpp"

Kernel::Kernel() {}
Kernel::~Kernel() {}

void Kernel::setItens(unordered_map < string, vector<int>> *itens) {
	this->itens = itens;
}

void Kernel::setClasses(unordered_map < string, vector<int>> *classes) {
	this->classes = classes;
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
void Kernel::itensInComum(
	unordered_map < int, vector<string>> *tarefaT,
	unordered_map < int, vector<string>> *tarefaT_processamento,
	unordered_map < int, vector<string>> *tarefaT_combinacoes
) {

	unordered_map < int, vector<string>>::iterator itr;
	unordered_map < int, vector<string>>::iterator foundLinha;
	unordered_map < string, vector<int>>::iterator foundItem;

	for (itr = tarefaT->begin();itr != tarefaT->end();++itr) {
		foundLinha = tarefaT_processamento->find(itr->first);

		for (auto item : itr->second) {
			foundItem = itens->find(item);
			if (foundItem != itens->end()) foundLinha->second.push_back(item);
		}
	}

	for (itr = tarefaT_processamento->begin();itr != tarefaT_processamento->end();++itr)
		fazCombinacoes(itr->first, itr->second, tarefaT_combinacoes);
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
void Kernel::fazCombinacoes(int key, vector<string> colunas,
	unordered_map < int, vector<string>> *tarefaT_combinacoes) {

	Combination c;

	int perm[5] = { 0 };

	vector<string> vetor;
	vector<string> res;

	int cont = 1;

	vetor.assign(colunas.begin(), colunas.end());

	for (auto item : colunas)
		c.combinate(vetor, perm, 0, colunas.size(), cont++);
	c.atribuiCombinations(&res);
	tarefaT_combinacoes->insert({ key, res });
}

/**
 * @brief realiza a intercessao das combinacoes realizadas
 *
 * Se uma tarefa T possui todas a N colunas existentes, sera feita a intercessao
 * inicialmente de cada elemento, depois de dois em dois elementos, tres em tres
 * ate N, para cada intercessao eh impresso o resultado a qual classe pertence a
 * tarefa T
 *
 * @param tarefaT_combinacoes
 *
 * chamado no main
 */
void Kernel::fazIntersecoes(unordered_map < int, vector<string>> *tarefaT_combinacoes) {

	Util <string> u;

	vector<int> v1;
	vector<int> v2;
	vector<int> aux;

	vector<int> res;
	vector<string> dados;
	vector<string>::iterator it_vec;

	unordered_map < int, unordered_map<string, int>> classes_aux;
	unordered_map < int, unordered_map<string, int>>::iterator foundClasses_aux;

	unordered_map < int, vector<int>>::iterator found_cache;
	unordered_map < int, vector<string>>::iterator itr_combinacoes;

	unordered_map < string, int> value_class_aux;
	unordered_map < string, vector<int>>::iterator itr_classes;

	// cria um map das classes com valor igual a 0
	for (itr_classes = classes->begin(); itr_classes != classes->end(); ++itr_classes)
		value_class_aux.insert({ itr_classes->first, 0 });

	for (itr_combinacoes = tarefaT_combinacoes->begin(); itr_combinacoes != tarefaT_combinacoes->end(); ++itr_combinacoes) {
		classes_aux.insert({ itr_combinacoes->first, value_class_aux });
		foundClasses_aux = classes_aux.find(itr_combinacoes->first);

		for (auto item : itr_combinacoes->second) {
			dados.clear();
			u.tokenizar(item, &dados);

			if (dados.size() > 1) {
				it_vec = dados.begin();
				v1.clear();
				v1 = itens->find(*it_vec)->second;

				++it_vec;
				res.clear();
				res.push_back(0); // apenas para inicializar

				for (; it_vec != dados.end() && res.size() > 0; ++it_vec) {
					v2 = itens->find(*it_vec)->second;
					intersecaoVetores(v1, v2, &res);

					v1.clear();
					v2.clear();
					res.clear();

					v1.assign(res.begin(), res.end());
				}
				aux.clear();
				aux.assign(res.begin(), res.end());

				if (aux.size() > 0) {
					checkClasse(aux, &foundClasses_aux->second);
				}
			} else {
				v1 = itens->find(item)->second;
				checkClasse(v1, &foundClasses_aux->second);
			}
		}
	}
	printResult(classes_aux);
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
void Kernel::checkClasse(vector<int> vecA, unordered_map<string, int> *classes_aux) {

	unordered_map < string, vector<int>>::iterator itr;
	unordered_map<string, int>::iterator itr_aux;

	vector<int> res;
	string classe;

	for (itr = classes->begin();itr != classes->end();++itr) {
		intersecaoVetores(vecA, itr->second, &res);
		itr_aux = classes_aux->find(itr->first);

		if (itr_aux != classes_aux->end())
			itr_aux->second = itr_aux->second + res.size();
	}
}

/**
 * @brief realiza a intersecao entre dois vetores e salva o resultado em res
 *
 * @param v1
 * @param v2
 * @param res
 *
 * utilizada pelo metodo fazIntersecoes e checkClasse
 */
void Kernel::intersecaoVetores(vector<int> v1, vector<int>v2, vector<int> *res) {
	vector<int>::iterator itRes;

	res->clear();
	res->resize(v1.size());
	sort(res->begin(), res->end());

	itRes = set_intersection(
		v1.begin(), v1.end(),
		v2.begin(), v2.end(),
		res->begin());
	res->resize(itRes - res->begin());
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