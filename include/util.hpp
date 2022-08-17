#ifndef UTIL_HPP
#define UTIL_HPP

#include <map>
#include <tuple>

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
	void tokenizar(string text, map<tuple<int, string>, vector<int>> *valores, int linha);

	void printMap(unordered_map<string, vector<int>> *valores);
	void printMap(map<tuple<int, string>, vector<int>> *valores);
};

#endif