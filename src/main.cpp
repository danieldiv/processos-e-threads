#include "./include/template/file.hpp"
#include "./include/kernel.hpp"

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
void escalonador(Dados dados, politicas politica);

int main() {
	int op = -1;

	steady_clock::time_point t1;
	steady_clock::time_point t2;

	Dados dados;

	t1 = steady_clock::now();
	control(&dados.itens, &dados.classes, "D");
	control(&dados.tarefaT, &dados.tarefaT_processamento, "T");
	t2 = steady_clock::now();
	dados.t_arquivos = duration_cast< duration<double> >(t2 - t1);

	while (op != 0) {
		system("clear");
		op = menu();
		cout << endl;

		switch (op) {
		case 1:
			escalonador(dados, fifo);
			break;
		case 2:
			escalonador(dados, lowest_job_first);
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

void escalonador(Dados dados, politicas politica) {
	steady_clock::time_point t1;
	steady_clock::time_point t2;

	Kernel k;

	t1 = steady_clock::now();
	k.setDados(dados);
	k.itensInComum(politica);
	t2 = steady_clock::now();

	dados.t_processamento = duration_cast< duration<double> >(t2 - t1);

	cout << "\nTempo leitura: " << dados.t_arquivos.count() << endl;
	cout << "Tempo de processamento: " << dados.t_processamento.count() << endl;
}

int menu() {
	cout << "================" << endl;
	cout << "   POLITICAS" << endl;
	cout << "================" << endl << endl;

	cout << "1 - Fifo" << endl;
	cout << "2 - Menor job primeiro" << endl;
	// cout << "1 - Maior job primeiro" << endl;
	// cout << "1 - Prioridade job primeiro" << endl;
	cout << "0 - Sair" << endl;

	cout << "\nEscolha uma politica: ";

	int op;
	cin >> op;

	return op;
}