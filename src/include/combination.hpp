#ifndef COMBINATION_HPP
#define COMBINATION_HPP

// #include "./packages.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Combination {
private:
	vector<string> combinations;
	string temp;

	// map < int, set < pair < string, int>>>::iterator it_pkg;
public:
	Combination();
	~Combination();

	void combinate(vector<string> vetor, int perm[], int index, int n, int k, int linha);
	void printCombinations();
	void atribuiCombinations(vector<string> *combinations);
};

#endif