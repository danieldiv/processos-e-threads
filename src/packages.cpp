#include "./include/packages.hpp"

void Packages::quebrarEmPacotes(unordered_map < int, vector<string>> combinacoes) {
	unordered_map < int, vector<string>>::iterator itr;
	map < int, set < pair < string, int>>>::iterator it_pkg;

	pair<string, int> dado;

	for (itr = combinacoes.begin(); itr != combinacoes.end();++itr) {
		for (auto combinacao : itr->second) {

			dado = make_pair(combinacao, itr->first);
			this->packages.insert(dado);
		}
	}
}

void Packages::printPackage() {
	for (auto value : this->packages) {
		cout << value.first << " " << value.second << endl;
	}
}