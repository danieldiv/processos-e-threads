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

int main() {
	clock_t start, end;

	start = clock();

	unordered_map<string, set<int>> itens;
	unordered_map<string, set<int>> classes;

	unordered_map<int, set<string>> tarefaT;
	unordered_map<int, set<string>> classesT;

	control(&itens, &classes, "D");
	control(&tarefaT, &classesT, "T");

	Operacao op;
	op.itensInComum(&itens, &tarefaT, &classesT);
	op.fazIntersecoes(&itens, &classes, &classesT);

	end = clock();

	printf("\nTempo total: %0.8f\n", ((float)end - start) / CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}