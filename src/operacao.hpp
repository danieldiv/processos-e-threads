#ifndef OPERACAO_HPP
#define OPERACAO_HPP

#include "util.hpp"

#include <algorithm>

class Operacao {
public:
	Operacao();
	~Operacao();

	void itensInComum(
		unordered_map < string, set<int>> *itens,
		unordered_map < int, set<string>> *tarefaT,
		unordered_map < int, set<string>> *classesT);

	void fazIntersecoes(
		unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *classesT);

	void checkClasse(set<int> vecA,
		unordered_map < string, set<int>> *classes,
		unordered_map<string, int> *classes_aux);

	void faz1(unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *classesT,
		unordered_map<int, unordered_map<string, int>> *classes_aux);

	void faz2(unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *classesT,
		unordered_map<int, unordered_map<string, int>> *classes_aux);

	void faz3(unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *classesT,
		unordered_map<int, unordered_map<string, int>> *classes_aux);

	void intersecaoVetores(set<int> v1, set<int>v2, vector<int> *res);
};

Operacao::Operacao() {}
Operacao::~Operacao() {}

void Operacao::itensInComum(
	unordered_map < string, set<int>> *itens,
	unordered_map < int, set<string>> *tarefaT,
	unordered_map < int, set<string>> *classesT) {

	unordered_map < int, set<string>>::iterator itr;
	unordered_map < int, set<string>>::iterator foundLinha;
	unordered_map < string, set<int>>::iterator foundItem;

	for (itr = tarefaT->begin();itr != tarefaT->end();++itr) {
		foundLinha = classesT->find(itr->first);

		for (auto item : itr->second) {
			foundItem = itens->find(item);
			if (foundItem != itens->end())foundLinha->second.insert(item);
		}
	}
}

void Operacao::fazIntersecoes(
	unordered_map < string, set<int>> *itens,
	unordered_map < string, set<int>> *classes,
	unordered_map < int, set<string>> *classesT) {

	unordered_map<int, unordered_map<string, int>> classes_aux;

	faz1(itens, classes, classesT, &classes_aux);
	faz2(itens, classes, classesT, &classes_aux);
	faz3(itens, classes, classesT, &classes_aux);

	unordered_map<int, unordered_map<string, int>>::iterator itr_aux;
	unordered_map<string, int>::iterator itr_aux_values;

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

void Operacao::faz1(unordered_map < string, set<int>> *itens,
	unordered_map < string, set<int>> *classes,
	unordered_map < int, set<string>> *classesT,
	unordered_map<int, unordered_map<string, int>> *classes_aux) {

	unordered_map<int, unordered_map<string, int>>::iterator foundClasses_aux;
	unordered_map < string, set<int>>::iterator itrClasses;
	unordered_map < string, set<int>>::iterator found;
	unordered_map < int, set<string>>::iterator itr;

	unordered_map<string, int> value_class_aux;
	int linha = 1;

	set<int> v1;

	for (itrClasses = classes->begin();itrClasses != classes->end();++itrClasses)
		value_class_aux.insert({ itrClasses->first, 0 });

	for (itr = classesT->begin();itr != classesT->end();++itr) {
		classes_aux->insert({ itr->first, value_class_aux });
		foundClasses_aux = classes_aux->find(itr->first);

		for (auto key : itr->second) {
			found = itens->find(key);
			v1 = found->second;
			checkClasse(v1, classes, &foundClasses_aux->second);
		}
	}
}

void Operacao::faz2(unordered_map < string, set<int>> *itens,
	unordered_map < string, set<int>> *classes,
	unordered_map < int, set<string>> *classesT,
	unordered_map<int, unordered_map<string, int>> *classes_aux) {

	unordered_map<int, unordered_map<string, int>>::iterator foundClasses_aux;
	unordered_map < string, set<int>>::iterator found;
	unordered_map < string, set<int>>::iterator found2;
	unordered_map < int, set<string>>::iterator itr;

	unordered_map<string, int> value_class_aux;
	int linha = 1;

	set<int> v1;
	set<int> v2;

	vector<int>res;
	set<int>aux;

	for (itr = classesT->begin();itr != classesT->end();++itr) {
		foundClasses_aux = classes_aux->find(linha++);

		for (auto key : itr->second) {
			found = itens->find(key);

			v1.clear();
			v1 = found->second;

			for (auto key2 : itr->second) {
				if (key.compare(key2) != 0) {
					found2 = itens->find(key2);

					v2.clear();
					v2 = found2->second;
					res.clear();
					intersecaoVetores(v1, v2, &res);

					aux.clear();
					aux.insert(res.begin(), res.end());

					if (aux.size() > 0)
						checkClasse(aux, classes, &foundClasses_aux->second);
				}
			}
		}
	}
}

void Operacao::faz3(unordered_map < string, set<int>> *itens,
	unordered_map < string, set<int>> *classes,
	unordered_map < int, set<string>> *classesT,
	unordered_map<int, unordered_map<string, int>> *classes_aux) {

	unordered_map<int, unordered_map<string, int>>::iterator foundClasses_aux;
	unordered_map < string, set<int>>::iterator found;
	unordered_map < string, set<int>>::iterator found2;
	unordered_map < string, set<int>>::iterator found3;
	unordered_map < int, set<string>>::iterator itr;

	unordered_map<string, int> value_class_aux;
	int linha = 1;

	set<int> v1;
	set<int> v2;
	set<int> v3;

	vector<int>res;
	set<int>aux;

	for (itr = classesT->begin();itr != classesT->end();++itr) {
		foundClasses_aux = classes_aux->find(linha++);

		for (auto key : itr->second) {
			found = itens->find(key);

			v1.clear();
			v1 = found->second;

			for (auto key2 : itr->second) {
				if (key.compare(key2) != 0) {

					found2 = itens->find(key2);

					v2.clear();
					v2 = found2->second;
					res.clear();
					intersecaoVetores(v1, v2, &res);

					if (res.size() > 0) {
						aux.clear();
						aux.insert(res.begin(), res.end());

						for (auto key3 : itr->second) {
							if (key.compare(key3) != 0 && key2.compare(key3) != 0) {
								found3 = itens->find(key3);

								v3.clear();
								v3 = found3->second;
								res.clear();
								intersecaoVetores(aux, v3, &res);

								aux.clear();
								aux.insert(res.begin(), res.end());

								if (aux.size() > 0)
									checkClasse(aux, classes, &foundClasses_aux->second);
							}
						}
					}
				}
			}
		}
	}
}

void Operacao::checkClasse(set<int> vecA,
	unordered_map < string, set<int>> *classes,
	unordered_map<string, int> *classes_aux) {
	unordered_map < string, set<int>>::iterator itr;

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

void Operacao::intersecaoVetores(set<int> v1, set<int>v2, vector<int> *res) {
	vector<int>::iterator itRes;

	res->resize(v1.size());
	sort(res->begin(), res->end());

	itRes = set_intersection(
		v1.begin(), v1.end(),
		v2.begin(), v2.end(),
		res->begin());
	res->resize(itRes - res->begin());
}

#endif