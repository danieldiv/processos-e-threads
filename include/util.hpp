#ifndef UTIL_HPP
#define UTIL_HPP

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Util {
private:
public:
	Util();
	~Util();
	void tokenizar(string text, unordered_map<string, vector<int>> *valores, int linha);
};

#endif