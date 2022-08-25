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

	void fazIntersecao(
		unordered_map < string, set<int>> *itens,
		unordered_map < int, set<string>> *classesT);
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
	unordered_map < int, set<string>> *classesT) {

	unordered_map < string, set<int>>::iterator found;
	unordered_map < int, set<string>>::iterator itr;

	for (itr = classesT->begin();itr != classesT->end();++itr) {
		for (auto key : itr->second) {
			found = itens->find(key);

			cout << found->first << " -> [ " << found->second.size() << " ] ";
			for (auto val : found->second)
				cout << val << " ";
			cout << endl;
		}
		cout << endl;
	}
}

#endif