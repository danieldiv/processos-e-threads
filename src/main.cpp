// #include <iostream>     // std::cout
// #include <algorithm>    // std::set_intersection, std::sort
// #include <vector>       // std::vector

// int main() {
// 	int first[] = { 5,10,15,20,25 };
// 	int second[] = { 50,40,30,20,10 };
// 	std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
// 	std::vector<int>::iterator it;

// 	std::sort(first, first + 5);     //  5 10 15 20 25
// 	std::sort(second, second + 5);   // 10 20 30 40 50

// 	it = std::set_intersection(first, first + 5, second, second + 5, v.begin());
// 	// 10 20 0  0  0  0  0  0  0  0
// 	std::cout << v.size() << std::endl;
// 	v.resize(it - v.begin());                      // 10 20
// 	std::cout << v.size() << std::endl;

// 	std::cout << "The intersection has " << (v.size()) << " elements:\n";
// 	for (it = v.begin(); it != v.end(); ++it)
// 		std::cout << ' ' << *it;
// 	std::cout << '\n';

// 	return 0;
// }

#include "arquivo.hpp"

template <typename T>
void control(string file) {
	T itens;
	T classes;

	Arquivo<T> arq;
	arq.readFile(file, &itens, &classes);

	Util<T> u;
	u.printMap(&itens);
	u.printMap(&classes);
}

int main() {
	control <unordered_map<string, set<int>>>("D");
	cout << "==========\n\n";
	control <unordered_map<int, set<string>>>("T");

	return EXIT_SUCCESS;
}