#ifndef MYTHREAD_HPP
#define MYTHREAD_HPP

#include <string.h>

#include <semaphore.h>
#include <pthread.h>

#include "./kernel.hpp"

#define NUMPROD 5
#define NUMCONS 5

template<Politicas p>
struct estrutura_global {
	pthread_mutex_t buffer_mutex;
	sem_t buffer_full;
	sem_t buffer_empty;

	queue<pair < string, int>> buffer;
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
	pthread_t prod[NUMPROD];
	pthread_t cons[NUMCONS];

	estrutura_global<p> vglobal;
	queue<pair < string, int>> *pkgs;
public:
	Kernel<p> kernel;

	MyThread(Dados *dados) { this->kernel.setDados(dados); }
	~MyThread() {};

	void init();
	void initThread();
};

template<>
void MyThread<Politicas::FIFO>::init() {
	this->kernel.itensInComum();
	this->vglobal.k = &this->kernel;

	steady_clock::time_point init = steady_clock::now();

	this->kernel.fazIntersecoes();

	this->vglobal.k->dados->t_intercessao =
		duration_cast<duration<double>>(steady_clock::now() - init);
}

template<Politicas p>
void MyThread<p>::init() {
	this->kernel.itensInComum();

	steady_clock::time_point init = steady_clock::now();

	this->kernel.fazIntersecoes();
	this->vglobal.k = &this->kernel;
	this->pkgs = &this->vglobal.pacotes;
	this->kernel.walkInPackage(this->pkgs);
	this->initThread();

	this->vglobal.k->dados->t_intercessao =
		duration_cast<duration<double>>(steady_clock::now() - init);

	this->vglobal.k->printResult(this->vglobal.result);
	this->vglobal.k->printAnalize();
}

template<Politicas p>
void MyThread<p>::initThread() {
	pthread_mutex_init(&this->vglobal.buffer_mutex, NULL);
	sem_init(&this->vglobal.buffer_full, 0, this->pkgs->size());
	sem_init(&this->vglobal.buffer_empty, 0, 0);

	for (int i = 0; i < NUMPROD; i++) pthread_create(&(this->prod[i]), NULL, addValue<p>, &this->vglobal);
	for (int i = 0; i < NUMCONS; i++) pthread_create(&(this->cons[i]), NULL, processaValue<p>, &this->vglobal);

	for (int i = 0; i < NUMPROD; i++) pthread_join(this->prod[i], NULL);
	for (int i = 0; i < NUMCONS; i++) pthread_join(this->cons[i], NULL);
}

template<Politicas p>
void *addValue(void *arg) {
	estrutura_global<p> *vglobal = (estrutura_global<p> *)arg;
	pair < string, int> dado;

	while (vglobal->pacotes.size() > 0) {
		sem_wait(&vglobal->buffer_full);
		pthread_mutex_lock(&vglobal->buffer_mutex);

		dado = vglobal->pacotes.front();
		vglobal->buffer.push(dado);
		vglobal->pacotes.pop();

		pthread_mutex_unlock(&vglobal->buffer_mutex);
		sem_post(&vglobal->buffer_empty);

		printf("[PROD] pacotes [%3ld] :: fila [%3ld] :: Lendo: # %s\n",
			vglobal->pacotes.size(), vglobal->buffer.size(), dado.first.c_str());
	}
	pthread_exit(arg);
}

template<Politicas p>
void *processaValue(void *arg) {
	pair < string, int> dado;
	estrutura_global<p> *vglobal = (estrutura_global<p> *)arg;

	while (!(vglobal->pacotes.size() == 0 && vglobal->buffer.size() == 0)) {
		sem_wait(&vglobal->buffer_empty);
		pthread_mutex_lock(&vglobal->buffer_mutex);

		dado = vglobal->buffer.front();
		vglobal->buffer.pop();

		pthread_mutex_unlock(&vglobal->buffer_mutex);
		sem_post(&vglobal->buffer_full);

		vglobal->k->checkCache(dado.first, dado.second, &vglobal->result);
		printf("[CONS] pacotes [%3ld] :: fila [%3ld] :: Consumindo: # %s\n",
			vglobal->pacotes.size(), vglobal->buffer.size(), dado.first.c_str());
	}
	pthread_exit(arg);
}

#endif