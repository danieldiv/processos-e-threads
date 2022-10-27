#include "./include/cache.hpp"

Cache::Cache() {
	setZero(true);
}

Cache::~Cache() {}

void Cache::setZero(bool valor) {
	this->vazio = valor;
}

bool Cache::getZero() {
	return this->vazio;
}