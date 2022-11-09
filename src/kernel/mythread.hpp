#ifndef MYTHREAD_HPP
#define MYTHREAD_HPP

#include <string.h>

#include <pthread.h>

#include "./kernel.hpp"

#define NUMPROD 5
#define NUMCONS 5

template<Politicas p>
struct memorial_virtual {
	pthread_mutex_t buffer_mutex;
	pthread_mutex_t pacotes_mutex;

	queue<content_processo> buffer;
	queue<pair < string, int>> *pacotes;

	unordered_map < int, unordered_map<string, int>> *result;

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

	memorial_virtual<p> vglobal;
	queue<pair < string, int>> pacotes;
	unordered_map < int, unordered_map<string, int>> result;
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
	this->kernel.findClasses();
	this->kernel.dados->t_chaveamento = 0;
}

template<Politicas p>
void MyThread<p>::init() {
	steady_clock::time_point init;
	steady_clock::time_point end;

	this->kernel.itensInComum();
	this->kernel.findClasses();
	this->vglobal.k = &this->kernel;
	this->kernel.walkInPackage(&this->pacotes);
	this->vglobal.pacotes = &this->pacotes;
	this->vglobal.result = &this->result;

	init = steady_clock::now();
	this->initThread();
	end = steady_clock::now();

	this->vglobal.k->dados->t_chaveamento = duration_cast<duration<double>>(end - init).count();
	this->vglobal.k->dados->t_chaveamento -= this->vglobal.k->dados->t_intercessao;

	this->vglobal.k->printResult(this->result);
	this->vglobal.k->printAnalize();
}

template<Politicas p>
void MyThread<p>::initThread() {
	pthread_mutex_init(&this->vglobal.buffer_mutex, NULL);
	pthread_mutex_init(&this->vglobal.pacotes_mutex, NULL);

	for (int i = 0; i < NUMPROD; i++) {
		if (pthread_create(&(this->prod[i]), NULL, addValue<p>, &this->vglobal) != 0) {
			perror("Erro ao criar thread prod\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < NUMCONS; i++) {
		if (pthread_create(&(this->cons[i]), NULL, processaValue<p>, &this->vglobal) != 0) {
			perror("Erro ao criar thread cons\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < NUMPROD; i++) {
		if (pthread_join(this->prod[i], NULL) != 0) {
			perror("Erro ao aguardar finalizacao da thread prod.\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < NUMCONS; i++) {
		if (pthread_join(this->cons[i], NULL) != 0) {
			perror("Erro ao aguardar finalizacao da thread cons.\n");
			exit(EXIT_FAILURE);
		}
	}
}

template<Politicas p>
void *addValue(void *arg) {
	memorial_virtual<p> *vglobal = (memorial_virtual<p> *)arg;
	pair < string, int> dado;
	content_processo c_mmu;
	bool aux = false;

	while (vglobal->pacotes->size() > 0) {
		pthread_mutex_lock(&vglobal->pacotes_mutex);

		if (vglobal->pacotes->size() > 0) {

			dado = vglobal->pacotes->front();
			vglobal->pacotes->pop();
			aux = true;
		}
		pthread_mutex_unlock(&vglobal->pacotes_mutex);

		if (aux) {
			pthread_mutex_lock(&vglobal->buffer_mutex);
			c_mmu.item = dado;
			vglobal->buffer.push(c_mmu);
			pthread_mutex_unlock(&vglobal->buffer_mutex);
		}
		aux = false;
	}
	pthread_exit(arg);
}

template<Politicas p>
void *processaValue(void *arg) {
	memorial_virtual<p> *vglobal = (memorial_virtual<p> *)arg;
	content_processo c_processo;

	while (!(vglobal->pacotes->size() == 0 && vglobal->buffer.size() == 0)) {
		pthread_mutex_lock(&vglobal->buffer_mutex);
		if (vglobal->buffer.size() > 0) {
			c_processo = vglobal->buffer.front();
			vglobal->buffer.pop();
			vglobal->k->checkCache(vglobal->result, &c_processo);
		}
		pthread_mutex_unlock(&vglobal->buffer_mutex);
	}
	pthread_exit(arg);
}

#endif