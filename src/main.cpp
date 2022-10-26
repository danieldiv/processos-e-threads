#include "./include/template/file.hpp"
#include "./include/kernel.hpp"

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

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
void escalonador(politicas politica);

int main() {
	int op = -1;

	while (op != 0) {
		system("clear");
		op = menu();
		cout << endl;

		switch (op) {
		case 1:
			escalonador(fifo);
			break;
		case 2:
			escalonador(lowest_job_first);
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

void escalonador(politicas politica) {
	steady_clock::time_point t1;
	steady_clock::time_point t2;

	duration<double> t_arquivos;
	duration<double> t_processamento;
	duration<double> t_intercessao;

	unordered_map<string, vector<int>> itens;
	unordered_map<string, vector<int>> classes;

	unordered_map<int, vector<string>> tarefaT;
	unordered_map<int, vector<string>> tarefaT_processamento;

	Kernel k;

	t1 = steady_clock::now();
	control(&itens, &classes, "D");
	control(&tarefaT, &tarefaT_processamento, "T");
	t2 = steady_clock::now();
	t_arquivos = duration_cast< duration<double> >(t2 - t1);

	t1 = steady_clock::now();
	k.setItens(&itens);
	k.setClasses(&classes);
	k.itensInComum(politica, &tarefaT, &tarefaT_processamento/*, &tarefaT_combinacoes*/);
	t2 = steady_clock::now();
	t_processamento = duration_cast< duration<double> >(t2 - t1);

	t1 = steady_clock::now();
	// k.fazIntersecoes();
	t2 = steady_clock::now();
	t_intercessao = duration_cast< duration<double> >(t2 - t1);

	cout << "\nTempo leitura de arquivos: " << t_arquivos.count() << endl;
	cout << "Tempo de processamento: " << t_processamento.count() << endl;
	cout << "Tempo de intercessoes: " << t_intercessao.count() << endl;
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