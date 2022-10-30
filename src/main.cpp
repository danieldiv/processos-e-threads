#include "./include/util/file.hpp"
#include "./include/mythread.hpp"

template <typename T>
void control(T *itens, T *classes, string file) {
	File<T> arq;
	arq.readFile(file, itens, classes);
}

template <typename T>
void imprimirMap(T *itens) {
	Tokenizar<T> u;
	u.printMap(itens);
}

int menu();
Politicas getPolitica(int op);

template<Politicas p>
void escalonador(Dados dados);

int main() {
	int op = -1;

	steady_clock::time_point t1;
	steady_clock::time_point t2;

	Dados dados;
	Politicas politica;

	t1 = steady_clock::now();
	control(&dados.itens, &dados.classes, "D");
	control(&dados.tarefaT, &dados.tarefaT_processamento, "T");
	t2 = steady_clock::now();
	dados.t_leitura = duration_cast<duration<double>>(t2 - t1).count();

	while (op != 0) {
		system("clear");
		op = menu();
		// cout << endl;

		if (op == 0) {
			// cout << "O programa sera finalizado!" << endl;
			return EXIT_SUCCESS;
		} else {
			switch (op) {
			case 1:
				escalonador<Politicas::FIFO>(dados);
				break;
			case 2:
				escalonador<Politicas::LJF>(dados);
				break;
			case 3:
				escalonador<Politicas::BJF>(dados);
				break;
			default:
				printf((RED "Opcao invalida!\n" RESET));
			}
		}
		system("read -p \"\nPressione enter para continuar...\" continue");
	}

	return EXIT_SUCCESS;
}

template<Politicas p>
void escalonador(Dados dados) {
	steady_clock::time_point t1;
	steady_clock::time_point t2;

	MyThread<p> myThread(&dados);

	t1 = steady_clock::now();
	myThread.init();
	t2 = steady_clock::now();

	dados.t_escalonamento = duration_cast<duration<double>>(t2 - t1).count();
	dados.t_escalonamento -= dados.t_impressao;

	if (dados.t_chaveamento < 0) dados.t_chaveamento = -dados.t_chaveamento;

	dados.t_processamento = dados.t_escalonamento - dados.t_chaveamento - dados.t_intercessao;

	if (dados.t_processamento < 0) dados.t_processamento = -dados.t_processamento;

	printf("\n");
	printf("Tempo de leitura       : %lf\n", dados.t_leitura);
	printf("Tempo de escalonamento : %lf\n", dados.t_escalonamento);
	printf("Tempo de processamento : %lf\n", dados.t_processamento);
	// printf("Tempo de chaveamento   : %lf\n", dados.t_chaveamento);
	printf("Tempo de intercessoes  : %lf\n", dados.t_intercessao);
}

int menu() {
	printf("================\n");
	printf("   POLITICAS\n");
	printf("================\n\n");

	printf("1 - Fifo\n");
	printf("2 - Menor job primeiro\n");
	printf("3 - Maior job primeiro\n");
	// printf("4 - Prioridade\n");
	printf("0 - Sair\n");

	printf("\nEscolha uma politica: \n");

	int op;
	cin >> op;

	return op;
}