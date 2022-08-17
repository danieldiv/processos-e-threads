#include "read.hpp"
#include <map>

int main() {
	unordered_map<string, vector<int>>   inputD;
	map<tuple<int, string>, vector<int>> inputT;

	Read
		<unordered_map<string, vector<int>>>   r1;
	Read
		<map<tuple<int, string>, vector<int>>> r2;
	Util u;

	r1.readFile("D", &inputD);
	r2.readFile("T", &inputT);

	u.printMap(&inputD);
	cout << "============" << endl << endl;
	u.printMap(&inputT);

	return EXIT_SUCCESS;
}