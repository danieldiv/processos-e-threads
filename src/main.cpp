#include "./utils/combination.hpp"

using namespace std;


int main() {
	Combination c;

	vector<string> vetor;
	vector<bool> perm(N);

	vetor.push_back("DA");
	vetor.push_back("NI");
	vetor.push_back("EL");

	int cont = 1;

	for (auto item : vetor) {
		c.combinate(&vetor, &perm, 0, vetor.size(), cont++);
	}
	c.printCombinations();
	return 0;
}

// 	clock_t start, end;

// 	unordered_map<string, set<int>> itens;
// 	unordered_map<string, set<int>> classes;

// 	unordered_map<int, set<string>> tarefaT;
// 	unordered_map<int, set<string>> tarefaT_processamento;
// 	unordered_map<int, vector<string>> tarefaT_permutacoes;

// 	Operacao opr;
// 	int op = -1;

// 	while (op != 0) {
// 		system("clear");
// 		op = menu(&itens, &tarefaT);
// 		cout << endl;

// 		switch (op) {
// 		case 1:
// 			control(&itens, &classes, "D");
// 			imprimirMap(&itens);
// 			break;
// 		case 2:
// 			if (!itens.empty()) {
// 				control(&tarefaT, &tarefaT_processamento, "T");
// 				opr.itensInComum(&itens, &tarefaT, &tarefaT_processamento, &tarefaT_permutacoes);
// 			} else cout << (RED "Nao e possivel executar a operacao!" RESET) << endl;
// 			break;
// 		case 3:
// 			if (!itens.empty() && !tarefaT.empty()) {
// 				start = clock();
// 				opr.fazIntersecoes(&itens, &classes, &tarefaT_processamento);
// 				end = clock();
// 				printf("\nTempo total: %0.8f\n", ((float)end - start) / CLOCKS_PER_SEC);
// 			} else cout << (RED "Nao e possivel executar a operacao!" RESET) << endl;
// 			break;
// 		case 0:
// 			cout << "O programa sera finalizado!" << endl;
// 			return EXIT_SUCCESS;
// 		default:
// 			cout << (RED "Opcao invalida!" RESET) << endl;
// 		}
// 		system("read -p \"\nPressione enter para continuar...\" continue");
// 	}

// 	return EXIT_SUCCESS;
// }

// template <typename T, typename D>
// int menu(T *itens, D *tarefaT) {
// 	cout << "=================" << endl;
// 	cout << "   MENU OPCOES" << endl;
// 	cout << "=================" << endl << endl;

// 	cout << "1 - Ler arquivo D ";
// 	cout << (itens->empty() ? RED "Nao lido" : GREEN "Lido") << RESET << endl;

// 	cout << "2 - Ler arquivo T ";

// 	if (itens->empty())
// 		cout << (BLUE "Bloqueado" RESET) << endl;
// 	else if (tarefaT->empty())
// 		cout << (RED "Nao lido" RESET) << endl;
// 	else
// 		cout << (GREEN "Lido" RESET) << endl;

// 	cout << "3 - Realizar operacoes ";
// 	cout << (!(!itens->empty() && !tarefaT->empty()) ? BLUE "Bloqueado" : GREEN "Liberado") << RESET << endl;

// 	cout << "0 - Sair" << endl;
// 	cout << "\nEscolha uma opcao: ";

// 	int op;
// 	cin >> op;

// 	return op;
// }