#ifndef CACHE_HPP
#define CACHE_HPP

#include <string>
#include <unordered_map>

using namespace std;

class Cache {
private:
	bool vazio;
public:
	unordered_map<string, int> class_model;

	Cache();
	~Cache();

	void setZero(bool valor);
	bool getZero();
};

#endif