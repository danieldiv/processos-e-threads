#include "arquivo.hpp"
#include "operacao.hpp"

#include <ctime>

template <typename T>
void control(T *itens, T *classes, string file) {
	Arquivo<T> arq;
	arq.readFile(file, itens, classes);
}

template <typename T>
void imprimirMap(T *itens) {
	Util<T> u;
	u.printMap(itens);
}

template <typename T, typename D>
int menu(T *itens, D *tarefaT);

void insere_permutacoes(vector<set<string>> *permutacoes, string str) {
	set<string> valores;

	valores.insert(str);
	permutacoes->push_back(valores);
}

void perm(int tam) {
	set<string>::iterator it_1;
	set<string>::iterator it_2;
	set<string>::iterator it_3;
	set<string>::iterator it_aux;

	set<string> s1;
	s1.insert("A");
	s1.insert("C");
	s1.insert("B");
	s1.insert("D");

	vector<set<string>> permutacoes;

	string auxFinal("");
	string aux;

	for (it_1 = s1.begin(); it_1 != s1.end();++it_1) {
		auxFinal.append(*it_1).append(",");
		insere_permutacoes(&permutacoes, *it_1);
	}

	for (it_1 = s1.begin(); it_1 != s1.end();++it_1) {
		it_aux = it_1;

		for (it_2 = ++it_aux; it_2 != s1.end();++it_2) {
			aux.assign(*it_1).append(",").append(*it_2);
			insere_permutacoes(&permutacoes, aux);
		}
	}

	for (it_1 = s1.begin(); it_1 != s1.end();++it_1) {
		it_aux = it_1;

		for (it_2 = ++it_aux; it_2 != s1.end();++it_2) {
			it_aux = it_2;

			for (it_3 = ++it_aux; it_3 != s1.end();++it_3) {
				aux.assign(*it_1).append(",").append(*it_2).append(",").append(*it_3);
				insere_permutacoes(&permutacoes, aux);
			}
		}
	}

	auxFinal.erase(auxFinal.end() - 1, auxFinal.end());
	insere_permutacoes(&permutacoes, auxFinal);

	for (auto val : permutacoes) {
		cout << "-> ";
		for (auto v : val)
			cout << v << " ";
		cout << endl;
	}
}

int main() {
	clock_t start, end;

	unordered_map<string, set<int>> itens;
	unordered_map<string, set<int>> classes;

	unordered_map<int, set<string>> tarefaT;
	unordered_map<int, set<string>> classesT;
	// unordered_map<int, vector<set<string>>> tarefaT_permutacoes;

	Operacao opr;
	int op = -1;

	perm(4);

	// vector<set<int>> vec;
	// set<int> vec;

	// vec.insert(6);
	// vec.insert(3);
	// vec.insert(1);
	// vec.insert(2);
	// vec.insert(2);
	// vec.insert(5);

	// for (auto v : vec)
	// 	cout << v << " ";
	// cout << endl;

	// set<int> v;

	// v.insert(1);
	// v.insert(2);
	// v.insert(3);

	// vec.push_back(v);

	// do {
	// 	for (auto v : vec) {
	// 		cout << v << " ";
			// for (auto s : v)
			// 	cout << s << " ";
			// cout << endl;
	// 	}
	// 	cout << endl;
	// } while (next_permutation(vec.begin(), vec.end()));

	return 0;

	while (op != 0) {
		system("clear");
		op = menu(&itens, &tarefaT);
		cout << endl;

		switch (op) {
		case 1:
			control(&itens, &classes, "D");
			imprimirMap(&itens);
			break;
		case 2:
			if (!itens.empty()) {
				control(&tarefaT, &classesT, "T");
				opr.itensInComum(&itens, &tarefaT, &classesT);
				// opr.fazPermutacoes();
			} else cout << (RED "Nao e possivel executar a operacao!" RESET) << endl;
			break;
		case 3:
			if (!itens.empty() && !tarefaT.empty()) {
				start = clock();
				opr.fazIntersecoes(&itens, &classes, &classesT);
				end = clock();
				printf("\nTempo total: %0.8f\n", ((float)end - start) / CLOCKS_PER_SEC);
			} else cout << (RED "Nao e possivel executar a operacao!" RESET) << endl;
			break;
		case 0:
			cout << "O programa sera finalizado!" << endl;
			return EXIT_SUCCESS;
		default:
			cout << (RED "Opcao invalida!" RESET) << endl;
		}
		system("read -p \"\nPressione enter para continuar...\" continue");
	}

	return EXIT_SUCCESS;
}

template <typename T, typename D>
int menu(T *itens, D *tarefaT) {
	cout << "=================" << endl;
	cout << "   MENU OPCOES" << endl;
	cout << "=================" << endl << endl;

	cout << "1 - Ler arquivo D ";
	cout << (itens->empty() ? RED "Nao lido" : GREEN "Lido") << RESET << endl;

	cout << "2 - Ler arquivo T ";

	if (itens->empty())
		cout << (BLUE "Bloqueado" RESET) << endl;
	else if (tarefaT->empty())
		cout << (RED "Nao lido" RESET) << endl;
	else
		cout << (GREEN "Lido" RESET) << endl;

	cout << "3 - Realizar operacoes ";
	cout << (!(!itens->empty() && !tarefaT->empty()) ? BLUE "Bloqueado" : GREEN "Liberado") << RESET << endl;

	cout << "0 - Sair" << endl;
	cout << "\nEscolha uma opcao: ";

	int op;
	cin >> op;

	return op;
}