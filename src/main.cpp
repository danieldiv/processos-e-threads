#include "./class/template/arquivo.hpp"
#include "./class/operacao.hpp"

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

template <typename T, typename D, typename U>
int menu(T *itens, D *tarefaT, U *combinacoes);

int main() {
	clock_t start, end;

	unordered_map<string, vector<int>> itens;
	unordered_map<string, vector<int>> classes;

	unordered_map<int, vector<string>> tarefaT;
	unordered_map<int, vector<string>> tarefaT_processamento;
	unordered_map<int, vector<string>> tarefaT_combinacoes;

	Operacao opr;
	int op = -1;

	while (op != 0) {
		system("clear");
		op = menu(&itens, &tarefaT, &tarefaT_combinacoes);
		cout << endl;

		switch (op) {
		case 1:
			control(&itens, &classes, "D");
			break;
		case 2:
			if (!itens.empty()) {
				control(&tarefaT, &tarefaT_processamento, "T");

				opr.setItens(itens);
				opr.setClasses(classes);
				opr.itensInComum(&tarefaT, &tarefaT_processamento, &tarefaT_combinacoes);
			} else cout << (RED "Nao e possivel executar a operacao!" RESET) << endl;
			break;
		case 3:
			if (!itens.empty() && !tarefaT.empty()) {
				start = clock();
				opr.fazIntersecoes(&tarefaT_combinacoes);
				end = clock();
				printf("\nTempo total: %0.8f\n", ((float)end - start) / CLOCKS_PER_SEC);
			} else cout << (RED "Nao e possivel executar a operacao!" RESET) << endl;
			break;
		case 4:
			if (!itens.empty()) imprimirMap(&itens);
			else cout << (RED "Opcao invalida!" RESET) << endl;
			break;
		case 5:
			if (!tarefaT_combinacoes.empty()) imprimirMap(&tarefaT_combinacoes);
			else cout << (RED "Opcao invalida!" RESET) << endl;
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

template <typename T, typename D, typename U>
int menu(T *itens, D *tarefaT, U *combinacao) {
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

	if (itens->size() > 0) cout << "4 - Imprimir dados arquivo D" << endl;
	if (combinacao->size() > 0) cout << "5 - Imprimir dados arquivo T combinados" << endl;

	cout << "0 - Sair" << endl;
	cout << "\nEscolha uma opcao: ";

	int op;
	cin >> op;

	return op;
}