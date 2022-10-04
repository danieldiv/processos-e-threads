#include "./include/template/file.hpp"
#include "./include/kernel.hpp"

#include <ctime>

template <typename T>
void control(T *itens, T *classes, string file) {
	File<T> arq;
	arq.readFile(file, itens, classes);
}

template <typename T>
void imprimirMap(T *itens) {
	Util<T> u;
	u.printMap(itens);
}

int menu();

int main() {
	clock_t start, end;

	unordered_map<string, vector<int>> itens;
	unordered_map<string, vector<int>> classes;

	unordered_map<int, vector<string>> tarefaT;
	unordered_map<int, vector<string>> tarefaT_processamento;
	unordered_map<int, vector<string>> tarefaT_combinacoes;

	int op = -1;

	float t_arquivos;
	float t_processamento;
	float t_intercessao;

	Kernel k;
	while (op != 0) {
		system("clear");
		op = menu();
		// op = 1;
		cout << endl;

		switch (op) {
		case 1:
			start = clock();
			control(&itens, &classes, "D");
			control(&tarefaT, &tarefaT_processamento, "T");
			t_arquivos = (float)start / CLOCKS_PER_SEC;

			start = clock();
			k.setItens(&itens);
			k.setClasses(&classes);
			k.itensInComum(&tarefaT, &tarefaT_processamento, &tarefaT_combinacoes);
			t_processamento = (float)start / CLOCKS_PER_SEC;

			start = clock();
			k.fazIntersecoes(&tarefaT_combinacoes);
			t_intercessao = (float)start / CLOCKS_PER_SEC;

			printf("\nTempo leitura de arquivos: %0.6f\n", t_arquivos);
			printf("Tempo de processamento: %0.6f\n", t_processamento);
			printf("Tempo de intercessoes: %0.6f\n", t_intercessao);

			return EXIT_SUCCESS;
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

int menu() {
	cout << "=================" << endl;
	cout << "   MENU OPCOES" << endl;
	cout << "=================" << endl << endl;

	cout << "1 - Processar" << endl;
	cout << "0 - Sair" << endl;

	cout << "\nEscolha uma opcao: ";

	int op;
	cin >> op;

	return op;
}