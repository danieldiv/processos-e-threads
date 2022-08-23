#include "read.hpp"
#include <map>

template <typename T>
void control(string file, bool control) {
	T input;

	Read<T> r;
	r.readFile(file, &input, control);

	Util u;
	u.printMap(&input);
}

int main() {
	control <unordered_map<string, vector<int>>>("D", false);
	cout << "==========\n\n";
	control <unordered_map<string, vector<int>>>("T", true);
	// control <map<tuple<int, string>, vector<int>>>("D");

	return EXIT_SUCCESS;
}