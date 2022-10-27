#ifndef DADOS_HPP
#define DADOS_HPP

#include <unordered_map>
#include <string>
#include <vector>

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

class Dados {
public:
	Dados();
	~Dados();

	// mapas

	std::unordered_map < std::string, std::vector<int>> itens;
	std::unordered_map < std::string, std::vector<int>> classes;

	std::unordered_map < int, std::vector<std::string>> tarefaT;
	std::unordered_map < int, std::vector<std::string>> tarefaT_processamento;
	std::unordered_map < int, std::vector<std::string>> tarefaT_combinacoes;

	// tempos

	duration<double> t_arquivos;
	duration<double> t_processamento;
	duration<double> t_intercessao;
};

#endif