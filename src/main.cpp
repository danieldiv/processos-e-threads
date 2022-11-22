#include "./include/util/file.hpp"
#include "./kernel/mythread.hpp"

#define TAM 1

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
void escalonador(Dados dados, Dados *dados_aux);

int main() {
	steady_clock::time_point t1;
	steady_clock::time_point t2;

	Dados dados;
	Dados dados_aux;
	Politicas politica;

	t1 = steady_clock::now();
	control(&dados.itens, &dados.classes, "D");
	control(&dados.tarefaT, &dados.tarefaT_processamento, "T");
	t2 = steady_clock::now();
	dados.t_leitura = duration_cast<duration<double>>(t2 - t1).count();

	int quant = TAM;

	dados_aux.t_leitura = dados.t_leitura;
	dados_aux.t_escalonamento = 0;
	dados_aux.t_processamento = 0;
	dados_aux.t_chaveamento = 0;
	dados_aux.t_intercessao = 0;

	while (quant-- > 0) escalonador<Politicas::LOWER_JOB_FIRST>(dados, &dados_aux);

	printf("\n");
	printf("Tempo de leitura       : %lf\n", dados_aux.t_leitura);
	printf("Tempo de escalonamento : %lf\n", dados_aux.t_escalonamento / TAM);
	printf("Tempo de processamento : %lf\n", dados_aux.t_processamento / TAM);
	printf("Tempo de chaveamento   : %lf\n", dados_aux.t_chaveamento / TAM);
	printf("Tempo de intercessoes  : %lf\n", dados_aux.t_intercessao / TAM);

	// escalonador<Politicas::ROUND_ROBIN>(dados);
	// escalonador<Politicas::BIGGER_JOB_FIRST>(dados);

	return EXIT_SUCCESS;
}

template<Politicas p>
void escalonador(Dados dados, Dados *dados_aux) {
	steady_clock::time_point t1;
	steady_clock::time_point t2;

	MyThread<p> myThread(&dados);

	t1 = steady_clock::now();
	myThread.init();
	t2 = steady_clock::now();

	dados.t_escalonamento = duration_cast<duration<double>>(t2 - t1).count();
	dados.t_processamento = dados.t_escalonamento - dados.t_chaveamento - dados.t_intercessao;

	dados_aux->t_escalonamento += dados.t_escalonamento;
	dados_aux->t_processamento += dados.t_processamento;
	dados_aux->t_chaveamento += dados.t_chaveamento;
	dados_aux->t_intercessao += dados.t_intercessao;
}