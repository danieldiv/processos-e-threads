#ifndef MYTHREAD_HPP
#define MYTHREAD_HPP

#include <string.h>

#include <pthread.h>

#include "./kernel.hpp"

#define NUMCONS 5

template<Politicas p>
struct estrutura_global {
	pthread_mutex_t pacotes_mutex;

	queue<pair < string, int>> pacotes;
	unordered_map < int, unordered_map<string, int>> result;

	Kernel<p> *k;
};

template<Politicas p>
void *addValue(void *arg);

template<Politicas p>
void *processaValue(void *arg);

template<Politicas p>
class MyThread {
private:
	pthread_t cons[NUMCONS];

	estrutura_global<p> vglobal;
public:
	Kernel<p> kernel;

	MyThread(Dados *dados) { this->kernel.setDados(dados); }
	~MyThread() {};

	void init();
	void initThread();
};

template<>
void MyThread<Politicas::ROUND_ROBIN>::init() {
	this->kernel.itensInComum();
	this->vglobal.k = &this->kernel;
	this->kernel.fazIntersecoes();
	this->kernel.dados->t_chaveamento = 0;
}

template<Politicas p>
void MyThread<p>::init() {
	steady_clock::time_point init;
	steady_clock::time_point end;

	this->kernel.itensInComum();
	this->kernel.fazIntersecoes();
	this->vglobal.k = &this->kernel;
	this->kernel.walkInPackage(&this->vglobal.pacotes);


	init = steady_clock::now();
	this->initThread();
	end = steady_clock::now();

	this->vglobal.k->dados->t_chaveamento = duration_cast<duration<double>>(end - init).count();
	this->vglobal.k->dados->t_chaveamento -= this->vglobal.k->dados->t_intercessao;

	this->vglobal.k->printResult(this->vglobal.result);
	this->vglobal.k->printAnalize();
}

template<Politicas p>
void MyThread<p>::initThread() {
	pthread_mutex_init(&this->vglobal.pacotes_mutex, NULL);

	for (int i = 0; i < NUMCONS; i++) {
		if (pthread_create(&(this->cons[i]), NULL, processaValue<p>, &this->vglobal) != 0) {
			perror("Erro ao criar thread\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < NUMCONS; i++) {
		if (pthread_join(this->cons[i], NULL) != 0) {
			perror("Erro ao aguardar finalizacao da thread.\n");
			exit(EXIT_FAILURE);
		}
	}
}

template<Politicas p>
void *processaValue(void *arg) {
	pair < string, int> dado;
	estrutura_global<p> *vglobal = (estrutura_global<p> *)arg;

	while (vglobal->pacotes.size() > 0) {
		pthread_mutex_lock(&vglobal->pacotes_mutex);
		if (vglobal->pacotes.size() > 0) {
			dado = vglobal->pacotes.front();
			vglobal->pacotes.pop();
			vglobal->k->checkCache(dado.first, dado.second, &vglobal->result);
		} else {
			this_thread::sleep_for(chrono::nanoseconds(200));
		}
		pthread_mutex_unlock(&vglobal->pacotes_mutex);

	}
	pthread_exit(arg);
}

#endif