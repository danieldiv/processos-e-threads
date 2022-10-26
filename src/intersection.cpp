#include "./include/intersetion.hpp"

Intersection::Intersection() {}
Intersection::~Intersection() {}

/**
 * @brief realiza a intersecao entre dois vetores e salva o resultado em res
 *
 * @param v1
 * @param res
 */
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