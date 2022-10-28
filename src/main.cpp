#include "./include/util/file.hpp"
#include "./include/kernel.hpp"

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
	dados.t_arquivos = duration_cast< duration<double> >(t2 - t1);

	while (op != 0) {
		system("clear");
		op = menu();
		cout << endl;

		if (op == 0) {
			cout << "O programa sera finalizado!" << endl;
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
				cout << (RED "Opcao invalida!" RESET) << endl;
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

	Kernel<p> k;

	t1 = steady_clock::now();
	k.setDados(&dados);
	k.itensInComum();
	t2 = steady_clock::now();

	dados.t_escalonamento = duration_cast< duration<double> >(t2 - t1);

	cout << "\nTempo leitura: " << dados.t_arquivos.count() << endl;
	cout << "Tempo de intercessoes: " << dados.t_intercessao.count() << endl;
	cout << "Tempo de escalonamento: " << dados.t_escalonamento.count() << endl;
}

int menu() {
	cout << "================" << endl;
	cout << "   POLITICAS" << endl;
	cout << "================" << endl << endl;

	cout << "1 - Fifo" << endl;
	cout << "2 - Menor job primeiro" << endl;
	cout << "3 - Maior job primeiro" << endl;
	// cout << "4 - Prioridade" << endl;
	cout << "0 - Sair" << endl;

	cout << "\nEscolha uma politica: ";

	int op;
	cin >> op;

	return op;
}

// Politicas getPolitica(int op) {
// 	switch (op) {
// 	case 1: return Politicas::FIFO;
// 	case 2: return Politicas::LOWEST_JOB_FIRST;
// 	case 3: return Politicas::BIGGEST_JOB_FIRST;
// 	default: return Politicas::NONE;
// 	}
// }