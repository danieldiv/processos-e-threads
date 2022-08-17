#ifndef READ_HPP
#define READ_HPP

#include <util.hpp>

#include <fstream>

using namespace std;

class Read {
private:
public:
	Read();
	~Read();
	void readFile(string file);
};

#endif