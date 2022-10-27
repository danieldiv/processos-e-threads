#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Combination {
private:
	vector<string> combinations;
	string temp;
public:
	Combination();
	~Combination();

	void combinate(vector<string> vetor, int perm[], int index, int n, int k, int linha);
	void printCombinations();
	void atribuiCombinations(vector<string> *combinations);
};

#endif