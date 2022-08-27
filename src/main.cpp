// #include <iostream>     // std::cout
// #include <algorithm>    // std::set_intersection, std::sort
// #include <vector>       // std::vector

// #include <unordered_map>
// #include <set>

// using namespace std;

// int main() {
// 	set<int> itensA;
// 	set<int> itensB;
// 	vector<int>::iterator itr;

// 	itensA.insert(1);
// 	itensA.insert(3);
// 	itensA.insert(6);
// 	itensA.insert(7);
// 	itensA.insert(90);

// 	itensB.insert(2);
// 	itensB.insert(3);
// 	itensB.insert(7);
// 	itensB.insert(88);
// 	itensB.insert(90);

// 	vector<int> res(10);

// 	itr = set_intersection(
// 		itensA.begin(), itensA.end(),
// 		itensB.begin(), itensB.end(), res.begin());

// 	res.resize(itr - res.begin());

// 	for (itr = res.begin(); itr != res.end();++itr)
// 		cout << *itr << " ";
// 	cout << endl;

	// int first[] = { 5,10,15,20,25 };
	// int second[] = { 50,40,30,20,10 };
	// std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	// std::vector<int>::iterator it;

	// std::sort(first, first + 5);     //  5 10 15 20 25
	// std::sort(second, second + 5);   // 10 20 30 40 50

	// it = std::set_intersection(first, first + 5, second, second + 5, v.begin());
	// // 10 20 0  0  0  0  0  0  0  0
	// std::cout << v.size() << std::endl;
	// v.resize(it - v.begin());                      // 10 20
	// std::cout << v.size() << std::endl;

	// std::cout << "The intersection has " << (v.size()) << " elements:\n";
	// for (it = v.begin(); it != v.end(); ++it)
	// 	std::cout << ' ' << *it;
	// std::cout << '\n';

// 	return 0;
// }

#include "arquivo.hpp"
#include "operacao.hpp"

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
	unordered_map<string, set<int>> itens;
	unordered_map<string, set<int>> classes;

	unordered_map<int, set<string>> tarefaT;
	unordered_map<int, set<string>> classesT;

	control(&itens, &classes, "D");
	control(&tarefaT, &classesT, "T");

	Operacao op;
	op.itensInComum(&itens, &tarefaT, &classesT);
	op.fazIntersecoes(&itens, &classes, &classesT);

	return EXIT_SUCCESS;
}