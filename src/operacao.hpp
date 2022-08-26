#ifndef OPERACAO_HPP
#define OPERACAO_HPP

#include "util.hpp"
#include <algorithm>

#define N 4

class Operacao {
public:
	Operacao();
	~Operacao();

	void itensInComum(
		unordered_map < string, set<int>> *itens,
		unordered_map < int, set<string>> *tarefaT,
		unordered_map < int, set<string>> *classesT);

	void fazIntersecao(
		unordered_map < string, set<int>> *itens,
		unordered_map < string, set<int>> *classes,
		unordered_map < int, set<string>> *classesT);

	void checkClasse(set<int> vecA,
		unordered_map < string, set<int>> *classes);

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

void Operacao::fazIntersecao(
	unordered_map < string, set<int>> *itens,
	unordered_map < string, set<int>> *classes,
	unordered_map < int, set<string>> *classesT) {

	unordered_map < string, set<int>>::iterator found;
	unordered_map < int, set<string>>::iterator itr;

	set<int> v1;
	set<int> v2;
	set<int> v3;
	set<int> v4;

	vector<int>res;

	// checkClasse(v1, classes);

	// intersecaoVetores(v1, v2, &res);
	// checkClasse(res, classes);

	// checkClasse(v1, classes);
	// checkClasse(v1, classes);

	// checkClasse(individualmente, classes); (1) (2) (3) (4)
	// checkClasse(intersection(dois vetores), classes); (1.2) (1.3) (1.4) (2.3) (2.4) (3.4)
	// checkClasse(intersection(tres vetores), classes); ([1.2].3) ([1.2].4) ([1.3].4)
	// checkClasse(intersection(quatro vetores), classes); ({[1.2].3}.4)

	for (itr = classesT->begin();itr != classesT->end();++itr) {
		for (auto key : itr->second) {
			found = itens->find(key);

			v1 = found->second;
			cout << found->first << "\n";

			checkClasse(v1, classes);
		}
		cout << "================" << endl << endl;
	}
}

void Operacao::checkClasse(set<int> vecA, unordered_map < string, set<int>> *classes) {
	unordered_map < string, set<int>>::iterator itr;

	unordered_map<string, int> classes_aux;
	unordered_map<string, int>::iterator itr_aux;

	vector<int> res;
	int maior;
	string classe;

	for (itr = classes->begin();itr != classes->end();++itr) {
		intersecaoVetores(vecA, itr->second, &res);
		classes_aux.insert({ itr->first, res.size() });
	}
	cout << endl;

	maior = -1;
	for (itr_aux = classes_aux.begin();itr_aux != classes_aux.end();++itr_aux) {
		if (itr_aux->second > maior) {
			classe.assign(itr_aux->first);
			maior = itr_aux->second;
		}
		cout << itr_aux->second << " -> " << itr_aux->first << endl;
	}
	cout << "--------> " << classe << endl;
}

void Operacao::intersecaoVetores(set<int> v1, set<int>v2, vector<int> *res) {
	vector<int>::iterator itRes;

	// size_t tam = (v1.size() >= v2.size()) ? v1.size() : v2.size();
	res->resize(v1.size());

	itRes = set_intersection(
		v1.begin(), v1.end(),
		v2.begin(), v2.end(),
		res->begin());
	res->resize(itRes - res->begin());
}

#endif