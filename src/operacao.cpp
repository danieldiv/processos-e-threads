#include "./class/operacao.hpp"

Operacao::Operacao() {}
Operacao::~Operacao() {}

void Operacao::setItens(unordered_map < string, set<int>> itens) {
	this->itens.insert(itens.begin(), itens.end());
}

void Operacao::setClasses(unordered_map < string, set<int>> classes) {
	this->classes.insert(classes.begin(), classes.end());
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
void Operacao::itensInComum(
	unordered_map < int, set<string>> *tarefaT,
	unordered_map < int, set<string>> *tarefaT_processamento,
	unordered_map < int, vector<string>> *tarefaT_combinacoes
) {

	unordered_map < int, set<string>>::iterator itr;
	unordered_map < int, set<string>>::iterator foundLinha;
	unordered_map < string, set<int>>::iterator foundItem;

	for (itr = tarefaT->begin();itr != tarefaT->end();++itr) {
		foundLinha = tarefaT_processamento->find(itr->first);

		for (auto item : itr->second) {
			foundItem = itens.find(item);
			if (foundItem != itens.end()) foundLinha->second.insert(item);
		}
	}

	for (itr = tarefaT_processamento->begin();itr != tarefaT_processamento->end();++itr)
		fazCombinacoes(itr->first, itr->second, tarefaT_combinacoes);
}

void Operacao::fazCombinacoes(int key, set<string> colunas,
	unordered_map < int, vector<string>> *tarefaT_combinacoes) {

	Combination c;
	vector<bool> perm(N);
	vector<string> vetor;
	vector<string> res;

	int cont = 1;

	vetor.assign(colunas.begin(), colunas.end());

	for (auto item : colunas)
		c.combinate(&vetor, &perm, 0, colunas.size(), cont++);
	c.atribuiCombinations(&res);
	tarefaT_combinacoes->insert({ key, res });
}

void Operacao::fazIntersecoes(unordered_map < int, vector<string>> *tarefaT_combinacoes) {

	Util <string> u;

	set<int> v1;
	set<int> v2;
	set<int> aux;

	vector<int> res;
	vector<string> dados;
	vector<string>::iterator it_vec;

	unordered_map < int, unordered_map<string, int>>::iterator foundClasses_aux;
	unordered_map < int, unordered_map<string, int>> classes_aux;
	unordered_map < int, vector<string>>::iterator itr;

	unordered_map < string, set<int>>::iterator itrClasses;
	unordered_map < string, int> value_class_aux;

	// cria um map das classes com valor igual a 0
	for (itrClasses = classes.begin(); itrClasses != classes.end(); ++itrClasses)
		value_class_aux.insert({ itrClasses->first, 0 });

	for (itr = tarefaT_combinacoes->begin(); itr != tarefaT_combinacoes->end(); ++itr) {
		classes_aux.insert({ itr->first, value_class_aux });
		foundClasses_aux = classes_aux.find(itr->first);

		for (auto item : itr->second) {
			dados.clear();
			u.tokenizar(item, &dados);

			if (dados.size() > 1) {
				it_vec = dados.begin();
				v1.clear();
				v1 = itens.find(*it_vec)->second;

				++it_vec;
				res.clear();
				res.push_back(0); // apenas para inicializar

				for (; it_vec != dados.end() && res.size() > 0; ++it_vec) {
					v2 = itens.find(*it_vec)->second;
					intersecaoVetores(v1, v2, &res);

					v1.clear();
					v2.clear();
					res.clear();

					v1.insert(res.begin(), res.end());
				}
				aux.clear();
				aux.insert(res.begin(), res.end());

				if (aux.size() > 0) {
					checkClasse(aux, &foundClasses_aux->second);
				}
			} else {
				v1 = itens.find(item)->second;
				checkClasse(v1, &foundClasses_aux->second);
			}
		}
	}
	printResult(classes_aux);
}

void Operacao::checkClasse(set<int> vecA, unordered_map<string, int> *classes_aux) {

	unordered_map < string, set<int>>::iterator itr;
	unordered_map<string, int>::iterator itr_aux;

	vector<int> res;
	string classe;

	for (itr = classes.begin();itr != classes.end();++itr) {
		intersecaoVetores(vecA, itr->second, &res);
		itr_aux = classes_aux->find(itr->first);

		if (itr_aux != classes_aux->end())
			itr_aux->second = itr_aux->second + res.size();
	}
}

void Operacao::intersecaoVetores(set<int> v1, set<int>v2, vector<int> *res) {
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

void Operacao::printResult(unordered_map < int, unordered_map<string, int>> classes_aux) {

	unordered_map < int, unordered_map<string, int>>::iterator itr_aux;
	unordered_map < string, int>::iterator itr_aux_values;

	int maior = 0;
	string classe;

	for (itr_aux = classes_aux.begin();itr_aux != classes_aux.end();++itr_aux) {
		printf("[ %2d ]\n", itr_aux->first);

		maior = 0;
		for (itr_aux_values = itr_aux->second.begin();
			itr_aux_values != itr_aux->second.end();
			++itr_aux_values) {

			cout << itr_aux_values->second << " -> " << itr_aux_values->first << endl;

			if (itr_aux_values->second > maior) {
				classe.assign(itr_aux_values->first);
				maior = itr_aux_values->second;
			}
		}
		cout << "----> " << ((maior > 0) ? classe : "NULL") << endl;
		cout << "\n===================================\n\n";
	}
}