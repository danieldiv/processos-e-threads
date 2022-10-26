#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <vector>
#include <algorithm>

class Intersection {
public:
	Intersection();
	~Intersection();

	void intersecaoVetores(std::vector<int> v1, std::vector<int>v2, std::vector<int> *res);
};

#endif