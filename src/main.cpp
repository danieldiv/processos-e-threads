#include "./include/util/file.hpp"
#include "./kernel/mythread.hpp"

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
	steady_clock::time_point t1;
	steady_clock::time_point t2;

	Dados dados;
	Politicas politica;

	t1 = steady_clock::now();
	control(&dados.itens, &dados.classes, "D");
	control(&dados.tarefaT, &dados.tarefaT_processamento, "T");
	t2 = steady_clock::now();
	dados.t_leitura = duration_cast<duration<double>>(t2 - t1).count();

	escalonador<Politicas::LOWER_JOB_FIRST>(dados);

	// escalonador<Politicas::ROUND_ROBIN>(dados);
	// escalonador<Politicas::BIGGER_JOB_FIRST>(dados);

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
	dados.t_processamento = dados.t_escalonamento - dados.t_chaveamento - dados.t_intercessao;

	printf("\n");
	printf("Tempo de leitura       : %lf\n", dados.t_leitura);
	printf("Tempo de escalonamento : %lf\n", dados.t_escalonamento);
	printf("Tempo de processamento : %lf\n", dados.t_processamento);
	printf("Tempo de chaveamento   : %lf\n", dados.t_chaveamento);
	printf("Tempo de intercessoes  : %lf\n", dados.t_intercessao);
}