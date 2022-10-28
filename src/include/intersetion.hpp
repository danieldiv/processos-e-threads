#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <vector>
#include <algorithm>

class Intersection {
public:
	Intersection() {};
	~Intersection() {};

	void intersecaoVetores(std::vector<int> v1, std::vector<int>v2, std::vector<int> *res);
};

void Intersection::intersecaoVetores(std::vector<int> v1, std::vector<int>v2, std::vector<int> *res) {
	std::vector<int>::iterator itRes;

	res->clear();
	res->resize(v1.size());
	sort(res->begin(), res->end());

	itRes = set_intersection(
		v1.begin(), v1.end(),
		v2.begin(), v2.end(),
		res->begin());
	res->resize(itRes - res->begin());
}

#endif