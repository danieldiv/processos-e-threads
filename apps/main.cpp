#include "read.hpp"
#include <map>
#include <typeinfo>

template <typename T> void control(string file) {
	T input;

	Read<T> r;
	r.readFile(file, &input, false);

	Util u;
	u.printMap(&input);
}

int main() {
	control <unordered_map<string, vector<int>>>("D");
	// control <map<tuple<int, string>, vector<int>>>("D");

	return EXIT_SUCCESS;
}