Documentacao pode ser encontrada em [Wiki](https://github.com/danieldiv/processos-e-threads/wiki)

# Processos e treads

<p align="justify">
	O trabalho constitui de um sistema de classificação cujas características serão utilizadas para observar conceitos importantes como: escalonamento e gestão de memória primária. No sistema será utilizado dois arquivos, D e T. A base D será utilizada para simular a inicialização, fornecendo assim o conceito de bootstrapping, tal como no sistema operacional. A base T irá representar os processos a serem executados.
</p>

## Menu

![Scrennshot](src/resource/imgs/menuPrincipal.png)

- 1. Faz o escalonamento dos processos utilizando a politica Fifo
- 2. Faz o escalonamento dos processos utilizando a politica Menor job primeiro
- 3. Faz o escalonamento dos processos utilizando a politica Maior job primeiro

## Sistema multitarefa: Etapa I

- Na etapa I é realizada a leitura e tokenização do arquivo `D`. O arquivo sera tokenizado em 5 colunas que representam as chaves e as linhas representam os valores. As 4 primeiras colunas serão utilizadas como chaves dos itens e a ultima coluna sera utilizada como chave da classe.

## Sistema multitarefa: Etapa II

- Na etapa II é realizada a leitura, tokenização, `processamento` e `combinação` do arquivo `T`. O arquivo sera tokenizado linha a linha utilizando as colunas como valores e linha como chave.

## Sistema multitarefa: Etapa III

- Nesta etapa é feita a operação para encontrar a classe da tarefa em T, sendo impresso o resultado das linhas com as possiveis classes.

## Sistema multitarefa: Etapa IV

- Na etapa IV é feito uma modificação no código para que seja possivel utilizar `cache`, ou seja, antes de realizar todas as operacoes de interceções é feito primeiro a busca na cache, que caso não exista, é feita as intercessoes normalmente

## Sistema multitarefa: Etapa V

- A etapa 5 consiste em modificar a politica de escalonamento, neste projeto foi adotado 3 politicas, sendo: `Fifo`, `Menor job primeiro` e `Maior job primeiro`. Como algumas das chamadas dos metodos são bastantes semelhantes, a execução do [Kernel](https://github.com/danieldiv/processos-e-threads/blob/main/src/include/kernel.hpp) foi modificada para trabalhar no modelo de template.

## Sistema multitarefa: Etapa VI

- Nesta etapa será utilizado os pacotes criados na `etapa V`, com a diferença de que agora eles serão processados em threads. A execução das threads almenta a complexidade, logo o tempo de execução também sofreu impacotos.

# Compilação e Execução

| Comando    | Função                                                                                  |
| ---------- | --------------------------------------------------------------------------------------- |
| make clean | Apaga a última compilação realizada contida na pasta build                              |
| make       | Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta build |
| make run   | Executa o programa da pasta build após a realização da compilação                       |
